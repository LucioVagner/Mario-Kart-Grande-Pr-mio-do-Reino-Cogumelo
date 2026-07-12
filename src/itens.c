#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itens.h"
#include "karts.h"
#include "pilotos.h"
#include "corridas.h"
#include "portabilidade.h"

//mostra todos os tipos de itens, so o basico
void visualizar_itens(Itens *lista){
    if(lista == NULL){
        printf("SEM ITEMS DISPONÍVEIS. ADICIONE ITENS PARA VISUALIZAR.\n");
        return;
    }
    printf("==================================== ITENS DISPONÍVEIS ====================================\n\n");
    for(int i = 0; i < 7; i++){
        printf("[%d] Nome do item: %s\tPoder: %d\tQuantidade: %d\t", i, lista[i].nome, lista[i].power, lista[i].quanti);
        switch (lista[i].rare){
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
    }
    printf("\n========================================================================\n");
}
//inicializa os itens no inicio do programa
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
//adiciona itens no estoque
Itens *add_item(Itens *lista){
    int choose, quanti;

    printf("Digite o item que deseja adicionar ao estoque: ");
    printf("\n[1] para Banana\t[2] para Casco Verde\t[3] para Cogumelo\n[4] para Casco Vermelho\t[5] para Bob-omb\t[6] para Raio\t[7] para Bullet \n");
    while(scanf("%d", &choose) != 1 || choose < 1 || choose > 7 ){
        getchar();
        printf(RED"ERRO! DIGITE UMA ENTRADA VÁLIDA.\n"RESET);
    }
    printf("Digite a quantidade de itens que deseja adicionar: ");
    while(scanf("%d", &quanti) != 1 || quanti < 1){
        printf(RED"\nERRO! Digite uma entrada válida.\n"RESET);

    }
    lista[choose - 1].quanti += quanti;

    return lista;
}
//devolve caso o item n tenha sido usado
void devolver(Itens *lista, Corrida *corrida){
    for(int i = 0; i < 7; i++){
        lista[i].quanti += corrida->itens[i];
        corrida->itens[i] = 0;
    }
}
//sorteia o numero do item que vai ser jogado pra cada piloto
int sorteio(Itens *lista, int posicao){
    int raridade, inicio = rand() % 7;

    if(posicao == 1){
        raridade = 0;
    } else if(posicao <= 3){
        raridade = rand() % 2;
    } else{
        raridade = rand() % 4;
    }



    for(int i = 0; i < 7; i++){
        int j = (inicio + i) % 7;

        if(lista[j].rare == raridade && lista[j].quanti > 0){ //se a raridade sorteada e o item sorteado for igual ele decrementa e manda o indice
            lista[j].quanti--;
            return j;
        }
    }
    
    for(int i = 0; i < 7; i++){ //se nao tiver nada de item nos sorteados envia o primeiro item q achar

        if(lista[i].quanti > 0){

            lista[i].quanti--;
            return i;
        }
    }
    return -1;
}

//entra na central da corrida e confere qual item ta na corrida
void itens_uso(HeapCorridas *central){
    int find = 1;
    char *nomes_itens[7] = {"Banana", "Casco Verde", "Cogumelo", "Casco Vermelho", "Bob-omb", "Raio", "Bullet Bill"};

    printf("\n========================= ITENS EM USO =========================\n");

    for(int i = 0; i < central->tamanho; i++){
        int item = 1;

        for(int j = 0; j < 7; j++){
            if(central->corridas[i].itens[j] > 0){
                if(item == 1){
                    printf("Corrida: %s\n", central->corridas[i].nome);
                    item = 0;
                }
                printf("Item: %s\tQuantidade na corrida: %d\n", nomes_itens[j], central->corridas[i].itens[j]);
                find = 0;
            }
        }
    }

    if(find == 1){
        printf("Sem itens sendo utilizados nessa corrida.");
    }

    printf("\n=====================================================================\n");

}
//procura onde um item especifico ta sendo usado
void identify_item(HeapCorridas *central, Itens *lista){
    int choose, find = 1;


    visualizar_itens(lista);
    printf("Qual item deseja rastrear?\n ");

    while(scanf("%d", &choose) != 1 || choose < 1 || choose > 7){
        getchar();
        printf("ERRO! Digite uma entrada válida.\n");
    }



    
    for(int i = 0; i < central->tamanho; i++){
        if(central->corridas[i].itens[choose - 1] > 0){
            printf("Item na Corrida: %s | Quantidade em uso: %d\n", central->corridas[i].nome, central->corridas[i].itens[choose - 1]);
            find = 0;
        }
    }

    if(find == 1){
        printf("O item não está sendo usado em nenhuma corrida.\n");
    } 

    printf("\n======================================================================\n");

}
