/**
*	@file 	main.c
*	@brief	Contém a função main do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "erro.h"
#include "log.h"
#include "graph.h"
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
	// "grafo", lista de vertices
	VertexList *lista = NULL;

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
		// Vertex *teste = busca_vertice( lista, identificador);
		// if (teste != NULL)
		// 	printf("\tValor encontrado: %d \n", teste -> V );
		// printf("Lista %p\n", logs);
		
		if (operacao != 'C'){
			//TODO se for o caso, fazer aqui a verificação para reiniciar o log e os vértices
				

			logs = insereLog(logs, tempo, identificador, operacao, atributo);
			int testeConflito = buscaConflito(logs);
			if (testeConflito == -1)
				printf("Nao possui conflitos \n");
			else{
				// printf("%d tem conflito com %d \n", logs -> tail -> id, testeConflito);
				criaArco(busca_vertice(lista, testeConflito), busca_vertice(lista, logs->tail->id));
			}
		} else{
			bool tem_ciclo = verifica_ciclo(lista);
			// printf("tem ciclo: %d \n", tem_ciclo);
			imprimeLogs( logs, f);

			printf("Lista: \n");
			if (logs != NULL && lista != NULL)
				equivalente(lista, logs);
			// bool ehCiclico = verifica_ciclo(lista);
			// printf("commit %s\n\n", ehCiclico?"true":"false");

			// !Posteriormente criar rotinas pra dar free nos ponteiros
			logs = NULL;
			lista = NULL;
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