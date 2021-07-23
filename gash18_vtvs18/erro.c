/**
 * @file erro.c
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo contendo a função de erro usada no código
 * @version 1.0
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Houve um erro: %s\n", erro);
  exit(-1);
}