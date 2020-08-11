#include <stdio.h>
#include <stdlib.h>
#include "../incl/matrix.h"

// Función que genera una matriz cuadrada como arreglo de arreglos, dado un tamaño entero "n".
// Entrada: Número de vértices del grafo
// Salida: Estructura con el número nodos y una matriz de adyacencia que permita representar un grafo del tamaño indicado.
// Cada valor dentro de la matriz quedará inicializado como 0.
int costoMatriz(MatrizGrafo* matriz){
    int costo = 0;
    for(int i = 0; i < matriz->vertices; i++){
        for(int j = i + 1; j < matriz->vertices; j++){
            if(matriz->adyacencias[i][j] != 0){
                costo += matriz->adyacencias[i][j];
            }
        }
    }
    return costo;
}

MatrizGrafo* generarMatrizGrafo(int vertices) {
	MatrizGrafo* matriz = (MatrizGrafo*)malloc(sizeof(MatrizGrafo));
	matriz->vertices = vertices;
	matriz->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i;
	matriz->id = 0;
	matriz->idAnterior = 0;
	for (i = 0; i < vertices; i++) {
		matriz->adyacencias[i] = (int*)calloc(vertices, sizeof(int));
	}
	return matriz;
}
// Función que copia una matriz
// Entrada: La matriz a copiar
// Salida: Estructura MatrizGrafo*.
MatrizGrafo* copiarMatriz(MatrizGrafo* aCopiar){
	int vertices = aCopiar->vertices; 
	MatrizGrafo* matriz = (MatrizGrafo*)malloc(sizeof(MatrizGrafo));
	matriz->adyacencias = (int**)malloc(vertices * sizeof(int*));
	matriz->vertices = vertices;
	for (int i = 0; i < vertices; i++) {
		matriz->adyacencias[i] = (int*)calloc(vertices, sizeof(int));
	}
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			matriz->adyacencias[i][j] = aCopiar->adyacencias[i][j];
		}
	}
	return matriz;
}


//Funcion que imprime la matriz
//por favor remplazar el 10 y la cantidad de espacios para que se vea bonito onda si son 100 darle un espacio mas
void printCurrent(MatrizGrafo* matriz) {
	int i, j;
	for (i = 0; i < matriz->vertices; i++) {
		for (j = 0; j < matriz->vertices; j++) {
			int numero = matriz->adyacencias[i][j];
			if(numero < 10){
				printf(" %d ", numero);
			}
			else{
				printf("%d ", numero);
			}
		}
		printf("\n");
	}
}
void escribirArchivo(char const* nombreArchivo, MatrizGrafo* matrizOriginal, MatrizGrafo* solucion){
	FILE *archivo;
	
	archivo = fopen(nombreArchivo, "w");
	fprintf(archivo,"Aristas eliminadas\n");
	for(int i = 0; i < matrizOriginal->vertices; i++){
		for(int j = i + 1; j < matrizOriginal->vertices; j++){
			if(matrizOriginal->adyacencias[i][j] != 0 && solucion->adyacencias[i][j] == 0){
				fprintf(archivo,"%d %d %d \n",i + 1, j + 1, matrizOriginal->adyacencias[i][j]);
			}
		}
	}
	fprintf(archivo,"Grafo conexo\n");
	for(int i = 0; i < matrizOriginal->vertices; i++){
		for(int j = i + 1; j < matrizOriginal->vertices; j++){
			if(solucion->adyacencias[i][j] != 0){
				fprintf(archivo,"%d %d %d \n",i + 1, j + 1, solucion->adyacencias[i][j]);
			}
		}
	}
	fprintf(archivo, "costo total: %d",costoMatriz(solucion));

	fclose(archivo);
}
// Función que lee el archivo y lo transforma en una matriz
// Entrada: El nombre del archivo
// Salida: Estructura MatrizGrafo*.
MatrizGrafo* abrirArchivoMatriz(char const* nombreArchivo) {
	int size, j, i, aux;
	char ch;
	FILE *archivo;
	archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL) {
		return NULL;
	}
	fscanf(archivo, "%d", &size);
	MatrizGrafo* matrizAdyacencia = generarMatrizGrafo(size);
	i = 0;
	j = 0;
	aux = 0;
	while (!feof (archivo)){  
      if(i == 0){
		  fscanf (archivo, "%d", &i);
	  }
	  else if(j == 0){
		  fscanf (archivo, "%d", &j);
	  }
	  else{
		  fscanf (archivo, "%d", &aux);
		  matrizAdyacencia->adyacencias[i-1][j-1] = aux;
		  i = 0;
		  j = 0;
	  }
    }
	fclose(archivo);
	return matrizAdyacencia;
}

// Función que elimina un camino dado un punto y traspasa el peso a sus adyacencias
// Entrada: el camino IJ a ser eliminado y la matriz
// Salida: Estructura MatrizGrafo*.
MatrizGrafo* eliminarCamino(int k, int l, MatrizGrafo* matrix){
	//se asume que el vertice que se ingresa no tiene peso 0
	if(matrix->vertices <= k || matrix->vertices <= l){
		return matrix;
	}
	if(matrix->adyacencias[k][l] == 0){
		return matrix;
	}
	int maximo = matrix->vertices;
	int cantidadDeAdy = 0;
	int peso = matrix->adyacencias[k][l];
	matrix->adyacencias[k][l] = 0;

	//contar la cantidad de adyacentes
	for (int i = 0; i < maximo; i++){
		for (int j = 0; j < maximo; j++){
			int valor = matrix->adyacencias[i][j];
			if((i == k || j == k || i == l || j == l) && valor != 0){
				cantidadDeAdy += 1;
			}
		}
	}
	//si la division es decimal hay que sumarle uno ya que no se puede pagar una fraccion
	cantidadDeAdy += 1;
	if(peso % cantidadDeAdy != 0){
		peso = peso / cantidadDeAdy + 1;
	}
	else{
		peso /= cantidadDeAdy;
	}

	//ver que vertices son adyacentes
	for (int i = 0; i < maximo; i++){
		for (int j = 0; j < maximo; j++){
			int valor = matrix->adyacencias[i][j];
			if((i == k || j == k || i == l || j == l) && valor != 0){
				matrix->adyacencias[i][j] += peso;
			}
		}
	}

	return matrix;
}

//funcion que libera la memoria de las matrices

void freeMatriz(MatrizGrafo* matriz){
	for(int i = 0; i < matriz->vertices; i++){
		free(matriz->adyacencias[i]);
	}
	free(matriz->adyacencias);
	free(matriz);
}

