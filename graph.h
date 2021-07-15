#ifndef __GRAPH__
#define __GRAPH__"
#include <stdio.h>
#include <stdlib.h>
#include "erro.c"
#include <stdbool.h>
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

Graph *inicia_grafo();

VertexList *adiciona_lista_vertices(Vertex *v);

/**
 * Adiciona um vértice na lista que contém os vértices (transações) atuais
 * -Desconsidera arcos
*/
void adiciona_vertice(Graph *g, int vertex_key);

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
Vertex *busca_vertice(Graph *g, int chave);


// verifica_ciclo

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

#endif