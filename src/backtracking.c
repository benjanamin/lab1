#include <stdio.h>
#include <stdlib.h>
#include "../incl/matrix.h"
#include "../incl/backtracking.h"
int conexiones(MatrizGrafo* matriz, int i){
    int aux = 0;
    for(int j = 0; j < matriz->vertices ; j++){
        //revisar columna i
        if(matriz->adyacencias[j][i] != 0){
            aux += 1;
        }
        //revisar fila
        if(matriz->adyacencias[i][j]){
            aux += 1;
        }
    }
    return aux;
}

int esSolucion(MatrizGrafo* matriz){
    int arrayVertices[matriz->vertices];
    int largo = matriz->vertices;
    for(int i = 0; i < largo; i++){
        arrayVertices[i] = conexiones(matriz, i);
        if(arrayVertices[i] != 1){
            return 0;
        }
    }
    return 1;
}


int main(){
    MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz("entrada.in");
    MatrizGrafo* copia = generarSubMatriz(matrizAdyacencia,2);
    imprimirMatrizAdyacencia(copia);
	if (matrizAdyacencia == NULL) {
		printf("Archivo no encontrado.");
		return -1;
	}
    printf("%d \n" ,esSolucion(matrizAdyacencia));
	matrizAdyacencia = eliminarCamino(0,2,matrizAdyacencia);
	imprimirMatrizAdyacencia(matrizAdyacencia);
    return 0;
}