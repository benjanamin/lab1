#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/matrix.h"
#include "../incl/backtracking.h"
#include "../incl/visitar.h"

int main(int argc, char const *argv[]){
    char const* entrada;
    char const* salida; 
    if(argc < 2){

    }
    else{
        entrada = argv[1];
        salida = argv[2];
    }

    
    
    MatrizGrafo* matriz;
    matriz = algoritmo(entrada);
    imprimirMatrizAdyacencia(matriz);
    printf("termine");
    return 1;
}