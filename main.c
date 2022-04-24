#include <stdio.h>
#include <stdlib.h>
#define MAX_LINEA 100 // Numero de caracteres en una linea

typedef struct articulo{
    int  id;
    float precio;
    char  nom[50];
    int  cantidad;
}art_t;

typedef struct inventario{
    art_t* articulos;
    int tamano;
}inv_t;

inv_t leer_inventario(char archivo[]);
void escribir_inventario(inv_t inv, char archivo[]);
void agregar_art();
void print_art();
void eliminar_art();
void modificar_art();
void imprimir_art();
void imprimir_inventario(inv_t inv);
int numero_lineas();


int main(){
    char archivo[] = "inventario.txt";
    inv_t inventario = leer_inventario(archivo);

    int menu = 0;
    do{
        do{
            printf(
                "Menu\n"
                "1. Ingresar un articulo\n"
                "2. Eliminar un articulo\n"
                "3. Modificar un articulo\n"
                "4. Imprimir un articulo\n"
                "5. Reporte de inventario\n"
                "6. Salir\n"
                "Selecciona una opcion: "
            );
            scanf("%d", &menu);
        }while(menu > 6 || menu < 1);

        switch (menu) {
            case 1: agregar_art(); break;
            case 2: eliminar_art(); break;
            case 3: modificar_art(); break;
            case 4: imprimir_art(); break;
            case 5: imprimir_inventario(inventario); break;
            case 6:
                escribir_inventario(inv, archivo);
                printf("Adios :)\n"); break;
            default: printf("Hubo un error :(\n");
        }
    }while(menu != 6);
    free(inventario.articulos);
    return 0;
}

int numero_lineas(FILE *fp){
    int c;
    int tamano = 0;
    while ((c = getc(fp)) != EOF)
      if (c == '\n') tamano++;

    rewind(fp);
    return tamano;
}

inv_t leer_inventario(char archivo[]){
    FILE *fp;
    fp = fopen(archivo,"a+");
    int tamano = numero_lineas(fp);

    art_t* articulos = (art_t*) calloc(tamano, sizeof(art_t));

    // Leer el contenido del archivo
    char contenido[MAX_LINEA]; // Caracteres en una linea
    int linea = 0;
    while((fgets(contenido, sizeof(contenido), fp)) != NULL)
    {
        sscanf(contenido, "%d,%f,%s,%d",
               &articulos[linea].id,
               &articulos[linea].precio,
               articulos[linea].nom,
               &articulos[linea].cantidad);
        linea++;
    }

    inv_t inv = {articulos, tamano};

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

void agregar_art(){

    // Obtener inventario global?
    // Realloc para un articulo mas e incrementar tamano
    float precio;
    do{
        printf("\nIngresa el precio: ");
        scanf("%f", &precio);
    }while(precio < 0);
    art.precio = precio;

    // Limpiar buffer (no funciona fgets sin esto)
    int c;
    while((c = getchar()) != '\n' && c != EOF);

    // Usamos fgets para poder aceptar espacios
    printf("\nIngresa el nombre:\n");
    fgets(art.nom, 49, stdin);

    // Limpiamos el \n que sobra
    art.nom[strcspn(art.nom, "\n")] = 0;

    printf("\nIngresa la fecha: ");
    scanf("%s", art.fecha);

}

void print_art(){

}

void eliminar_art(){
    // Obtener inventario global?
    // Realloc para un articulo menos y decrementar tamano

}

void modificar_art(){
    // Obtener inventario global?

}

void imprimir_art(){
    printf("Ingresa el id del articulo que quieres seleccionar: ");


}

void imprimir_inventario(inv_t inv){

}
