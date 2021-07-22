/**
 * @file main.c
 * @author Gabriel S.H. & Vinícius V.T.S.
 * @brief Função chamada pelo usuário para execução do programa
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "erro.h"
#include "log.h"
#include "graph.h"
#include "output.h"
#include "equivalente.h"


/**
 * Função chamada pelo Sistema Operacional para execução do programa
 *
 * @param	argc	Número de argumentos da execução do programa
 * @param	argv	Vetor de strings dos argumentos de execução do programa 
 *
 * @retval	0		Caso o programa seja executado corretamente
 * @retval	-1		Caso seja encontrado um erro durante a execução do programa
 */
int main(int argc, char *argv[]){	 
	// string de cada linha a ser lida
	char line[1024];
	// lista dos logs;
	ListaLog *logs = NULL;
	
	Vertex *commited;
	// "grafo", lista de vertices
	VertexList *lista = NULL;

	bool isSerial, isEquivalent;
	int id_escalonamento = 0;

	FILE *f = fopen("logs", "w");
	if (f == NULL)
		imprimeErro("Erro ao criar arquivo\n");
	
	while (fgets(line, 1024, stdin)){
		
		// a cada iteração separa o atributo de de cada linha
		int tempo = atoi(strtok(line, " "));
		int identificador = atoi(strtok(NULL, " "));
		char operacao = strtok(NULL, " ")[0];
		char atributo = strtok(NULL, "\n")[0];

		lista = adiciona_vertice( lista, identificador);
		
		if (operacao != 'C'){
			//TODO se for o caso, fazer aqui a verificação para reiniciar o log e os vértices
				
			logs = insereLog(logs, tempo, identificador, operacao, atributo);
			int testeConflito = buscaConflito(logs);
			if (testeConflito != -1)
				criaArco(busca_vertice(lista, testeConflito), busca_vertice(lista, logs->tail->id));
			
		} else {
			commited = busca_vertice(lista, identificador);
			commited->commitado = true;
			if(verifica_commit(lista)){
				id_escalonamento++;
				
				isSerial = !verifica_ciclo(lista);
				isEquivalent = false;
				if (logs != NULL && lista != NULL)
					isEquivalent = equivalente(lista, logs);
				// TODO isEquivalent = visao_equivalente(...)
				print_output(lista, id_escalonamento, isSerial, isEquivalent, tamanho_lista(lista));
				logs = finaliza_lista_log(logs);
				lista = finaliza_lista_vertices(lista);
			}

		}
	}
	fclose(f);
	return 0;
}