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
        printf(RED "SEM ITEMS DISPONÍVEIS. ADICIONE ITENS PARA VISUALIZAR.\n" RESET);
        return;
    }
    printf(GREEN BOLD"==================================== ITENS DISPONÍVEIS ====================================\n\n"RESET);
    for(int i = 0; i < 7; i++){
        printf("[%d] Nome do item: %s\tPoder: %d\tQuantidade: %d\t", i, lista[i].nome, lista[i].power, lista[i].quanti);
        switch (lista[i].rare){
            case 0:
                printf("Raridade: " MAGENTA "Comum\n" RESET);
                break;
            case 1:
                printf("Raridade: " MAGENTA "Raro\n" RESET);
                break;
            case 2:
                printf("Raridade: " MAGENTA "Épico\n" RESET);
                break;
            case 3:
                printf("Raridade: " MAGENTA "Lendário\n" RESET);
                break;
        }
    }
    printf(GREEN BOLD "\n========================================================================================\n" RESET);
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

    strcpy(lista[3].nome, "Casco Azul");
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
//sorteia o numero do item que vai ser jogado pra cada piloto, consumindo da reserva da corrida
int sorteio(Itens *catalogo, Corrida *corrida, int posicao){
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

        if(catalogo[j].rare == raridade && corrida->itens[j] > 0){
            corrida->itens[j]--;   // consome da reserva DESSA corrida, não do estoque global
            return j;
        }
    }

    for(int i = 0; i < 7; i++){
        if(corrida->itens[i] > 0){
            corrida->itens[i]--;
            return i;
        }
    }
    return -1;
}

//distribui o estoque global entre as corridas pendentes no heap, uma unidade por vez, em rodízio
void distribuir_itens_pistas(HeapCorridas *heap, Itens *estoque){
    if(heap->tamanho == 0){
        return;
    }

    for(int i = 0; i < 7; i++){
        int pista = 0;
        while(estoque[i].quanti > 0){
            estoque[i].quanti--;
            heap->corridas[pista].itens[i]++;
            pista = (pista + 1) % heap->tamanho;
        }
    }
}

//ao fim da corrida: devolve o que sobrou na reserva e registra o que foi de fato usado
void finalizar_itens_corrida(Itens *estoque, Corrida *corrida, int reservados_iniciais[7]){
    for(int i = 0; i < 7; i++){
        int usados = reservados_iniciais[i] - corrida->itens[i];
        estoque[i].quanti += corrida->itens[i];  // devolve o não utilizado
        corrida->itens[i] = usados;               // registra o consumo real pro histórico
    }
}
//entra na central da corrida e confere qual item ta na corrida
void itens_uso(HeapCorridas *central){
    int find = 1;
    char *nomes_itens[7] = {"Banana", "Casco Verde", "Cogumelo", "Casco Vermelho", "Bob-omb", "Raio", "Bullet Bill"};

    printf(BLUE BOLD"\n========================= ITENS EM USO =========================\n"RESET);

    for(int i = 0; i < central->tamanho; i++){
        int item = 1;

        for(int j = 0; j < 7; j++){
            if(central->corridas[i].itens[j] > 0){
                if(item == 1){
                    printf("\n\nCorrida: %s\n", central->corridas[i].nome);
                    item = 0;
                }
                printf("Item: %s\tQuantidade na corrida: %d\n", nomes_itens[j], central->corridas[i].itens[j]);
                find = 0;
            }
        }
    }

    if(find == 1){
        printf("Sem itens sendo utilizados nessa corrida.\n");
    }

    printf(BLUE BOLD"\n=====================================================================\n"RESET);

}
//procura onde um item especifico ta sendo usado
void identify_item(HeapCorridas *central, Itens *lista){
    int choose, find = 1;


    visualizar_itens(lista);
    printf("Digite o número do item que deseja rastrear:\n");

    while(scanf("%d", &choose) != 1 || choose < 0 || choose > 6){
        getchar();
        printf("ERRO! Digite uma entrada válida.\n");
    }



    
    for(int i = 0; i < central->tamanho; i++){
        if(central->corridas[i].itens[choose] > 0){
            printf("Item na Corrida: "YELLOW BOLD"%s" RESET" | Quantidade em uso: "MAGENTA BOLD"%d"RESET"\n", central->corridas[i].nome, central->corridas[i].itens[choose]);
            find = 0;
        }
    }

    if(find == 1){
        printf(RED"O item não está sendo usado em nenhuma corrida.\n" RESET);
    } 

    printf(GREEN BOLD"\n======================================================================\n" RESET);

}
