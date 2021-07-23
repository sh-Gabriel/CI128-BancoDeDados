/**
 * @file log.c
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo contendo as esturturas e funções relacionadas à criação de uma lista de
 * logs, criada conforme transações são lidas. A log é armazenada em um arquivo "log.log" durante
 * a execução para que erros sejam debugados. A estura é utilizada para montar as visões referentes 
 * ao Algoritmo de visão equivalente
 * @version 1.0
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

/**
 * @brief Inicia a estrutura de dados ListaLog
 * 
 * @return ListaLog* O ponteiro para a estrutura recém-criada
 */
ListaLog *criaListaLog(void){
	ListaLog *aux = (ListaLog*) malloc(sizeof(ListaLog));
	if (aux == NULL)
		imprimeErro("Erro ao criar ListaLog\n");
	
	aux -> head = NULL;
	aux -> tail = NULL;
	aux -> size = 0;

	return aux;
}

/**
 * @brief Insete uma unidade de log recém-criada na lista de logs conforme o valor do tempo em que foi efetuada
 * 
 * @param time O tempo da transação recebida
 * @param identificador Um identificador único para cada log
 * @param op A operação da transação
 * @param atribute O atributo alvo da operação
 * @return ListaLog* A lista atualizada
 */
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

/**
 * @brief Insete uma unidade de log recém-criada no final da lista de logs (utilizda nas permutações geradas pelo algoritmo 2)
 * 
 * @param time O tempo da transação recebida
 * @param identificador Um identificador único para cada log
 * @param op A operação da transação
 * @param atribute O atributo alvo da operação
 * @return ListaLog* A lista atualizada
 */
ListaLog *insereLogFinal(ListaLog *lista, int time, int identificador, char op, char tribute){

	// log que sera inserido na lista:
	Log *newLog = criaLog(time, identificador, op, tribute);
	if (lista == NULL){
		lista = criaListaLog();
		lista -> head = newLog;
		lista -> tail = newLog;
		lista -> size++;
		return lista;
	}

	// insere no tail
	newLog -> prev = lista -> tail; 
	lista -> tail -> next = newLog;
	lista -> tail = newLog;
	lista -> size++;
	return lista;
}

/**
 * @brief Cria uma unidade da estrutura de dados abstrata "Log"
 * 
 * @param time O tempo da transação recebida
 * @param identificador Um identificador único para cada log (decidiu-se não usar o tempo como id único dada a possibilidade de erro e que duas transações
 * venham anotadas com o mesmo valor)
 * @param op A operação da transação
 * @param atribute O atributo alvo da operação
 * @return Log* O ponteiro para a estrutura criada
 */
Log *criaLog(int time, int identificador, char op, char atribute){
	Log *aux = (Log*) malloc(sizeof(Log));
	if (aux == NULL)
		imprimeErro("Erro ao criar Log\n");

	aux -> prev = NULL;
	aux -> next = NULL;
	aux -> tempo = time;
	aux -> id = identificador;
	aux -> operacao = op;
	aux -> atributo = atribute;

	return aux;
}

/**
 * @brief Percorre a lista de logs e verifica a ocorrência de conflito entre a última transição lida com as demais
 * 
 * @param lista A lista de logs após a insersão da nova transação
 * @return int O id da operação, caso um conflito tenha ocorrido, -1 caso contrário
 */
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

/**
 * @brief Imprime a lista de logs atualmente criada no programa
 * 
 * Fora de uso. Caso queira utilizá-la, chame-a na main ou em alguma função que esteja usando uma lista do tipo
 * "ListaLog" e forneça um ponteiro para o arquivo que será escrito.
 * 
 * @param lista A lista de logs
 * @param f O arquivo em que as logs serão escritas
 */
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
 * @return void* O ponteiro para a lista esvaziada (NULL)
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