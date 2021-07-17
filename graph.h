/**
*	@file 	graph.h
*	@brief	Biblioteca de graph.c
*/
#ifndef __GRAPH__
#define __GRAPH__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "erro.h"

typedef struct ListaAdj{
    struct Vertex *destino;
    struct ListaAdj *next;
} ListaAdj;
//Lista de adjascentes de um vértice
typedef struct Adjascentes{
    struct ListaAdj *head;
    struct ListaAdj *tail;
} Adjascentes;

// T1 T2
// Vertice *T1 = inicia_grafo(1);


//Unidade vértice
typedef struct Vertex{
    int V;
    int visitado;
    bool commitado;
    struct Adjascentes *adj;
    
} Vertex;

typedef struct VertexList{
    struct Vertex *vertice;
    struct VertexList *next;
} VertexList;

//lista que contém os vértices existentes; não considera arcos
typedef struct Graph{
    struct VertexList *lista;
} Graph;

/**
 * Adiciona um vértice na lista que contém os vértices (transações) atuais de valor NULL
 * -Desconsidera arcos
*/
Graph *inicia_grafo();

/**
 * Adiciona um vértice na lista que contém os vértices (transações) atuais
 * -Desconsidera arcos
*/
VertexList *cria_nodo_lista(int);


/**
 * Adiciona um vértice na lista que contém os vértices (transações) atuais
 * -Desconsidera arcos
*/
VertexList *adiciona_vertice(VertexList *list, int vertex_key);

/**
 * Criar uma unidade da estrutura de dados que representa um vértice
 * @param vertex A 'chave' do vértice que será criado
 * @retval A estrutura criada e ajustada
*/
Vertex *cria_vertice(int vertex);

/**
 * Inicia a lista de vértices adjascentes a um vértice
*/
void inicia_adj(Vertex *grafo);

// funcao_commit em algum lugar aí 


// busca_vertice(int chave) se retornar NULL cria_vertice(); senão, retorna o vertice
// indice do "alvo"
Vertex *busca_vertice(VertexList *list, int chave);


// Vertex *busca_grafo(){

// }

/**
 * Função para adicionar uma Arco a um vértice existente
 * 
 * @param origin    O grafo de origem da Arco
 * @param destination O 'alvo'
 * 
 * if(condições){
 *  criaArco(Ti, j);
 * }
*/
void criaArco(Vertex *origin, Vertex *destination);

bool itera_vizinhos(ListaAdj *adj);

#endif