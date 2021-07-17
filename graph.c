#include "graph.h"

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
		list = cria_nodo_lista(vertex_key);
		return list;
    }
	// retorna caso 
	VertexList *iterator = list;
	if (iterator -> vertice -> V == vertex_key){
		return list;
	}
	
	while(iterator -> next != NULL){
		// retorna caso o valor ja exista
		if (iterator -> vertice -> V == vertex_key)
			return list;
		iterator = iterator -> next;
	}
	// adiciona novo nodo na lista 
	VertexList *aux = cria_nodo_lista(vertex_key);
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

VertexList *cria_nodo_lista(int vertex){
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

bool itera_vizinhos(ListaAdj *adj){
    if(adj == NULL){
        imprimeErro("Não há uma vizinhança para ser percorrida na função itera_vizinhos");
    }
    ListaAdj *iter = adj;
    while(iter != NULL){
        if(adj->destino->visitado == 1){
            //Existe ciclo
            return true;
        }
        if(adj->destino->visitado == 2){
            //O vértice foi visitado e não teve ciclo
            return false;
        }
        adj->destino->visitado++;
        itera_vizinhos(adj->destino->adj->head);
        adj->destino->visitado++;
        iter = iter->next;
    }
    return false;
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
            if(iterator->vertice->adj != NULL && iterator->vertice->adj->head != NULL){
                if (itera_vizinhos(iterator->vertice->adj->head)){
                    return true;
                }
            }
        }
        iterator = iterator->next;
    }
    return false;
}
