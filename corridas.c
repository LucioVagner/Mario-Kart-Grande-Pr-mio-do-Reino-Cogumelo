#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pilotos.h"
#include "karts.h"
#include "corridas.h"

Corrida *cria_pistas(){
    Corrida *pistas = (Corrida*) malloc(5 * sizeof(Corrida));

    if(pistas == NULL){
        printf("ERRO DE ALOCAÇÃO!\n");
        return NULL;
    }

    strcpy(pistas[0].nome, "Rainbow Road");
    strcpy(pistas[1].nome, "Bowser's Castle");
    strcpy(pistas[2].nome, "Mario Circuit");
    strcpy(pistas[3].nome, "Sherbet Land");
    strcpy(pistas[4].nome, "Coconut Mall");

    pistas[0].perigo = 95;
    pistas[1].perigo = 85;
    pistas[2].perigo = 40;
    pistas[3].perigo = 60;
    pistas[4].perigo = 25;
    
    pistas[0].voltas = 3;
    pistas[1].voltas = 3;
    pistas[2].voltas = 5;
    pistas[3].voltas = 4;
    pistas[4].voltas = 3;


    for(int i = 0; i < 5; i++){
        pistas[i].clima = (rand() % 3 ) + 1;
        pistas[i].status = 0;
    }

    return pistas;
}

void lista_pistas(HeapCorridas *heap){
    if(heap->tamanho == 0){
        printf("Nenhuma pista disponível na Central Digital.\n");
        return;
    }

    printf("\n------------------------------------------\n\n|\tPISTAS RESTANTES NA CENTRAL CORRIDAS\t|\n\n------------------------------------------\n");
    for(int i = 0; i < heap->tamanho; i++){
        printf("[%d] %s\nPerigo: %d\nVoltas: %d\n", i+1, heap->corridas[i].nome, heap->corridas[i].perigo, heap->corridas[i].voltas);   
    }
}

void iniciar_heap(HeapCorridas *heap, Corrida *pistas){
    heap->tamanho = 0;
    heap->capacidade = 5;


    for(int i = 0; i < 5; i++){
        heap->corridas[i] = pistas[i];
        heap->tamanho++;
        heapify_up(heap, i);
    }
}

void heapify_up(HeapCorridas *heap, int i){
    int pai = (i-1)/2;

    if (i > 0){
        if((heap->corridas[i].perigo > heap->corridas[pai].perigo) || (heap->corridas[i].perigo == heap->corridas[pai].perigo && heap->corridas[i].prioridade < heap->corridas[pai].prioridade)){
            Corrida aux = heap->corridas[i];
            heap->corridas[i] = heap->corridas[pai];
            heap->corridas[pai] = aux;

            heapify_up(heap, pai);
        }
    }
}

void heapify_down(HeapCorridas *heap, int i){
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int maior = i;

    if(esq < heap->tamanho && (heap->corridas[esq].perigo > heap->corridas[maior].perigo || (heap->corridas[esq].perigo == heap->corridas[maior].perigo && heap->corridas[esq].prioridade < heap->corridas[maior].prioridade))){
        maior = esq;
    }
    if(dir < heap->tamanho && (heap->corridas[dir].perigo > heap->corridas[maior].perigo || (heap->corridas[dir].perigo == heap->corridas[maior].perigo && heap->corridas[dir].prioridade < heap->corridas[maior].prioridade))){
        maior = dir;
    }

    if (maior != i){
        Corrida aux = heap->corridas[i];
        heap->corridas[i] = heap->corridas[maior];
        heap->corridas[maior] = aux;

        heapify_down(heap, maior);
    }
}

Corrida remover_corrida(HeapCorridas *heap){
    if(heap->tamanho == 0){
        printf("Nenhuma pista disponível na Central Digital.\n");
        Corrida vazia = {"", 0, 0, 0, 0, 0};
        return vazia;
    }

    Corrida topo = heap->corridas[0];
    heap->corridas[0] = heap->corridas[heap->tamanho - 1];

    heap->tamanho--;

    if (heap->tamanho > 0){
        heapify_down(heap, 0);
    }

    return topo;
}