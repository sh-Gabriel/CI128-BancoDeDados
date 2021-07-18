/**
*	@file 	main.c
*	@brief	Contém a função main do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "erro.h"


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
	ListaLog *listaLog = NULL;

	while (fgets(line, 1024, stdin)){
		
		// a cada iteração separa o atributo de de cada linha
		int tempo = atoi(strtok(line, " "));
		int identificador = atoi(strtok(NULL, " "));
		char operacao = strtok(NULL, " ")[0];
		char atributo = strtok(NULL, " ")[0];
		/*
		printf("Adicionando valor %d: \n", identificador);
		lista = adiciona_vertice( lista, identificador);
		printf("Buscando valor %d: \n", identificador);
		Vertex *teste = busca_vertice( lista, identificador);
		if (teste != NULL)
			printf("\tValor encontrado: %d \n", teste -> V );
		*/
		// printf("b");
		listaLog = insereLog(listaLog, tempo, identificador, operacao, atributo);
		int testeConflito = buscaConflito(listaLog);
		if (testeConflito == -1)
			printf("Nao possui conflitos \n");
		else
			printf("%d tem conflito com %d \n", listaLog -> tail -> id, testeConflito);

	}
	
	return 0;
}