#include <stdio.h>
#include <stdlib.h>
#include "../incl/matrix.h"

// Función que genera una matriz cuadrada como arreglo de arreglos, dado un tamaño entero "n".
// Entrada: Número de vértices del grafo
// Salida: Estructura con el número nodos y una matriz de adyacencia que permita representar un grafo del tamaño indicado.
// Cada valor dentro de la matriz quedará inicializado como 0.
MatrizGrafo* generarMatrizGrafo(int vertices) {
	MatrizGrafo* matriz = (MatrizGrafo*)malloc(sizeof(MatrizGrafo));
	matriz->vertices = vertices;
	matriz->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i;
	for (i = 0; i < vertices; i++) {
		matriz->adyacencias[i] = (int*)calloc(vertices, sizeof(int));
	}
	return matriz;
}

//por favor remplazar el 10 y la cantidad de espacios para que se vea bonito onda si son 100 darle un espacio mas
void imprimirMatrizAdyacencia(MatrizGrafo* matriz) {
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


MatrizGrafo* abrirArchivoMatriz(char *nombreArchivo) {
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

MatrizGrafo* eliminarCamino(int k, int l, MatrizGrafo* matrix){
	//se asume que el vertice que se ingresa no tiene peso 0
	if(matrix->vertices <= k || matrix->vertices <= l){
		return NULL;
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
	
	
	printf("Cantidad de adyacentes = %d \n",cantidadDeAdy);
	printf("El peso es = %d \n",peso);
	//si la division es decimal hay que sumarle uno ya que no se puede pagar una fraccion
	if(peso % cantidadDeAdy != 0){
		peso = peso / cantidadDeAdy + 2;
	}
	else{
		peso /= cantidadDeAdy;
		peso += 1;
	}

	printf("El peso es = %d \n",peso);

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

int main(){
	MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz("entrada.in");
	if (matrizAdyacencia == NULL) {
		printf("Archivo no encontrado.");
		return -1;
	}
	imprimirMatrizAdyacencia(matrizAdyacencia);
	matrizAdyacencia = eliminarCamino(0,2,matrizAdyacencia);
	imprimirMatrizAdyacencia(matrizAdyacencia);
    return 0;
}