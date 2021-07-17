#include "erro.h"

void imprimeErro ( char* erro ) {
  fprintf (stderr, "Houve um erro: %s\n", erro);
  exit(-1);
}