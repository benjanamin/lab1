#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "struct.h"

int sonIguales(MatrizGrafo* matriz1, MatrizGrafo* matriz2);

Lista* generarHijos(Lista* cabeza, MatrizGrafo* padre);
void freeLista(MatrizGrafo** lista, int* tamano);
MatrizGrafo* backTracking(Lista* cabeza);
MatrizGrafo* algoritmo(char const* entrada);
int sePuedeEliminarCamino(MatrizGrafo* matriz,int i, int j);
int esReducible(MatrizGrafo* matrix);

Lista* crearNodo(MatrizGrafo* matriz);
Lista* agregarNodo(Lista* cabeza, Lista* nodo);
Lista* sacarNodo(Lista* cabeza);
#endif