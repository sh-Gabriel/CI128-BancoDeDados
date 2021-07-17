/**
*	@file 	main.c
*	@brief	Contém a função main do programa
*/
#ifndef __LOG__
#define __LOG__

#include <stdio.h>
#include <stdlib.h>
// #include "erro.c"
#include <stdbool.h>

//Lista duplamente encadeada para armazenar logs
typedef struct ListaLog{
    struct Log *head;
    struct Log *tail;
    struct Log *size;
} ListaLog;

typedef struct Log{
    struct Log *prev;
    int tempo;
    int id;
    char operacao;
    char atributo;
    struct Log *next;
} Log;


ListaLog *criaListaLog(void);

ListaLog *insereLog(ListaLog *lista, int time, int identificador, char op, char tribute);

Log *criaLog(int time, int identificador, char op, char tribute);

void percorreLogProximo(ListaLog *lista);

void percorreLogAnterior(ListaLog *lista);


#endif