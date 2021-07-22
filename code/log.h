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
#include "log.h"
#include "erro.h"
#include "graph.h"

/**
 * Estrutura de dados para armazenar inicio e fim da lista de logs
*/
typedef struct ListaLog{ 
    struct Log *head;
    struct Log *tail;
    int size;
} ListaLog;

/**
 * Estrutura de dados para cada nodo da lista de logs
*/
typedef struct Log{
    struct Log *prev;
    int tempo;
    int id;
    char operacao;
    char atributo;
    struct Log *next;
} Log;



/**
 * Inicializa a lista de logs vazia.
 * 
 * @retval A lista inicializada.
 */
ListaLog *criaListaLog(void);

/**
 * @brief Adiciona um novo nodo a lista de logs.
 * 
 * @param lista A lista de logs atual
 * @param time O tempo em que o novo log sera executado
 * @param identificador O identificador que o novo log tera
 * @param op A operacao que o novo log tera que executar
 * @param tribute O atributo que o novo log ira alterar
 *
 * @return ListaLog* a lista de logs atualizada com o novo log 
 */
ListaLog *insereLog(ListaLog *lista, int time, int identificador, char op, char tribute);

/**
 * @brief Inicializa um novo nodo para a lista de logs
 * 
 * @param time O tempo em que o novo nodo sera executado
 * @param identificador O identificador que o novo nodo tera
 * @param op A operacao que o novo nodo tera que executar
 * @param tribute O atributo que o novo nodo ira alterar
 *
 * @return Log* O novo nodo criado
 */
Log *criaLog(int time, int identificador, char op, char tribute);

/**
 * @brief Debug
 * 
 * @param lista 
 */
void percorreLogProximo(ListaLog *lista);

/**
 * @brief Debug
 * 
 * @param lista 
 */
void percorreLogAnterior(ListaLog *lista);

/**
 * @brief Percorre a lista de logs do fim para o inicio buscando conflitos para o algoritmo de
 * teste de seriabilidade com base no ultimo log adicionado
 * 
 * @param lista A lista de logs 
 * @return int Caso encontre um conflito, retona o valor do vertice conflitante. Caso contrario, retorna -1.
 */
int buscaConflito(ListaLog *lista);

void imprimeLogs(ListaLog *lista, FILE *f);

ListaLog *insereLogFinal(ListaLog *lista, int time, int identificador, char op, char tribute);

#endif