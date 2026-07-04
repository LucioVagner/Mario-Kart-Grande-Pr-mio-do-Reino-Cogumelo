#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "itens.h"
#include "karts.h"
#include "pilotos.h"
#include "corridas.h"

int main(){
    srand(time(NULL));
    Itens *estoque = inicializar_itens();
    HeapCorridas *central = (HeapCorridas*) malloc(sizeof(HeapCorridas));
    Corrida *pistas = cria_pistas();
    iniciar_heap(central, pistas);

    free(pistas);

    NoPiloto *lista = criar_lista_pilotos();

    int opcao;

    do {
        printf("\n================= Mario Kart ==================\n");
        printf("[1] para visualizar estoque.\n");
        printf("[2] para adicionar itens ao estoque.\n");
        printf("[3] para ver pistas\n");
        printf("[4] para simular item na pista\n");
        printf("[5] para visualizar itens em uso.\n");
        printf("[6] para rastrear item.\n");
        printf("[0] para sair.\n");
        printf("\n===============================================\n");

        printf("Digite o que deseja testar: ");
        while(scanf("%d", &opcao) != 1){
            getchar();
            printf("again");
        }

        switch(opcao){
            case 1:
                visualizar_itens(estoque);
                break;
            case 2:
                add_item(estoque);
                break;
            case 3:
                lista_pistas(central);
                break;
            case 4:
                if(central->tamanho > 0){
                    int i;
                    printf("Digite a posição do piloto: ");
                    scanf("%d", &i);

                    int item = sorteio(estoque, i);

                    if(item != -1){
                        printf("O piloto na posição %d tirou um %s\n", i, estoque[item].nome);
                        central->corridas[0].itens[item]++;

                    }else{
                        printf("Estoque de todos os itens vazio.\n");

                    }
                    
                }else{
                        printf("Nenhuma pista ativa.\n");
                }
                break;

            case 5:
                itens_uso(central);
                break;
            case 6:
                identify_item(central, estoque);
                break;
            case 0:
                break;
        }
    } while(opcao != 0);

    free(estoque);
    free(central);
    
    return 0;
}