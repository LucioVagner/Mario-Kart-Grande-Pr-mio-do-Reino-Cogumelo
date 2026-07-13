#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oficina.h"
#include "pilotos.h"
#include "karts.h"
#include "itens.h"
#include "historico.h"
#include "portabilidade.h"

//funcao de colocar karts na oficina
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
//funcao de colocar karts destruidos na oficina
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
//funcao de heap uf normal
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
//funcao de heapdown normal tbm
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

//funcao de reparar o kart, apenas muda o valor do status do kart com maior prioridade, nao pode escolher qual kart arrumar
void repair_destructed(HeapOficina *heap, NoPiloto *lista){
    NoPiloto *aux = lista;
    Kart repaired;
    char nome[50];
    if (heap->tam == 0){
        printf("Nenhum kart na oficina.\n");
        return;
    }
    repaired = heap->karts[0];
    strcpy(nome, heap->piloto[0]);
    heap->karts[0] =  heap->karts[heap->tam - 1];
    strcpy(heap->piloto[0], heap->piloto[heap->tam - 1]);
    heap->tam--;

    if (heap->tam > 0){
        heapdown_oficina(heap, 0); //manda o ultimo valor do heap para abaixar ela ate o final de novo e encontrar o maior valor 
    }

    repaired.status = 0;
    repaired.damage = 100;


    while(aux != NULL){
        if(strcmp(aux->piloto.nome, nome) == 0){

            aux->piloto.status = 0;          // volta a ficar disponível
            aux->piloto.kart = repaired;     // devolve o kart consertado
            printf("Kart "YELLOW BOLD " %s" RESET"reparado com" GREEN " sucesso.\n"RESET, aux->piloto.kart.nome);
            return;
    }

    aux = aux->proximo;
    }

}
//mesma coisa que o de cima so que aquele era pra heap e esse é pra FIFO 
void repair_damaged(FilaOficina *fila, NoPiloto *lista){
    Nofila *aux;
    NoPiloto *pilot = lista;
    Kart repaired;
    int find = 0;
    if(fila->inicio == NULL){
        printf("Nenhum kart na oficina.\n");
        return;
    }
    aux = fila->inicio;
    repaired = aux->kart;
    
    repaired.status = 0;
    repaired.damage = 100;
    while(pilot != NULL){
        if(strcmp(pilot->piloto.nome, aux->piloto) == 0){
            pilot->piloto.status = 0;
            pilot->piloto.kart = repaired;
            find = 1;
            printf("Kart "YELLOW BOLD " %s" RESET"reparado com" GREEN " sucesso.\n"RESET, pilot->piloto.kart.nome);
        }
        pilot = pilot->proximo;
    }
    if(find == 1){
        fila->inicio = aux->proximo;

        if(fila->inicio == NULL){
        fila->fim = NULL;
    }

        free(aux);
        fila->tam--;
        return;
    }else{
        printf("Piloto não encontrado.\n");
    }
    

}
//passa por todos os karts danificados e destruidos da oficina com um for, so o basico

void consulta_oficina(Oficina *oficina){
    limpar_tela();
    printf(MAGENTA"\n----------------DESTRUIDOS-----------------\n"RESET);
    if(oficina->destruct.tam == 0){
            printf("SEM KARTS DESTRUIDOS NA OFICINA.\n");
    }else{
        for(int i = 0; i < oficina->destruct.tam; i++){
        
        printf("Piloto: "YELLOW BOLD"%s"RESET"\t| Kart: "GREEN BOLD"%s"RESET"\n", oficina->destruct.piloto[i], oficina->destruct.karts[i].nome);
    }
}

    printf(CYAN"\n----------------DANIFICADOS-----------------\n"RESET);
    if(oficina->damaged.tam == 0){
            printf("SEM KARTS DANIFICADOS NA OFICINA.\n");
            esperar(5000);
    }else {
        Nofila *aux = oficina->damaged.inicio;
        while(aux  != NULL){
            
            printf("Piloto: "YELLOW BOLD"%s"RESET"\t| Kart: "GREEN BOLD"%s"RESET"\n", aux->piloto, aux->kart.nome);
            aux = aux->proximo;
        }
    }

}
void liberar_oficina(FilaOficina *fila){
    Nofila *aux;
    while(fila->inicio != NULL){
        aux = fila->inicio;
        fila->inicio = fila->inicio->proximo;
        free(aux);
    }
    fila->fim = NULL;
    fila->tam = 0;
}
