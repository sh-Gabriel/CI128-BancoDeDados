/**
 * @file graph.h
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo header de graph.c
 * @version 1.0
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef __GRAPH__
#define __GRAPH__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "erro.h"


/*! \struct
 * @brief Estrutura para armazenar a vizinhança de um vértice
 * A vizinhança é dada por outras estruturas vértice, utilizada no algoritmo 1 para
 * buscar a existência de um ciclo no grafo gerado pelas transações
 */
typedef struct ListaAdj{
    struct Vertex *destino;
    struct ListaAdj *next;
} ListaAdj;

/*! \struct
 * @brief Estrutura para armazenar as informações de um vértice gerado pelas transações
 * Composta pela chave do vértice, um valor que representa se ele foi visitado ou percorrido,
 * uma flag para saber se a transação representada pelo vértice sofreu commit e a vizinhança
 * do vértice
 */
typedef struct Vertex{
    int V;
    int visitado;
    bool commitado;
    struct ListaAdj *adj;
    
} Vertex;

/*! \struct
 * @brief Estrutura para armazenar a lista de vértices criadas pela leitura da entrada
 * Utilizada para saber quais são os vértices existentes a serem verificados na busca de 
 * ciclos do algoritmo 1
 */
typedef struct VertexList{
    struct Vertex *vertice;
    struct VertexList *next;
} VertexList;

/**
 * @brief Adiciona um vértice na lista de vértices
 * 
 * @param lista A lista que será incrementada
 * @param v A chave do vértice que será adicionado na lista
 */
void adiciona_vertice_lista(VertexList *lista, int v);

/**
 * @brief Faz as verificações para adicionar um vértice na lista que contém os vértices (transações) atuais
 * 
 * @param list A lista de vertices do grafo
 * @param vertex_key A 'chave' do vértice que será criado
 * @return VertexList* A lista de vertices ajustada ou NULL caso nao seja possivel cria-la
 */
VertexList *adiciona_vertice(VertexList *list, int vertex_key);

/**
 * @brief Aloca memória para uma unidade da estrutura de dados que representa um vértice
 * 
 * @param vertex A chave do vértice que será criado
 * @return Vertex* O ponteiro para a estrutura recém-alocada
 */
Vertex *cria_vertice(int vertex);

/**
 * @brief Inicia a lista de vértices, já contendo um vértice inserido nela
 * 
 * @param vertex A chave do vértice que será criado
 * @return VertexList* O ponteiro referência para o começo da lista
 */
VertexList *inicia_lista_vertice(int vertex);

/**
 * @brief Inicia a lista de vértices adjascentes de um vértice
 * 
 * @param origem O vértice que terá sua lista de adjascentes iniciada
 * @param destino O vértice que fará parte da lista de adjascentes
 */
void inicia_adj(Vertex *origem, Vertex *destino);

// funcao_commit em algum lugar aí 


/**
 * @brief Dado uma lista de vértices, retorna aquele que contém a chave buscada
 * 
 * @param list A lista de vértices existente
 * @param chave A chave do vértice a ser buscado
 * @return Vertex* O vértice encontrado ou NULL, caso não o encontre
 */
Vertex *busca_vertice(VertexList *list, int chave);

/**
 * @brief Adiciona um arco entre dois vértices existentes
 * 
 * @param origin O vértice de origem do arco
 * @param destination O vértice de destino do arco
 */
void criaArco(Vertex *origin, Vertex *destination);

/**
 * @brief Dado um vértice, itera por sua vizinhança verificando a existência de ciclo
 * 
 * @param v O vértice cuja vizinhança será percorrida
 * @return true Caso exista um ciclo
 * @return false Caso contrário
 */
bool itera_adjascentes(Vertex *v);

/**
 * @brief Verifica a existência de um ciclo em um grafo
 * 
 * @param list A atual lista de vértices criados
 * @return true Caso exista ciclo
 * @return false Caso contrário
 */
bool verifica_ciclo(VertexList *list);

/**
 * @brief Percorre a lista de vértices verificando se todas as transações dos vértices já sofreram commit
 * 
 * @param list A lista de vértices existente no agendamento
 * @return true Todos sofreram o commit
 * @return false Algum ainda não sofreu o commit
 */
bool verifica_commit(VertexList *list);


/**
 * @brief Usar free em todas as esturturas referentes à vértices alocadas até então
 * 
 * @param lista A lista de vértices que será liberada
 */
void *finaliza_lista_vertices(VertexList *lista);

#endif