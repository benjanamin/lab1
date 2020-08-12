#include <stdio.h>
#include <stdlib.h>
#include "../incl/matrix.h"
#include "../incl/backtracking.h"
#include "../incl/visitar.h"


int id = 1; //variable global que marca el id de todos
//mucho codigo de backtracking lo tenia de antes xD (metodos)

Lista* crearNodo(MatrizGrafo* matriz){
    Lista* aux = (Lista*)malloc(sizeof(Lista));
    aux->matriz = matriz;
    aux->siguiente = NULL;
    aux->largo = 0;
    return aux;
}

Lista* agregarNodo(Lista* cabeza, Lista* nodo){
    if(cabeza == NULL){
        cabeza = nodo;
        return cabeza;
    }
    else{
        Lista* aux = cabeza;
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = nodo;
        return cabeza;
    }
}
Lista* sacarNodo(Lista* cabeza){
    if(cabeza == NULL){
        return NULL;
    }
    else if(cabeza->siguiente = NULL){
        return NULL;
    }
    else{
        Lista* aux = cabeza->siguiente;

        return aux;
    }
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


//genera hijos dado un padre y los añade a la lista
//entradas:una lista de matricesGrafo , &NumerodeElementosdeLaLista, la matriz padre
Lista* generarHijos(Lista* cabeza, MatrizGrafo* padre){
   
    int largo = padre->vertices;
    for(int i = 0; i < largo; i++){
        for(int j = i + 1; j < largo; j++){
            if(padre->adyacencias[i][j] != 0 && sePuedeEliminarCamino(padre, i, j) ){
                MatrizGrafo* aux;
                aux = copiarMatriz(padre);
                aux = eliminarCamino(i, j, aux);
                if(esConexo(aux) && aux != NULL){
                    
                    Lista* nodo = crearNodo(aux);
                    id += 1;
                    aux->idAnterior = padre->id;
                    aux->id = id;

                    
                    cabeza = agregarNodo(cabeza, nodo);
                    
                }
            }
        }
    }
    
    return cabeza;
}

//Recibe una matriz y determina su costo total


//Recibe la lista de soluciones y su largo para devolver la posicion de la matriz con el menor costo

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

int esReducible(MatrizGrafo* matrix){
    for(int i = 0; i < matrix->vertices; i++){
        for(int j = i + 1; j < matrix->vertices; j++){
            if(sePuedeEliminarCamino(matrix,i,j)){
                return 1;
            }
        }
    }
    return 0;
}

MatrizGrafo* backTracking(Lista* cabeza){
    if(cabeza == NULL){
        return NULL;
    }
    
    MatrizGrafo* aux;
    MatrizGrafo* solucion = copiarMatriz(cabeza->matriz);
    int pesoMin = costoMatriz(solucion);
    Lista* puntero = cabeza;
    while(puntero != NULL){
        aux = puntero->matriz;
        int peso = costoMatriz(aux);
        #ifdef DEBUG
        printf("Matriz id: %d peso: %d\n",aux->id, peso);
        printCurrent(aux);
        printf("\n");
        #endif
        if(esConexo(aux) && peso < pesoMin &&!sonIguales(aux,solucion)){
            pesoMin = peso;
            solucion = copiarMatriz(aux);
            
        }
        else{
            puntero = generarHijos(puntero, aux);
            freeMatriz(puntero->matriz);
            
        }
        puntero = puntero->siguiente;
    }
    return solucion;
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
    MatrizGrafo* matriz;
    Lista* lista = crearNodo(matrizAdyacencia);
    
    matriz = backTracking(lista);
    return matriz; 
    

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