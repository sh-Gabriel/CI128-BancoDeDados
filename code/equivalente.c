#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "equivalente.h"
#include "log.h"


void troca(int *x, int *y){
    int iterator;
    iterator = *x;
    *x = *y;
    *y = iterator;
}

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

ListaLog *criaAgendamento(int size, int *A, ListaLog *logs){
	ListaLog *S_linha = NULL;
	Log *iterator;
	// percorre cada 
	for (int i = 0; i < size; i++){
		iterator = logs -> head;
		while(iterator  != NULL){
			if (A[i] == iterator -> id){
				S_linha = insereLogFinal(S_linha, iterator -> tempo, iterator -> id, iterator -> operacao, iterator -> atributo);
			}
			iterator = iterator -> next;
		}
	}
	
	return S_linha;
}


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

	return 0;
}

bool equivalente(VertexList *vertices, ListaLog *logs){
	VertexList *iterator = vertices;
	int tam_vertices = 0;
	// conta o num. de vertices
	while (iterator != NULL){
		iterator = iterator -> next;
		tam_vertices++;
	}

	// conta o num. de vertices
	int *arrayVertices = (int *)malloc(sizeof(int)* tam_vertices);
	iterator = vertices;
	int i = 0;
	// adiciona os valores dos vertices no array
	while (iterator != NULL){
		arrayVertices[i] = iterator -> vertice -> V;
		iterator = iterator -> next;
		i++;
	}
	
	return generate(tam_vertices, tam_vertices, arrayVertices, logs);
}
