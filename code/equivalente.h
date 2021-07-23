/**
 * @file equivalente.h
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo contendo funções para verificar se um agendamento possui visão equivalente
 * caso permutemos suas transações.
 * @version 1.0
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __EQUIVALENTE__
#define __EQUIVALENTE__

#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "graph.h"

/**
 * @brief Realiza a troca de valores entre dois inteiros
 * 
 * @param x Inteiro que ao final da execução passa a ter o valor de y
 * @param y Inteiro que ao final da execução passa a ter o valor de x
 */
void troca(int *x, int *y);

/**
 * @brief Busca a última escrita realizada no atributo dado 
 * 
 * @param S O agendamento para realizar a busca
 * @param atributo O atributo para ser buscado no agendamento S
 * @return int O identificador de T_k em que ocorre a última escrita do atributo  
 * @return -1 Caso o atributo não possua uma escrita neste agendamento
 */
int ultimaEscrita(ListaLog *S, char atributo);

/**
 * @brief Busca a última escrita em T_k do atributo que foi lido por T_i
 * 
 * @param L Log de T_i do agendamento em que será feita a busca
 * @return int O identificador de T_k 
 * @return -1 Caso não exita um T_k satisfaz a codição
 */
int escritaAnterior(Log *L);

/**
 * @brief Verifica se os agendamentos S e S' são ditos visão equivalentes
 * 
 * @param S O agendamento S a ser comparado
 * @param S_linha O agendamento S' a ser comparado
 * @return true Os agendamentos são equivalentes
 * @return false Os agendamentos não são equivalentes
 */
bool comparaAgendamentos(ListaLog *S, ListaLog *S_linha);

/**
 * @brief Cria um agendamento S' com base no agendamento S e no vetor que determine a ordem das transações de S'  
 * 
 * @param size O tamanho do vetor A
 * @param A O vetor que possui a ordem das transações que serão usadas no agendamento criado
 * @param S Os logs do agendamento S que servirão de base para S'
 * @return ListaLog* Os logs do agendamento S' criado
 */
ListaLog *criaAgendamento(int size, int *A, ListaLog *S);

/**
 * @brief Algoritmo recursivo que gera as n! permutações S' do agendamento S com base no Algoritmo de Heap 
 * e verifica se existe algum S' e S de visão equivalentes
 * 
 * @param size O número de transações a serem permutadas
 * @param n O número em que serão geradas as n! permutações de S
 * @param A O vetor que possui a ordem das transações que serão usadas para criar as permutações de S 
 * @param S O agendamento S em que as permutações serão baseadas
 * @return true Caso exista uma permutação de S com visão equivalente a S
 * @return false Caso não exista uma permutação de S com visão equivalente a S
 */
bool generate(int size, int n, int *A, ListaLog *S);

/**
 * @brief Verifica se o agendamento S possui uma visão equivalente com a perpermutação de seus elementos
 * 
 * @param vertices Os vértices de cada nó do escalonamento de S
 * @param S O agendamento para realizar a busca de uma visão equivalente
 * @return true Caso exista uma visão equivalente
 * @return false Caso não exista uma visão equivalente
 */
bool equivalente(VertexList *vertices, ListaLog *S);

#endif