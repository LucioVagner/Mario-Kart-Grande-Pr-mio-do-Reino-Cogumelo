#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oficina.h"
#include "pilotos.h"
#include "karts.h"
#include "itens.h"
#include "historico.h"


void put_kart(FilaOficina *atual, Kart kart, char pilot[]){
    Nofila *aux = (Nofila*)malloc (sizeof(Nofila));
    if(aux == NULL){
        printf("ERRO! SEM KARTS ACIDENTADOS.\n");
        return;
    }

    aux->kart = kart;
    strcpy(aux->piloto, pilot);
    aux->proximo = NULL;

    if(atual->inicio == NULL){
        atual->inicio == aux;
    }else
        {
        atual->fim->proximo = aux;
        atual->fim = aux;
        atual->tam++;
        }
    
}

void put_destroyed(HeapOficina *heap, Kart kart, char pilot[]){
    if(heap->tam >= 10){
        printf("OFICINA CHEIA, VOLTE MAIS TARDE.\n");
        return;
    }
    heap->karts[heap->tam] = kart;
    strcpy(heap->pilotos[heap->tam], pilot);
    heap->tam++;

    heapup_oficina(heap, heap->tam - 1);
}

void heapup_oficina(HeapOficina *heap, int tam){
    int pai = (tam - 1)/2;

    if(tam > 0 && heap->karts[tam].status > heap->karts[pai].status){
        Kart aux = heap->karts[tam];
        heap->karts[tam] = heap->karts[pai];
        heap->karts[pai] = aux;

        char temp[50];
        strcpy(temp, heap->pilotos[tam]);
        strcpy(heap->pilotos[tam], heap->pilotos[pai]);
        strcpy(heap->pilotos[pai], temp);

        heapup_oficina(heap, pai);
    }
}