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
        atual->inicio = aux;
        atual->fim = aux;
    }else
        {
        atual->fim->proximo = aux;
        atual->fim = aux;

    }
    atual->tam++;

    
}

void put_destroyed(HeapOficina *heap, Kart kart, char pilot[]){
    if(heap->tam >= 10){
        printf("OFICINA CHEIA, VOLTE MAIS TARDE.\n");
        return;
    }
    heap->karts[heap->tam] = kart;
    strcpy(heap->piloto[heap->tam], pilot);
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
        strcpy(temp, heap->piloto[tam]);
        strcpy(heap->piloto[tam], heap->piloto[pai]);
        strcpy(heap->piloto[pai], temp);

        heapup_oficina(heap, pai);
    }

}

void heapdown_oficina(HeapOficina *heap, int tam){
    int esq = 2 * tam + 1;
    int dir = 2 * tam + 2;
    int maior = tam;

    if ((esq < heap->tam && (heap->karts[esq].status > heap->karts[maior].status))){
        maior = esq;
    }
    if(dir < heap->tam && (heap->karts[dir].status > heap->karts[maior].status)){
        maior = dir;
    }

    if (maior != tam){
        Kart aux = heap->karts[tam];
        heap->karts[tam] = heap->karts[maior];
        heap->karts[maior] = aux;

        char temp[50];
        strcpy(temp, heap->piloto[tam]);
        strcpy(heap->piloto[tam], heap->piloto[maior]);
        strcpy(heap->piloto[maior], temp);

        heapdown_oficina(heap, maior);
    }

}


Kart repair_destructed(HeapOficina *heap){
    if (heap->tam == 0){
        printf("Nenhum kart na oficina.\n");
        Kart vazio = {"", 0, 0, 0, 0, 0};
        return vazio;
    }
    Kart repaired = heap->karts[0];
    heap->karts[0] =  heap->karts[heap->tam - 1];
    strcpy(heap->piloto[0], heap->piloto[heap->tam - 1]);
    heap->tam--;

    if (heap->tam > 0){
        heapdown_oficina(heap, 0);
    }

    repaired.status = 0;
    return repaired;

}

Kart repair_damaged(FilaOficina *fila){
    if(fila->inicio == NULL){
        printf("Nenhum kart na oficina.\n");
        Kart vazio = {"", 0, 0, 0, 0, 0};
        return vazio;
    }
    Nofila *aux = fila->inicio;
    Kart repaired = aux->kart;
    fila->inicio = aux->proximo;

    if(fila->inicio == NULL){
        fila->fim = NULL;
    }

    free(aux);
    fila->tam--;
    repaired.status = 0;
    return repaired;


}

void consulta_oficina(Oficina *oficina){
    printf("----------------DESTRUIDOS-----------------\n");
    for(int i = 0; i < oficina->destruct.tam; i++){
        printf("Piloto: %s\t|Kart: %s\n", oficina->destruct.piloto[i], oficina->destruct.karts[i].nome);
    }

    printf("----------------DANIFICADOS-----------------\n");
    Nofila *aux = oficina->damaged.inicio;
    while(aux != NULL){
        printf("Piloto: %s\t|Kart: %s", aux->piloto, aux->kart.nome);
        aux = aux->proximo;
    }

}