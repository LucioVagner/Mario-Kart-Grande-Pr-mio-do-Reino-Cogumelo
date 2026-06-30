#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itens.h"
#include "karts.h"
#include "pilotos.h"
#include "corridas.h"


void visualizar_itens(Itens *atual){
    Itens *lista = atual;
    if(atual == NULL){
        printf("SEM ITEMS DISPONÍVEIS. ADICIONE ITENS PARA VISUALIZAR.\n");
        return;
    }
    printf("==================================== ITENS DISPONÍVEIS ====================================\n\n");
    while(lista != NULL){
        printf("Nome do item: %s\tPoder: %d\tQuantidade: %d\t", lista->nome, lista->power, lista->quanti);
        switch (lista->rare){
            case 0:
                printf("Raridade: Comum\n");
                break;
            case 1:
                printf("Raridade: Raro\n");
                break;
            case 2:
                printf("Raridade: Épico\n");
                break;
            case 3:
                printf("Raridade: Lendário\n");
                break;
        }
        lista = lista->proximo;
    }
    printf("\n========================================================================\n");
}

Itens *inicializar_itens(){
    Itens *lista = (Itens*)malloc(7 * sizeof(Itens));

    strcpy(lista[0].nome, "Banana");
    lista[0].rare = 0;
    lista[0].quanti = 5;
    lista[0].power = 10;

    strcpy(lista[1].nome, "Casco Verde");
    lista[1].rare = 0;
    lista[1].quanti = 5;
    lista[1].power = 20;

    strcpy(lista[2].nome, "Cogumelo");
    lista[2].rare = 1;
    lista[2].quanti = 3;
    lista[2].power = 30;

    strcpy(lista[3].nome, "Casco Vermelho");
    lista[3].rare = 1;
    lista[3].quanti = 3;
    lista[3].power = 40;

    strcpy(lista[4].nome, "Bob-omb");
    lista[4].rare = 2;
    lista[4].quanti = 2;
    lista[4].power = 60;

    strcpy(lista[5].nome, "Raio");
    lista[5].rare = 2;
    lista[5].quanti = 2;
    lista[5].power = 70;

    strcpy(lista[6].nome, "Bullet Bill");
    lista[6].rare = 3;
    lista[6].quanti = 1;
    lista[6].power = 90;

    return lista;
}

Itens *add_item(Itens *lista){
    int choose, quanti;

    printf("Digite o item que deseja adicionar ao estoque: ");
    printf("[1] para Banana\t[2] para Casco Verde\t[3] para Cogumelo\n[4] para Casco Vermelho\t[5] para Bob-omb\t[6] para Raio\t[7] para Bullet Bill");
    while(scanf("%d", &choose) != 1 || choose < 1 || choose > 7 ){
        getchar();
        printf("ERRO! DIGITE UMA ENTRADA VÁLIDA.\n");
    }
    printf("Digite a quantidade de itens que deseja adicionar: ");
    scanf("%d", &quanti);
    lista[choose - 1].quanti += quanti;

    return lista;
}

void item_corrida(Itens *lista, Corrida *corrida, int i){
    if(lista[i].quanti <= 0){
        return;
    }
    lista[i].quanti--;
    corrida->itens[i]++;
}

void devolver(Itens *lista, Corrida *corrida){
    for(int i = 0; i < 7; i++){
        lista[i].quanti += corrida->itens[i];
        corrida->itens[i] = 0;
    }
}

int sorteio(Itens *lista, int posicao){
    int raridade;

    if(posicao == 1){
        raridade = 0;
    } else if(posicao <= 3){
        raridade = 1;
    } else{
        raridade = 3;
    }

    int rare = rand () % (raridade + 1);

    for(int i = 0; i < 7; i++){
        if(lista[i].rare == raridade && lista[i].quanti > 0){
            return i;
        }
    }
    return -1;
}


