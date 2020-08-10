#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "struct.h"

MatrizGrafo** agregarEstado(MatrizGrafo** lista, int * elementos, MatrizGrafo* estado);
MatrizGrafo** sacarElemento(MatrizGrafo** lista, int * elementos);
int sonIguales(MatrizGrafo* matriz1, MatrizGrafo* matriz2);
int esSolucionRepetida(MatrizGrafo** soluciones, int* canSoluciones, MatrizGrafo* solucion);
MatrizGrafo** generarHijos(MatrizGrafo** abiertos, int* canAbiertos, MatrizGrafo* padre);
void freeLista(MatrizGrafo** lista, int* tamano);
MatrizGrafo** backTracking(MatrizGrafo** abiertos, MatrizGrafo** cerrados, MatrizGrafo** soluciones,int* canAbiertos, int* canCerrados, int* canSoluciones, MatrizGrafo* inicial);
int seleccionarMejorSolucion(MatrizGrafo** soluciones,int *canSoluciones);
MatrizGrafo* algoritmo(char const* entrada);
#endif