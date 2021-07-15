#ifndef __GRAPH__
#define __GRAPH__"
#include <stdio.h>
#include <stdlib.h>
#include "erro.c"

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
};

//lista que contém os vértices existentes; não considera arcos
typedef struct Graph{
    struct VertexList *lista;
} Graph;

Graph *inicia_grafo(){
    Graph *g = (Graph*) malloc(sizeof(Graph));
    g->lista = NULL;
    return g;
}

VertexList *adiciona_lista_vertices(Vertex *v){
    VertexList *lista = (VertexList *)malloc(sizeof(VertexList));
    lista->next = NULL;
    lista->vertice = v;
    return lista;
}

/**
 * Adiciona um vértice na lista que contém os vértices (transações) atuais
 * -Desconsidera arcos
*/
void adiciona_vertice(Graph *g, int vertex_key){
    if(g == NULL){
        imprimeErro("O grafo passado para a função adiciona_vertice é nulo");
    }

    Vertex *vertex = cria_vertice(vertex_key);

    if(g->lista == NULL){
        g->lista = adiciona_lista_vertices(vertex);
    } else {
        VertexList *iterator = g->lista;
        while(iterator->next != NULL){
            iterator = iterator->next;
        }
        iterator->next = adiciona_lista_vertices(vertex);
    }
}

/**
 * Criar uma unidade da estrutura de dados que representa um vértice
 * @param vertex A 'chave' do vértice que será criado
 * @retval A estrutura criada e ajustada
*/
Vertex *cria_vertice(int vertex){
    Vertex *aux = (Vertex*) malloc(sizeof(Vertex));
    aux->V = vertex;
    aux->adj = NULL;
    aux->visitado = 0;
    aux->commitado = 0;

    return aux;
}

/**
 * Inicia a lista de vértices adjascentes a um vértice
*/
void inicia_adj(Vertex *grafo){
    grafo->adj = (Adjascentes*) malloc(sizeof(Adjascentes));
    grafo->adj->head = (ListaAdj*) malloc(sizeof(ListaAdj));
    grafo->adj->head->next = NULL;
    grafo->adj->tail = grafo->adj->head;
}

// funcao_commit em algum lugar aí 


// busca_vertice(int chave) se retornar NULL cria_vertice(); senão, retorna o vertice
// indice do "alvo"
Vertex *busca_vertice(Graph *g, int chave){
    if (g == NULL){
        imprimeErro("Um grafo não existente foi passado para a função busca_vertice");
    }
    VertexList *iterator = g;
    while(iterator != NULL){
        if(iterator->vertice->V == chave){
            return iterator->vertice;
        }
        iterator = iterator->next;
    }
    /*Não encontrou o vértice*/
    fprintf(stderr, "Vértice não foi encontrado na função busca_vertice");
    return NULL;
}


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
void criaArco(Vertex *origin, Vertex *destination){
    if(origin == NULL){
        imprimeErro("O vértice de origem passado para a função criaArco é nulo.");
    }
    /*o grafo não tem Arcos*/
    if(origin->adj == NULL){
        /*inicia a lista de Arcos dele*/
        inicia_adj(origin);
    } else {
        /*O grafo tem Arcos*/
        origin->adj->tail->next = (ListaAdj *)malloc(sizeof(ListaAdj));
        origin->adj->tail = origin->adj->tail->next;
    }

    origin->adj->tail->destino = destination;
    origin->adj->tail->next = NULL;
}

#endif