#include <stdio.h>
#include <stdlib.h>

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Houve um erro: %s\n", erro);
  exit(-1);
}