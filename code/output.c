/**
 * @file erro.c
 * @author Gabriel S.H. & Vinícius T. V. S.
 * @brief Arquivo contendo funções referentes à geração de saída do programa
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "output.h"

/**
 * @brief Calcula o tamanho em bytes que as chaves dos vértices, somadas, têm
 * 
 * @param lista A lista de vértices existente
 * @return int O tamanho em bytes
 */
int tamanho_lista(VertexList *lista){
    if (lista == NULL)
        return 0;
    VertexList *iterator = lista;
    int size = 0;
    while(iterator != NULL){
        size+=(int)sizeof(iterator->vertice->V);
        iterator = iterator->next;
    }
    return size;
}

/**
 * @brief Formata e printa a output do programa
 * 
 * @param lista A lista de vértices do escalonamento corrente
 * @param ident_escalonamento A id do escalonamento
 * @param isSerial O escalonamento ser serial
 * @param isEquivalent O escalonamento ser equivalente
 * @param size_lista O tamanho em bytes da soma dos vértices da lista
 */
void print_output(VertexList *lista, int ident_escalonamento, bool isSerial, bool isEquivalent, int size_lista){
    if (lista == NULL)
        imprimeErro("Uma lista vazia foi passada para a função print_output");
    if (ident_escalonamento == 0)
        imprimeErro("Um ident_escalonamento foi passado zerado para a função print_output");
    
    int tam = TAM_CMD + (int)log10(ident_escalonamento) + 2*size_lista - 1;
    VertexList *iterator = lista;
    char output[tam];
    char auxiliar_id_transacao[(int)sizeof(int)];
    //1o campo, identificador escalonamento
    sprintf(output, "%d ", ident_escalonamento);
    //2o campo, a lista dos ids das transações que estão contidas no escalonamento
    while(iterator->next != NULL){
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