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

		// printf("Adicionando valor %d: \n", identificador);
		lista = adiciona_vertice( lista, identificador);
		// printf("Buscando valor %d: \n", identificador);
		Vertex *teste = busca_vertice( lista, identificador);
		if (teste != NULL)
		// printf("b");
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

	// Vertex *a1 = busca_vertice(lista, 1);
	// Vertex *a2 = busca_vertice(lista, 2);
	// Vertex *a3 = busca_vertice(lista, 3);
	// Vertex *a4 = busca_vertice(lista, 4);
	// criaArco(a1, a2);
	// criaArco(a3, a4);
	// criaArco(a2, a3);
	// criaArco(a3, a1);
	// criaArco(a2, a1);
	// printf("O destino do arco %d\n", a2->adj->destino->V);
	// bool a = verifica_ciclo(lista);
	// printf("O result?? %d\n", a);

	
	fclose(f);
	return 0;
}