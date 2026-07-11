#ifndef CORRIDAS_H
#define CORRIDAS_H

typedef struct pista{
    char nome[50];
    int voltas;
    int perigo;
    int clima;
    int status;
    int prioridade;
    int itens[7];
}Corrida;

typedef struct {
    Corrida corridas[5];
    int tamanho;
    int capacidade;

} HeapCorridas;

Corrida *cria_pistas();

void lista_pistas(HeapCorridas *heap);

void iniciar_heap(HeapCorridas *heap, Corrida *pistas);

void heapify_up(HeapCorridas *heap, int i);

void heapify_down(HeapCorridas *heap, int i);

Corrida remover_corrida(HeapCorridas *heap);

void exibir_corrida(Corrida corrida);

#endif