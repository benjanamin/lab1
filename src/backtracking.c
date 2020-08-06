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

// ve si una matriz es solucion
// entrada una matriz


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
            if(padre->adyacencias[i][j] != 0){
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


MatrizGrafo** backTracking(MatrizGrafo** abiertos, MatrizGrafo** cerrados, MatrizGrafo** soluciones,int* canAbiertos, int* canCerrados, int* canSoluciones, MatrizGrafo* inicial){
    MatrizGrafo* aux;
    if(*canAbiertos <= 0){
        return soluciones;
    }
    else{
        aux = abiertos[0];
        cerrados = agregarEstado(cerrados, canCerrados, aux);
        abiertos = sacarElemento(abiertos, canAbiertos);
        if(esConexo(aux) && !esSolucionRepetida(soluciones, canSoluciones, aux) && !sonIguales(aux,inicial)){
            soluciones = agregarEstado(soluciones, canSoluciones, aux);
            abiertos = agregarEstado(abiertos, canAbiertos, aux);

            return backTracking(abiertos, cerrados, soluciones, canAbiertos, canCerrados, canSoluciones, inicial);
            
        }
        
        else{
            abiertos = generarHijos(abiertos, canAbiertos, aux);
            return backTracking(abiertos, cerrados, soluciones, canAbiertos, canCerrados, canSoluciones, inicial);
        }
    }

}
int main(){
    //cosas iniciales
    MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz("entrada.in");
	if (matrizAdyacencia == NULL) {
		printf("Archivo no encontrado.");
		return -1;
	}
    int canAbiertos = 0;
	int canCerrados = 0;
    int canSoluciones = 0;
    
    MatrizGrafo ** soluciones = (MatrizGrafo **)malloc(sizeof(MatrizGrafo*)*canSoluciones);
	MatrizGrafo ** abiertos = (MatrizGrafo **)malloc(sizeof(MatrizGrafo*)*canAbiertos);
	MatrizGrafo ** cerrados = (MatrizGrafo **)malloc(sizeof(MatrizGrafo*)*canCerrados);
    abiertos = agregarEstado(abiertos, &canAbiertos, matrizAdyacencia);
    
    soluciones = backTracking(abiertos, cerrados, soluciones, &canAbiertos, &canCerrados, &canSoluciones, matrizAdyacencia);
    printf("inicio \n");
    printf("soluciones: %d \n", canSoluciones);
    for(int i = 0; i < canSoluciones; i++){
        printf("Solucion %d: \n",i);
        printf("id: %d \n", soluciones[i]->id);
        imprimirMatrizAdyacencia(soluciones[i]);
    }
    printf("termine \n");
    return 0;
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