#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "../incl/matrix.h"
#include "../incl/backtracking.h"
#include "../incl/visitar.h"

int main(int argc, char const *argv[]){
    char const* entrada;
    char const* salida; 
    if(argc != 3){

        printf( "Nombres no ingresados");
        return 0;
    }
    else{
        entrada = argv[1];
        salida = argv[2];
    }
    MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz(entrada);
    MatrizGrafo* matriz;
    #ifdef DEBUG
    printf("Matriz inicial: \n");
    printCurrent(matrizAdyacencia);
    #endif
    matriz = algoritmo(entrada);
    escribirArchivo(salida,matrizAdyacencia,matriz);
    printf("termine");
    return 1;
}