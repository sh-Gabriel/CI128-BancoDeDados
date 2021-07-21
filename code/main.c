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
#include <string.h>
#include "log.h"
#include "erro.h"
#include "graph.h"
#include "output.h"

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
	char line[1024];
	// VertexList *lista = NULL;
	ListaLog *logs = NULL;
	Vertex *commited;
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
		char atributo = strtok(NULL, " ")[0];

		lista = adiciona_vertice( lista, identificador);

		percorreLogProximo(logs);
		if (operacao != 'C'){
			//TODO se for o caso, fazer aqui a verificação para reiniciar o log e os vértices
			logs = insereLog(logs, tempo, identificador, operacao, atributo);
			int testeConflito = buscaConflito(logs);
			if (testeConflito == -1)
				printf("Nao possui conflitos \n");
			else{
				criaArco(busca_vertice(lista, testeConflito), busca_vertice(lista, logs->tail->id));
			}
		} else {
			commited = busca_vertice(lista, identificador);
			commited->commitado = true;
			if(verifica_commit(lista)){
				id_escalonamento++;
				imprimeLogs( logs, f);
				isSerial = !verifica_ciclo(lista);
				isEquivalent = false;
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