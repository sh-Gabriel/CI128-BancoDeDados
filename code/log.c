/**
 * @file log.c
 * @author your name (you@domain.com)
 * @brief Arquivo contendo as esturturas e funções relacionadas à criação de uma lista d
 * logs, criada conforme transações são lidas. A log é armazenada em um arquivo "log.log" durante
 * a execução para que erros sejam debugados. A estura é utilizada para montar as visões referentes 
 * ao Algoritmo de visão equivalente
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "erro.h"

ListaLog *criaListaLog(void){
	ListaLog *aux = (ListaLog*) malloc(sizeof(ListaLog));
	if (aux == NULL)
		imprimeErro("Erro ao criar ListaLog\n");
	
	aux -> head = NULL;
	aux -> tail = NULL;
	aux -> size = 0;

	return aux;
}

ListaLog *insereLog(ListaLog *lista, int time, int identificador, char op, char tribute){

	// log que sera inserido na lista:
	Log *newLog = criaLog(time, identificador, op, tribute);
	if (lista == NULL){
		lista = criaListaLog();
		lista -> head = newLog;
		lista -> tail = newLog;
		lista -> size++;
		return lista;
	}

	Log *iterator = lista -> head;
	// insere no head
	if (time < iterator -> tempo){
		newLog -> next = iterator; 
		iterator -> prev = newLog; 
		lista -> head = newLog;
		lista -> size++;
		return lista;
	}

	// insere no meio
	while (iterator -> next != NULL){
		// printf("iterator: %d \n", iterator -> tempo);
		if (time < iterator -> tempo){
			iterator -> prev -> next = newLog;
			newLog -> prev = iterator -> prev;

			newLog -> next = iterator;
			iterator -> prev = newLog;

			lista -> size++;
			return lista;

		} 
		iterator = iterator -> next;
	}
	
	// insere no tail
	newLog -> prev = lista -> tail; 
	lista -> tail -> next = newLog;
	lista -> tail = newLog;
	lista -> size++;
	return lista;
}

Log *criaLog(int time, int identificador, char op, char tribute){
	Log *aux = (Log*) malloc(sizeof(Log));
	if (aux == NULL)
		imprimeErro("Erro ao criar Log\n");

	aux -> prev = NULL;
	aux -> next = NULL;
	aux -> tempo = time;
	aux -> id = identificador;
	aux -> operacao = op;
	aux -> atributo = tribute;

	return aux;
}

void percorreLogProximo(ListaLog *lista){
	if (lista == NULL)
		return;
	Log *aux = lista -> head;
	while (aux != NULL){
		printf("%d \n", aux -> tempo);
		aux = aux -> next;
	}
}

void percorreLogAnterior(ListaLog *lista){
	Log *aux = lista -> tail;
	while (aux != NULL){
		printf("%d \n", aux -> tempo);
		aux = aux -> prev;
	}
}

int buscaConflito(ListaLog *lista){
	Log *lastLog = lista -> tail;
	Log *iterator = lista -> tail -> prev;

	while (iterator != NULL){
		// seleciona operacoes no mesmo atributo em vertices diferentes
		if (iterator -> atributo == lastLog -> atributo && iterator -> id != lastLog -> id){
			// se o ultimo for read
			if (lastLog -> operacao == 'W')
				return (iterator -> id);
			if (lastLog -> operacao == 'R' && iterator -> operacao == 'W')
				return (iterator -> id);
		}
		iterator = iterator -> prev;
	}

	// caso nao encontre conflito
	return -1;
}

void imprimeLogs(ListaLog *lista, FILE *f){
	//* perde a lista de logs depois do 1o print (1a leitura de commit)
	if (lista == NULL)
		return;
	Log *aux = lista -> head;

	fprintf(f, "Log:\n");
	while(aux != NULL){
		fprintf(f, "%d %d %c %c \n", aux -> tempo, aux -> id, aux -> operacao, aux -> atributo);
		aux = aux -> next;
	}

}
/**
 * @brief Usar free em todas as esturturas referentes à log alocadas até então
 * 
 * @param lista A lista de logs que será liberada
 */
void *finaliza_lista_log(ListaLog *lista){
	if (lista == NULL)
		return NULL;
	Log *aux = lista->head;
	while(aux->next != NULL){
		aux = aux->next;
		free(aux->prev);
	}
	free(aux);
	free(lista);
	return NULL;

}