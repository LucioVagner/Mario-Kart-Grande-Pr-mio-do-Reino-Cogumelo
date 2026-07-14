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

void devolver(Itens *lista, Corrida *corrida);

void itens_uso(HeapCorridas *central);

void identify_item(HeapCorridas *central, Itens *lista);
// sorteio agora recebe o catálogo (pra saber raridade/poder) E a corrida (de onde consome a reserva)
int sorteio(Itens *catalogo, Corrida *corrida, int posicao);

// distribui o estoque global pra todas as corridas pendentes no heap
void distribuir_itens_pistas(HeapCorridas *heap, Itens *estoque);

// ao fim de uma corrida: devolve o que sobrou e registra o que foi usado
void finalizar_itens_corrida(Itens *estoque, Corrida *corrida, int reservados_iniciais[7]);


#endif