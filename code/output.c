#include "output.h"


void print_output(VertexList *lista, int ident_escalonamento, bool isSerial, bool isEquivalent, int size_lista, int maior_id_transacao){
    if (lista == NULL)
        imprimeErro("Uma lista vazia foi passada para a função print_output");
    if (ident_escalonamento == 0)
        imprimeErro("Um ident_escalonamento foi passado zerado para a função print_output");
    printf("ident_escal %d, sizelista %d\n", ident_escalonamento, size_lista);
    int tam = TAM_CMD + (int)log10(ident_escalonamento) + 2*size_lista - 1;
    VertexList *iterator = lista;
    printf("Abacate %d\n", tam);
    char output[tam];
    char auxiliar_id_transacao[maior_id_transacao + 1];
    //1o campo, identificador escalonamento
    sprintf(output, "%d ", ident_escalonamento);
    //2o campo, a lista dos ids das transações que estão contidas no escalonamento
    if(iterator->next == NULL)
        imprimeErro("Amigao?");
    while(iterator->next != NULL){
        printf("\titerator %d\n", iterator->vertice->V);
        sprintf(auxiliar_id_transacao, "%d,", iterator->vertice->V);
        strcat(output, auxiliar_id_transacao);
        iterator = iterator->next;
    }
    sprintf(auxiliar_id_transacao, "%d ", iterator->vertice->V);
    strcat(output, auxiliar_id_transacao);

    //3o campo, serialidade
    sprintf(auxiliar_id_transacao, "%s ", isSerial?"SS":"NS");
    strcat(output, auxiliar_id_transacao);

    //4o campo, equivalente
    sprintf(auxiliar_id_transacao, "%s ", isEquivalent?"SV":"NV");
    strcat(output, auxiliar_id_transacao);

    printf("%s\n", output);

}