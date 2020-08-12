#include <stdio.h>
#include <stdlib.h>
#include "../incl/matrix.h"
#include "../incl/backtracking.h"
#include "../incl/visitar.h"

int id = 1; //variable global que marca el id de todos
//mucho codigo de backtracking lo tenia de antes xD (metodos)

MatrizGrafo** agregarEstado(MatrizGrafo** lista, int * elementos, MatrizGrafo* estado){
	MatrizGrafo** nuevaLista = (MatrizGrafo**)malloc(sizeof(MatrizGrafo*)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

MatrizGrafo** sacarElemento(MatrizGrafo** lista, int * elementos){
	MatrizGrafo** nuevaLista = (MatrizGrafo**)malloc(sizeof(MatrizGrafo*)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

// ve si una matriz es igual a otra
// Entrada: dos matrices
//salida: un booleano que indica si son iguales o no

int sonIguales(MatrizGrafo* matriz1, MatrizGrafo* matriz2){
    int largo = matriz1->vertices;
    for(int i = 0; i < largo; i++){
        for(int j = i + 1; j < largo; j++){
            if(matriz1->adyacencias[i][j] != matriz2->adyacencias[i][j]){
                return 0; //son distintas
            }
        }
    }
    return 1; //son iguales
}

int esSolucionRepetida(MatrizGrafo** soluciones, int* canSoluciones, MatrizGrafo* solucion){
    for(int i = 0; i < *canSoluciones; i++){
        if(sonIguales(soluciones[i],solucion)){
            return 1; //esta repetida           
        }
    }
    return 0; //no esta repetida
}
//genera hijos dado un padre y los añade a la lista
//entradas:una lista de matricesGrafo , &NumerodeElementosdeLaLista, la matriz padre
MatrizGrafo** generarHijos(MatrizGrafo** abiertos, int* canAbiertos, MatrizGrafo* padre){
    MatrizGrafo* aux;
    int largo = padre->vertices;
    for(int i = 0; i < largo; i++){
        for(int j = i + 1; j < largo; j++){
            if(padre->adyacencias[i][j] != 0 && sePuedeEliminarCamino(padre, i, j)){
                aux = copiarMatriz(padre);
                aux = eliminarCamino(i, j, aux);
                if(esConexo(aux) && aux != NULL){
                    id += 1;
                    aux->idAnterior = padre->id;
                    aux->id = id;
                    abiertos = agregarEstado(abiertos, canAbiertos, aux);
                }
            }
        }
    }
    return abiertos;
}

// Libera una lista y su matriz
void freeLista(MatrizGrafo** lista, int* tamano){
    for(int i = 0; i < *tamano; i++){
        freeMatriz(lista[i]);
    }
    free(lista);
}




//Recibe una matriz y determina su costo total


//Recibe la lista de soluciones y su largo para devolver la posicion de la matriz con el menor costo
int seleccionarMejorSolucion(MatrizGrafo** soluciones,int *canSoluciones){
    int costo = 9999999;
    int id = 0;
    for(int i = 0; i < *canSoluciones; i++){
        if(costoMatriz(soluciones[i]) < costo){
            id = i;
            costo = costoMatriz(soluciones[i]);
        }
    }
    return id;
}
int sePuedeEliminarCamino(MatrizGrafo* matriz,int i ,int j){
    int aux = matriz->adyacencias[i][j];
    matriz->adyacencias[i][j] = 0;
    if(esConexo(matriz)){
        matriz->adyacencias[i][j] = aux;
        return 1;
    }
    else{
        matriz->adyacencias[i][j] = aux;
        return 0;
    }

}
MatrizGrafo** backTracking(MatrizGrafo** abiertos, MatrizGrafo** soluciones,int* canAbiertos, int* canSoluciones, MatrizGrafo* inicial){
    if(*canAbiertos <= 0){
        return soluciones;
    }

    MatrizGrafo* aux;
    while(*canAbiertos > 0){
        aux = abiertos[0];
        abiertos = sacarElemento(abiertos, canAbiertos);
        
        #ifdef DEBUG
        printf("Matriz id: %d \n",aux->id);
        printCurrent(aux);
        printf("\n");
        #endif
        if(esConexo(aux) && !sonIguales(aux,inicial)){
            soluciones = agregarEstado(soluciones, canSoluciones, aux);
            abiertos = generarHijos(abiertos, canAbiertos, aux);
            continue;
        }
        else{
            abiertos = generarHijos(abiertos, canAbiertos, aux);
        }
    }
    return soluciones;
}
MatrizGrafo* algoritmo(char const* entrada){
     //cosas iniciales
    MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz(entrada);
    if (matrizAdyacencia == NULL) {
		printf("Archivo no encontrado. \n");
		return NULL;
	}
    if(!esConexo(matrizAdyacencia)){
        printf("Su matriz no es conexa, por favor ingresar un archivo con una matriz conexa.\n");
        return NULL;
    }
    int canAbiertos = 0;
	int canCerrados = 0;
    int canSoluciones = 0;

    MatrizGrafo ** soluciones = (MatrizGrafo **)malloc(sizeof(MatrizGrafo*)*canSoluciones);
	MatrizGrafo ** abiertos = (MatrizGrafo **)malloc(sizeof(MatrizGrafo*)*canAbiertos);
    abiertos = agregarEstado(abiertos, &canAbiertos, matrizAdyacencia);
    
    soluciones = backTracking(abiertos, soluciones, &canAbiertos, &canSoluciones, matrizAdyacencia);
    
    int i = seleccionarMejorSolucion(soluciones, &canSoluciones);

    matrizAdyacencia = copiarMatriz(soluciones[i]);
    freeLista(soluciones,&canSoluciones);
    
    return(matrizAdyacencia);
}

/*
4
1 2 16
1 3 17
1 4 5
2 3 2
2 4 4
3 4 4

*/