/**
 * @file graph.c
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo contendo as esturturas e funções relacionadas à criação de uma lista de
 * vértices, criada conforme transações são lidas. Utilizada para o Algoritmo de teste de 
 * seriabilidade quanto ao conflito
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "graph.h"

/**
 * @brief Adiciona um vértice na lista de vértices
 * 
 * @param lista A lista que será incrementada
 * @param v A chave do vértice que será adicionado na lista
 */
void adiciona_vertice_lista(VertexList *lista, int v){
    if (lista == NULL)
        imprimeErro("A lista passada para a função adiciona_vertice_lista é nula");
    lista->next = (VertexList *)malloc(sizeof(VertexList));
    lista->next->next = NULL;
    lista->next->vertice = cria_vertice(v);
}

/**
 * @brief Faz as verificações para adicionar um vértice na lista que contém os vértices (transações) atuais
 * 
 * @param list A lista de vertices do grafo
 * @param vertex_key A 'chave' do vértice que será criado
 * @return VertexList* A lista de vertices ajustada ou NULL caso nao seja possivel cria-la
 */
VertexList *adiciona_vertice(VertexList *list, int vertex_key){
    if(list == NULL){
		list = inicia_lista_vertice(vertex_key);
		return list;
    }
	
	// retorna caso o valor ja exista
	VertexList *iterator = list;

    while(iterator->next != NULL){
        if (iterator -> vertice -> V == vertex_key){
            return list;
        }
        iterator = iterator->next;

	}
    if(iterator->vertice->V != vertex_key)
        adiciona_vertice_lista(iterator, vertex_key);

    return list;
}

/**
 * @brief Aloca memória para uma unidade da estrutura de dados que representa um vértice
 * 
 * @param vertex A chave do vértice que será criado
 * @return Vertex* O ponteiro para a estrutura recém-alocada
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
 * @brief Inicia a lista de vértices, já contendo um vértice inserido nela
 * 
 * @param vertex A chave do vértice que será criado
 * @return VertexList* O ponteiro referência para o começo da lista
 */
VertexList *inicia_lista_vertice(int vertex){
	VertexList *aux = (VertexList*) malloc(sizeof(VertexList));
	if (aux == NULL)
		return NULL;
	aux -> vertice = cria_vertice(vertex);
	if (aux -> vertice == NULL)
		return NULL;
	aux -> next = NULL;

	return aux;
}

/**
 * @brief Inicia a lista de vértices adjascentes de um vértice
 * 
 * @param origem O vértice que terá sua lista de adjascentes iniciada
 * @param destino O vértice que fará parte da lista de adjascentes
 */
void inicia_adj(Vertex *origem, Vertex *destino){
    origem->adj = (ListaAdj*) malloc(sizeof(ListaAdj));
    origem->adj->destino = destino;
    origem->adj->next = NULL;
}

/**
 * @brief Dado uma lista de vértices, retorna aquele que contém a chave buscada
 * 
 * @param list A lista de vértices existente
 * @param chave A chave do vértice a ser buscado
 * @return Vertex* O vértice encontrado ou NULL, caso não o encontre
 */
Vertex *busca_vertice(VertexList *list, int chave){
    if (list == NULL){
        imprimeErro("Um grafo não existente foi passado para a função busca_vertice");
    }
    
	VertexList *iterator = list;
    while(iterator != NULL){
		if (iterator -> vertice -> V == chave)
			return iterator -> vertice;
        iterator = iterator -> next;
    }
	
    
	/*Não encontrou o vértice*/
    fprintf(stderr, "\tVértice não foi encontrado na função busca_vertice\n");
    return NULL;
}

/**
 * @brief Adiciona um arco entre dois vértices existentes
 * 
 * @param origin O vértice de origem do arco
 * @param destination O vértice de destino do arco
 */
void criaArco(Vertex *origin, Vertex *destination){
    if(origin == NULL){
        imprimeErro("O vértice de origem passado para a função criaArco é nulo.");
    }
    /*o grafo não tem Arcos*/
    if(origin->adj == NULL){
        /*inicia a lista de Arcos dele*/
        inicia_adj(origin, destination);
    } else {
        ListaAdj *iter = origin->adj;
        while(iter->next != NULL){
            iter = iter->next;
        }
        iter->next = (ListaAdj *)malloc(sizeof(ListaAdj));
        iter->next->next = NULL;
        iter->next->destino = destination;
    }
}

/**
 * @brief Dado um vértice, itera por sua vizinhança verificando a existência de ciclo
 * 
 * @param v O vértice cuja vizinhança será percorrida
 * @return true Caso exista um ciclo
 * @return false Caso contrário
 */
bool itera_adjascentes(Vertex *v){
    if(v == NULL){
        return false;
    }
    bool result = false;
    if(v->visitado == 1){
        //Existe ciclo
        return true;
    }
    if(v->visitado == 2){
        //O vértice foi visitado e não teve ciclo
        return false;
    }
    v->visitado++;
    ListaAdj *iter = v->adj;
    while(iter != NULL && !result){
        result = itera_adjascentes(iter->destino);
        iter = iter->next;
    }
    v->visitado++;
    return result;
}

/**
 * @brief Verifica a existência de um ciclo em um grafo
 * 
 * @param list A atual lista de vértices criados
 * @return true Caso exista ciclo
 * @return false Caso contrário
 */
bool verifica_ciclo(VertexList *list){
    VertexList *iterator = list;
    //iterando pela lista de vértices que temos
    while(iterator != NULL){
        //Se o vértice não foi visitado
        if(iterator->vertice->visitado == 0){
            //Se o vértice tem vizinhança
            if(iterator->vertice->adj != NULL){
                if (itera_adjascentes(iterator->vertice)){
                    return true;
                }
            }
        }
        iterator = iterator->next;
    }
    return false;
}

/**
 * @brief Percorre a lista de vértices verificando se todas as transações dos vértices já sofreram commit
 * 
 * @param list A lista de vértices existente no agendamento
 * @return true Todos sofreram o commit
 * @return false Algum ainda não sofreu o commit
 */
bool verifica_commit(VertexList *list){
    if (list == NULL)
        imprimeErro("Uma lista nula foi passada para a função verifica_commit");
    VertexList *iterator = list;
    while(iterator != NULL){
        if (!iterator->vertice->commitado)
            return false;
        iterator = iterator->next;
    }
    return true;
}

/**
 * @brief Usar free em todas as esturturas referentes à vértices alocadas até então
 * 
 * @param lista A lista de vértices que será liberada
 */
void *finaliza_lista_vertices(VertexList *lista){
    if (lista == NULL)
        return NULL;
    VertexList *aux = lista;
    while (lista != NULL){
        aux = lista;
        lista = lista->next;
        free(aux->vertice->adj);
        free(aux->vertice);
        free(aux);
    }
    return NULL;
}

