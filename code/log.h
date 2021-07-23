/**
 * @file log.h
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo header de log.c
 * @version 1.0
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __LOG__
#define __LOG__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*! \struct
 * @brief Estrutura para armazenar inicio e fim da lista de logs
 */
typedef struct ListaLog{ 
    struct Log *head;
    struct Log *tail;
    int size;
} ListaLog;

/**
 * Estrutura de dados para cada nodo da lista de logs
*/
/*! \struct
 * @brief Estrutura para representar os nodos da lista de logs 
 * É duplamente encadeada, e em relação à transação que representa, contém
 * o tempo em que ela foi executada, o id, a operação executada e o atributo
 * alvo da operação
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
 * @brief Inicia a estrutura de dados ListaLog
 * 
 * @return ListaLog* O ponteiro para a estrutura recém-criada
 */
ListaLog *criaListaLog(void);

/**
 * @brief Insete uma unidade de log recém-criada na lista de logs conforme o valor do tempo em que foi efetuada
 * 
 * @param time O tempo da transação recebida
 * @param identificador Um identificador único para cada log
 * @param op A operação da transação
 * @param atribute O atributo alvo da operação
 * @return ListaLog* A lista atualizada
 */
ListaLog *insereLog(ListaLog *lista, int time, int identificador, char op, char tribute);

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
Log *criaLog(int time, int identificador, char op, char tribute);

/**
 * @brief Percorre a lista de logs e verifica a ocorrência de conflito entre a última transição lida com as demais
 * 
 * @param lista A lista de logs após a insersão da nova transação
 * @return int O id da operação, caso um conflito tenha ocorrido, -1 caso contrário
 */
int buscaConflito(ListaLog *lista);

/**
 * @brief Imprime a lista de logs atualmente criada no programa
 * 
 * Fora de uso. Caso queira utilizá-la, chame-a na main ou em alguma função que esteja usando uma lista do tipo
 * "ListaLog" e forneça um ponteiro para o arquivo que será escrito.
 * 
 * @param lista A lista de logs
 * @param f O arquivo em que as logs serão escritas
 */
void imprimeLogs(ListaLog *lista, FILE *f);

/**
 * @brief Usar free em todas as esturturas referentes à log alocadas até então
 * 
 * @param lista A lista de logs que será liberada
 * @return void* O ponteiro para a lista esvaziada (NULL)
 */
void *finaliza_lista_log(ListaLog *lista);

/**
 * @brief Insete uma unidade de log recém-criada no final da lista de logs (utilizda nas permutações geradas pelo algoritmo 2)
 * 
 * @param time O tempo da transação recebida
 * @param identificador Um identificador único para cada log
 * @param op A operação da transação
 * @param atribute O atributo alvo da operação
 * @return ListaLog* A lista atualizada
 */
ListaLog *insereLogFinal(ListaLog *lista, int time, int identificador, char op, char tribute);

#endif