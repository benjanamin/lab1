#ifndef STRUCT_H
#define STRUCT_H
typedef struct Lista Lista;
typedef struct matrizGrafo {
	int vertices;
	int** adyacencias;
	int id;
	int idAnterior;
}MatrizGrafo;

struct Lista
{
	Lista* siguiente;
	MatrizGrafo* matriz;
	int largo;
};

#endif