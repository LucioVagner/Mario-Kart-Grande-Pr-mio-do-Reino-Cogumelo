#ifndef ITENS_H
#define ITENS_H
#include "corridas.h"


typedef struct item{
    char nome[50];
    int power;
    int quanti;
    int rare;
    struct item *proximo;
}Itens;

void visualizar_itens(Itens *atual);

Itens *inicializar_itens();

Itens *add_item(Itens *lista);

void item_corrida(Itens *lista, Corrida *corrida, int i);

void devolver(Itens *lista, Corrida *corrida);

int sorteio(Itens *lista, int posicao);

void itens_uso(HeapCorridas *central);

void identify_item(HeapCorridas *central, Itens *lista);
#endif