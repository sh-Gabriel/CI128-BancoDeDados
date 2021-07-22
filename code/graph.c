#include "graph.h"
/**
 * Inicializa uma lista de vértices que conterá todos os vértices criados,
 * e não leva em consideração a vizinhança deles.
 * @param v O primeiro vértice que a lista irá conter.
 * @retval A lista inicializada.
 */
VertexList *adiciona_lista_vertices(Vertex *v){
    VertexList *lista = (VertexList *)malloc(sizeof(VertexList));
    lista->next = NULL;
    lista->vertice = v;
    return lista;
}

/**
 * Adiciona um vértice na lista que contém os vértices (transações) atuais
 * -Desconsidera arcos
 * @param list 			A lista de vertices do grafo
 * @param vertex_key 	A 'chave' do vértice que será criado
 * @retval A lista de vertices ajustada ou NULL caso nao seja possivel cria-la
*/
VertexList *adiciona_vertice(VertexList *list, int vertex_key){
    if(list == NULL){
		list = inicia_lista_vertice(vertex_key);
		return list;
    }
	// retorna caso o valor ja exista
	VertexList *iterator = list;
	
	while(iterator -> next != NULL){
		if (iterator -> vertice -> V == vertex_key)
			return list;
		iterator = iterator -> next;
	}
	if (iterator -> vertice -> V == vertex_key){
		return list;
	}
	// adiciona novo nodo na lista 
	VertexList *aux = inicia_lista_vertice(vertex_key);
	if (aux == NULL){
		imprimeErro("Erro ao criar nodo na lista de vertices");
		return NULL;
	}
	iterator -> next = aux;
    return list;
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
 * Inicia a lista de vértices com um recém criado.
 * @param vertex A chave do vértice a ser criado.
 * @retval O ponteiro para a lista.
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
 * Inicia a lista de vértices adjascentes de um vértice.
 * @param origem O vértice que terá sua lista iniciada.
 * @param destino O vértice que pertence à lista de adjascentes recém-criada.
*/
void inicia_adj(Vertex *origem, Vertex *destino){
    origem->adj = (ListaAdj*) malloc(sizeof(ListaAdj));
    origem->adj->destino = destino;
    origem->adj->next = NULL;
}

/**
 * Função que dado uma lista de vértices retorna aquele que contém a chave requerida.
 * @param list A lista de vértives existentes.
 * @param chave O valor do vértice buscado.
 * @retval A estrutura de dados abstrata contendo o vértice encontrado, NULL caso contrário.
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
 * Função para adicionar uma Arco a um vértice existente
 * 
 * @param origin    O grafo de origem da Arco.
 * @param destination O 'alvo'.
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
        inicia_adj(origin, destination);
        printf("Algo %p\n", origin->adj->destino);
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
 * Função que, dado um vértice, itera por sua vizinhança.
 * @param v O vértice, em questão, a ser explorado.
 * @retval True para a existência de ciclo e False caso o contrário.
*/
bool itera_adjascentes(Vertex *v){
    printf("Entrou %p, visitado %d\n", v, v->visitado);
    if(v == NULL){
        printf("Sem vizinhança\n");
        return false;
        imprimeErro("Não há uma vizinhança para ser percorrida na função itera_vizinhos");
    }
    bool result = false;
    if(v->visitado == 1){
        printf("%d o destino antes do return \n", v->V);
        //Existe ciclo
        return true;
    }
    if(v->visitado == 2){
        printf("Retornou falso??\n");
        //O vértice foi visitado e não teve ciclo
        return false;
    }
    v->visitado++;
    ListaAdj *iter = v->adj;
    while(iter != NULL && !result){
        printf("A chave de iter %d %d\n", iter->destino->V, iter->destino->visitado);
        result = itera_adjascentes(iter->destino);
        printf("Depois\n");
        iter = iter->next;
    }
    v->visitado++;
    return result;
}
/**
 * Função que verifica a existência de um ciclo em um grafo
 * @param list A lista de vértices (transações) existentes
 * @retval True para a existência de ciclo e False caso contrário
*/
bool verifica_ciclo(VertexList *list){
    VertexList *iterator = list;
    //iterando pela lista de vértices que temos
    while(iterator != NULL){
        //Se o vértice não foi visitado
        if(iterator->vertice->visitado == 0){
            //Se o vértice tem vizinhança
            if(iterator->vertice->adj != NULL){
                printf("A vizinhança é de %d\n", iterator->vertice->V);
                if (itera_adjascentes(iterator->vertice)){
                    return true;
                }
            }
        }
        iterator = iterator->next;
    }
    return false;
}


// int numVertices = (VertexList *list){
//     VertexList *iterator = list;
	
// }