#ifndef VISITAR_H
#define VISITAR_H

#include "struct.h"
int top(int* cola,int largo);
int* push(int* cola,int* largo,int numero);
int* sacar(int* cola,int* largo);
int esConexo(MatrizGrafo* matriz);
#endif