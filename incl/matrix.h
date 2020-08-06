#ifndef MATRIX_H
#define MATRIX_H

#include "struct.h"

MatrizGrafo* generarMatrizGrafo(int vertices);
void imprimirMatrizAdyacencia(MatrizGrafo* matriz);
MatrizGrafo* abrirArchivoMatriz(char *nombreArchivo);
MatrizGrafo* eliminarCamino(int k, int l, MatrizGrafo* matrix);
MatrizGrafo* copiarMatriz(MatrizGrafo* aCopiar);
void freeMatriz(MatrizGrafo* matriz);

#endif