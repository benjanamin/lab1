#ifndef STRUCT_H
#define STRUCT_H

typedef struct matrizGrafo {
	int vertices;
	int** adyacencias;
	int id;
	int idAnterior;
}MatrizGrafo;

#endif