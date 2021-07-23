/**
 * @file equivalente.c
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo contendo funções para verificar se um agendamento possui visão equivalente
 * caso permutemos suas transações.
 * @version 1.0
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "equivalente.h"
#include "log.h"

/**
 * @brief Realiza a troca de valores entre dois inteiros
 * 
 * @param x Inteiro que ao final da execução passa a ter o valor de y
 * @param y Inteiro que ao final da execução passa a ter o valor de x
 */
void troca(int *x, int *y){
    int iterator;
    iterator = *x;
    *x = *y;
    *y = iterator;
}

/**
 * @brief Busca a última escrita realizada no atributo dado 
 * 
 * @param S O agendamento para realizar a busca
 * @param atributo O atributo para ser buscado no agendamento S
 * @return int O identificador de T_k em que ocorre a última escrita do atributo  
 * @return -1 Caso o atributo não possua uma escrita neste agendamento
 */
int ultimaEscrita(ListaLog *S, char atributo){
	Log *iterator = S -> tail;
	// retorna o id da ultima escrita
	while (iterator != NULL){
		if (atributo == iterator -> atributo && iterator -> operacao == 'W')
			return iterator -> id;
		
		iterator = iterator -> prev;
	}

	// se nao retorna -1
	return -1;
}

/**
 * @brief Busca a última escrita em T_k do atributo que foi lido por T_i
 * 
 * @param L Log de T_i do agendamento em que será feita a busca
 * @return int O identificador de T_k 
 * @return -1 Caso não exita um T_k satisfaz a codição
 */
int escritaAnterior(Log *L){
	Log *iterator = L;
	// retorna o id da ultima escrita do atributo de L onde o T_i != T_j seja diferente
	while (iterator != NULL){
		if (iterator -> atributo == L -> atributo && iterator -> operacao == 'W' && iterator -> id != L -> id)
			return iterator -> id;
		
		iterator = iterator -> prev;
	}

	// se nao tiver escrita em T_j != T_j
	return -1;
}

/**
 * @brief Verifica se os agendamentos S e S' são ditos visão equivalentes
 * 
 * @param S O agendamento S a ser comparado
 * @param S_linha O agendamento S' a ser comparado
 * @return true Os agendamentos são equivalentes
 * @return false Os agendamentos não são equivalentes
 */
bool comparaAgendamentos(ListaLog *S, ListaLog *S_linha){
	char *array_atributos = malloc(S -> size);
	int tam_array = 0;
	Log *iterator = S -> head;
	// adiciona na string os diferentes atributos 
	while (iterator != NULL){
		bool insere = true;
		for (int i = 0; i < tam_array; i++){
			if (array_atributos[i] == iterator -> atributo){
				insere = false;
				break;
			}
		}
		if (insere == true){
			array_atributos[tam_array] = iterator -> atributo;
			tam_array++;
		}
		iterator = iterator -> next;
	}

	// terceira condicao: check se ultimo W em cada atributo sao no mesmo T_i
	for (int i = 0; i < tam_array; i++){
		if (ultimaEscrita(S, array_atributos[i]) != ultimaEscrita(S_linha, array_atributos[i])){
			return false;	
		}
	}

	iterator = S -> head;
	// Log *aux = S -> head;
	// segunda condicao: busca o T_j da ultima escrita do atributo T_i de S e compara com o Tj de S'
	while (iterator != NULL){
		Log *aux = S_linha -> head;
		// encontra uma leitura em S
		if (iterator -> operacao == 'R'){
			while (iterator -> tempo != aux -> tempo)
				aux = aux -> next;
			if (escritaAnterior(aux) != escritaAnterior(iterator)){
				return false;	
			}
		}

		iterator = iterator -> next;
	}
	return true;
}

/**
 * @brief Cria um agendamento S' com base no agendamento S e no vetor que determine a ordem das transações de S'  
 * 
 * @param size O tamanho do vetor A
 * @param A O vetor que possui a ordem das transações que serão usadas no agendamento criado
 * @param S Os logs do agendamento S que servirão de base para S'
 * @return ListaLog* Os logs do agendamento S' criado
 */
ListaLog *criaAgendamento(int size, int *A, ListaLog *S){
	ListaLog *S_linha = NULL;
	Log *iterator;
	// percorre cada 
	for (int i = 0; i < size; i++){
		iterator = S -> head;
		while(iterator  != NULL){
			if (A[i] == iterator -> id){
				S_linha = insereLogFinal(S_linha, iterator -> tempo, iterator -> id, iterator -> operacao, iterator -> atributo);
			}
			iterator = iterator -> next;
		}
	}
	
	return S_linha;
}

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
bool generate(int size, int n, int *A, ListaLog *S){
	
	if (1 == n){
		ListaLog *S_linha = criaAgendamento(size, A, S);
		return comparaAgendamentos(S, S_linha);
	}
    else {
		for (int i = 0; i < n  ; i++){
			bool teste = generate(size, n - 1, A, S);
			if (teste)
				return true;
			if (n % 2 == 0){
				troca(&A[i], &A[n-1]);
			}
			else {
				troca(&A[0], &A[n-1]);
			}
		}
	}

	return false;
}

/**
 * @brief Verifica se o agendamento S possui uma visão equivalente com a perpermutação de seus elementos
 * 
 * @param vertices Os vértices de cada nó do escalonamento de S
 * @param S O agendamento para realizar a busca de uma visão equivalente
 * @return true Caso exista uma visão equivalente
 * @return false Caso não exista uma visão equivalente
 */
bool equivalente(VertexList *vertices, ListaLog *S){
	VertexList *iterator = vertices;
	int tam_vertices = 0;
	// conta o num. de vertices
	while (iterator != NULL){
		iterator = iterator -> next;
		tam_vertices++;
	}

	// cria o array com base no num. de vertices 
	int *arrayVertices = (int *)malloc(sizeof(int)* tam_vertices);
	iterator = vertices;
	int i = 0;
	// adiciona os valores dos vertices no array
	while (iterator != NULL){
		arrayVertices[i] = iterator -> vertice -> V;
		iterator = iterator -> next;
		i++;
	}
	
	return generate(tam_vertices, tam_vertices, arrayVertices, S);
}
