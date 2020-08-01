#include <stdio.h>
#include <stdlib.h>

typedef struct matrizGrafo {
	int vertices;
	int** adyacencias;
}MatrizGrafo;

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
		  matrizAdyacencia->adyacencias[j-1][i-1] = aux;
		  i = 0;
		  j = 0;
	  }
    }
	fclose(archivo);
	return matrizAdyacencia;
}

int main(){
	MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz("entrada.in");
	if (matrizAdyacencia == NULL) {
		printf("Archivo no encontrado.");
		return -1;
	}
	imprimirMatrizAdyacencia(matrizAdyacencia);
	
    return 0;
}