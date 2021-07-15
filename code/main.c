/**
*	@file 	main.c
*	@brief	Contém a função main do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "Sistemas_Lineares.h"
// #include "utils.h"



/**
 * Função chamada pelo Sistema Operacional para execução do programa
 *
 * @param	argc	Número de argumentos da execução do programa
 * @param	argv	Vetor de strings dos argumentos de execução do programa 
 *
 * @retval	0		Caso o programa seja executado corretamente
 * @retval	-1		Caso seja encontrado um erro durante a execução do programa
 */
int main(int argc, char *argv[])
{	 
	char line[1024];
	while (fgets(line, 1024, stdin)){
		
		// a cada iteração de ptr, este "pega" uma substring de cada linha
		char *ptr = strtok(line, " ");
		while(ptr != NULL)
		{
			printf("%s ", ptr);
			ptr = strtok(NULL, " ");
		}
		printf("\n");
	}
	return 0;
}