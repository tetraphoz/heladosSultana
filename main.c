#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 100 // Numero de caracteres en una linea
#define TAMANO_NOMBRE 50 // Numero de caracteres disponibles para el nombre
#define TAMANO_ARCHIVO 20 // Numero de caracteres disponibles para el nombre del archivo
#define MAX_INVENTARIO 100 // Numero maximo de articulos que podemos procesar

typedef struct articulo{
    int  id;
    float precio;
    char  nom[TAMANO_NOMBRE];
    int  cantidad;
}art_t;

typedef struct inventario{
    art_t* articulos;
    int tamano;
}inv_t;

// Funciones de inventario
inv_t leer_inventario(char archivo[]);
void escribir_inventario(inv_t inv, char archivo[]);
void imprimir_inventario(inv_t inv);

// Funciones de articulos
void agregar_art(inv_t* inv);
void eliminar_art(inv_t* inv);
void modificar_art(inv_t* inv);
void imprimir_art(inv_t inv);
void ingresar_art(int pos, inv_t* inv);

// Funciones misc
int numero_lineas(char archivo[]);
int posicion_id(inv_t inv);
int id_valido(int id, inv_t inv);

int main(){
    char archivo[TAMANO_ARCHIVO] = "inventario.dat";
    inv_t inventario = leer_inventario(archivo);

    int menu = 0;
    do{
        do{
            printf(
                "Menu\n"
                "1. Ingresar un articulo\n"
                "2. Eliminar un articulo\n"
                "3. Modificar informacion de un articulo\n"
                "4. Imprimir un articulo\n"
                "5. Reporte de inventario\n"
                "6. Salir (Guardar cambios)\n"
                "Selecciona una opcion: "
            );
            scanf("%d", &menu);
        }while(menu > 6 || menu < 1);

        switch (menu) {
            case 1: agregar_art(&inventario); break;
            case 2: eliminar_art(&inventario); break;
            case 3: modificar_art(&inventario); break;
            case 4: imprimir_art(inventario); break;
            case 5: imprimir_inventario(inventario); break;
            case 6: escribir_inventario(inventario, archivo); break;
            default: printf("Hubo un error :(\n");
        }
    }while(menu != 6);
    return 0;
}

int numero_lineas(char archivo[TAMANO_ARCHIVO]){
    FILE *fp = fopen(archivo, "r");
    int c;
    int tamano = 0;

    do {
      c = fgetc(fp);
      if (c == '\n') tamano++;
    } while (c != EOF);

    fclose(fp);
    /* printf("Tamano: %d\n", tamano); */
    return tamano;
}

inv_t leer_inventario(char archivo[]){
    FILE *fp;
    fp = fopen(archivo,"a+");

    art_t articulos[MAX_INVENTARIO] = {};

    // Leer el contenido del archivo
    char contenido[MAX_LINEA]; // Caracteres en una linea
    int linea = 0;
    while((fgets(contenido, sizeof(contenido), fp)) != NULL)
    {
        sscanf(contenido, "%d,%f,%[^,],%d",
               &articulos[linea].id,
               &articulos[linea].precio,
               articulos[linea].nom,
               &articulos[linea].cantidad);
        linea++;
    }

    inv_t inv = {articulos, numero_lineas(archivo)};

    fclose(fp);
    return inv;
}

void escribir_inventario(inv_t inv, char archivo[]){
    FILE *fp;
    fp = fopen(archivo,"w");

    for(int i = 0; i <inv.tamano; i++){
        fprintf(fp ,"%d,%.2f,%s,%d\n",
                inv.articulos[i].id,
                inv.articulos[i].precio,
                inv.articulos[i].nom,
                inv.articulos[i].cantidad);
    }
    printf("Escritura exitosa :)\n");
    fclose(fp);
}

void ingresar_art(int pos, inv_t* inv){
    // Si ya existe un id dejarlo igual
    if(inv->articulos[pos].id == 0){
        int id = 0;
        do {
          printf("\nIngresa el id: ");
          scanf("%d", &id);
        } while (id < 0 || !id_valido(id, *inv));
        inv->articulos[pos].id = id;
    }
    /* inv->articulos[pos].id = pos; */

    float precio = 0;
    do{
        printf("\nIngresa el precio: ");
        scanf("%f", &precio);
    }while(precio < 0);
    inv->articulos[pos].precio = precio;

    // Limpiar buffer (no funciona fgets sin esto)
    int c;
    while((c = getchar()) != '\n' && c != EOF);

    // Usamos fgets para poder aceptar espacios
    char nom[TAMANO_NOMBRE];
    printf("\nIngresa el nombre: ");
    fgets(nom, TAMANO_NOMBRE-1, stdin); // Dejamos espacio para el \0 al final de la cadena

    // Limpiamos el \n que sobra
    strncpy(inv->articulos[pos].nom, nom, strlen(nom)-1);

    int cantidad = 0;
    do{
        printf("\nIngresa la cantidad: ");
        scanf("%d", &cantidad);
    }while(cantidad < 0);
    inv->articulos[pos].cantidad = cantidad;
}

void agregar_art(inv_t* inv){
    if(inv->tamano >= MAX_INVENTARIO){
        printf("El inventario ya esta lleno\n");
        return;
    }

    ingresar_art(inv->tamano, inv);
    // Actualizamos el tamano
    inv->tamano++;
}

void imprimir_art(inv_t inv){
    int pos = posicion_id(inv);
    if(pos >= 0) {
        printf("\nID:\t%d\nPrecio:\t$%.2f\nNombre:\t%s\nCantidad:\t%d\n",
               inv.articulos[pos].id, inv.articulos[pos].precio, inv.articulos[pos].nom,
               inv.articulos[pos].cantidad);
    }
}

void eliminar_art(inv_t* inv){
    int pos = posicion_id(*inv);
    if(pos >= 0) {
        // Mover posicion de los elementos del arreglo un lugar a la izquierda
        for(int i = pos; pos < inv->tamano; pos++){
            inv->articulos[pos] = inv->articulos[pos+1];
        }
        // Reducimos el tamano
        inv->tamano--;
    }
}

void modificar_art(inv_t* inv){
    int pos = posicion_id(*inv);
    if(pos >= 0) ingresar_art(pos, inv); // Sobreescribimos sobre los valores anteriores
}

void imprimir_inventario(inv_t inv){
    if(inv.tamano == 0){
        printf("El inventario esta vacio. Ingresa un nuevo articulo e intentalo de nuevo\n");
        return;
    }

    for(int pos = 0; pos < inv.tamano; pos++){
        printf("ID: %d\tPrecio: $%.2f\tNombre: %s\tCantidad: %d\n",
               inv.articulos[pos].id, inv.articulos[pos].precio, inv.articulos[pos].nom,
               inv.articulos[pos].cantidad);
    }
}

int posicion_id(inv_t inv){
    int id = 0;
    do{
        printf("Ingresa el id del articulo: ");
        scanf("%d", &id);
    }while(id < 0);

    int pos = -1;
    for(int i = 0; i < inv.tamano; i++){
        if(id == inv.articulos[i].id){
            pos = i;
            break;
        }
    }
    if(pos == -1) printf("No existe un articulo con ese id (Puede consultar los valores validos con la opcion 5.)\n");
    return pos;
}

int id_valido(int id, inv_t inv){
    // Validar que no se repitan los id
    if(id == 0){
        printf("El id tiene que ser positivo.\n");
        return 0;
    }
    for(int i = 0; i < inv.tamano; i++){
        if(id == inv.articulos[i].id){
            printf("El id que ingreso ya esta registrado.\n");
            return 0;
        }
    }
    return 1;
}
