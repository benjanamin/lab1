#include <stdio.h>
#include <stdlib.h>
#include "../incl/matrix.h"


int top(int* cola,int largo){
	return cola[largo-1];
}
//A�ade un numero a la cola
//Entrada: una cola, el largo y el numero a a�adir 
//Salida:  una cola
int* push(int* cola,int* largo,int numero){
	int* aux= (int*)malloc(sizeof(int)*(*largo+1));
	for(int i=0;i<*largo + 1;i++){
			aux[i]=cola[i];
	}
	aux[*largo]=numero;
	*largo=*largo+1;
	return aux;
}

//Elimina el numero superior de la cola
//Entrada: una cola y su largo
//Salida: una cola
int* sacar(int* cola,int* largo){
	if(*largo<=1){
		*largo=0;
		return (int*)malloc(sizeof(int));
	}
	else{
		int* aux= (int*)malloc(sizeof(int)*(*largo-1));
		*largo=*largo-1;
		for(int i=0;i<*largo;i++){
			aux[i]=cola[i+1];
		}
		
		return aux;
	}
}


int esConexo(MatrizGrafo* matriz){
    int* cola= (int*) malloc(sizeof(int));
	int largo=0;
    int inicio = 0;
	int* visitados=(int*)malloc(sizeof(int)*matriz->vertices);
    for(int i=0;i<matriz->vertices;i++){
		visitados[i]=0;
	}
	cola = push(cola,&largo, inicio);
	while(largo > 0){
		int index = cola[0];
		cola = sacar(cola,&largo);
		if(visitados[index] = 0){
			continue;
		}
		else{
			visitados[index] = 1;
			for(int i = 0; i < matriz->vertices; i++){
				if(matriz->adyacencias[index][i] > 0 && visitados[i] == 0){
					cola = push(cola, &largo, i);
				}
			}
		}
	}
	
	for(int i = 0; i < matriz->vertices; i++){
		if(visitados[i] != 1){
			return 0;
			
		}
	}
	return 1;
    
}