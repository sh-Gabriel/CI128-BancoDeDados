#include <stdio.h>

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Houve um erro: %s\n", erro);
  exit(-1);
}