#include "stdio.h"
#include "math.h"
#include "string.h"
#include "graph.h"
#include "erro.h"

#define TAM_CMD 8

int tamanho_lista(VertexList *lista);

void print_output(VertexList *lista, int ident_escalonamento, bool isSerial, bool isEquivalent, int size_lista);