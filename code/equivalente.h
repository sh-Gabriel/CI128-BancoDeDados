/**
*	@file 	main.c
*	@brief	Contém a função main do programa
*/
#ifndef __EQUIVALENTE__
#define __EQUIVALENTE__

#include <stdio.h>
#include <stdlib.h>
// #include "erro.c"
#include "log.h"

bool equivalente(VertexList *vertices, ListaLog *logs);

bool generate(int size, int n, int *A, ListaLog *S);

bool comparaAgendamentos(ListaLog *S, ListaLog *S_linha);
// int* generate(int size, int n, int *A, ListaLog *logs);

#endif