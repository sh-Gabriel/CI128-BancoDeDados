/**
 * @file erro.h
 * @author Gabriel S.H. & Vinícius V.T.S.
 * @brief Arquivo header de output.c
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "graph.h"
#include "erro.h"

#define TAM_CMD 8

/**
 * @brief Calcula o tamanho em bytes que as chaves dos vértices, somadas, têm
 * 
 * @param lista A lista de vértices existente
 * @return int O tamanho em bytes
 */
int tamanho_lista(VertexList *lista);

/**
 * @brief Formata e printa a output do programa
 * 
 * @param lista A lista de vértices do escalonamento corrente
 * @param ident_escalonamento A id do escalonamento
 * @param isSerial O escalonamento ser serial
 * @param isEquivalent O escalonamento ser equivalente
 * @param size_lista O tamanho em bytes da soma dos vértices da lista
 */
void print_output(VertexList *lista, int ident_escalonamento, bool isSerial, bool isEquivalent, int size_lista);