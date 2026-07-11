#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "itens.h"
#include "karts.h"
#include "pilotos.h"
#include "corridas.h"
#include "camp.h"
#include "historico.h"
#include "oficina.h"
#include "portabilidade.h"
#include "simulacao.h"
#include "menu.h"
int main(){
    srand(time(NULL));

    inicializar_terminal();
    setlocale(LC_ALL, ".UTF8");
     //mudei a logica da main Kart *karts = NULL;
    Historico *historico = NULL;
    Camp *campeonato = NULL;
    
    Itens *estoque = inicializar_itens();
    HeapCorridas *central = (HeapCorridas*) malloc(sizeof(HeapCorridas));
    Corrida *pistas = cria_pistas();
    iniciar_heap(central, pistas);

    free(pistas);

    NoPiloto *lista = criar_lista_pilotos();
    NoPiloto *removidos = criar_lista_pilotos();
    Oficina oficina;
    oficina.damaged.inicio = NULL;
    oficina.destruct.tam = 0;
    oficina.damaged.fim = NULL;
    oficina.damaged.tam = 0;
    int temp = 1;
    int opcao;
    int contador = 0;
    limpar_tela();
    do {
        printf("\n================== SIMULADOR DE CORRIDAS DE KART =====================\n");
        printf("| [1] para menu dos pilotos.                                         |\n");
        printf("| [2] para menu das corridas.                                        |\n");
        printf("| [3] para consultar a oficina.                                      |\n");
        printf("| [4] para menu do campeonato.                                       |\n");
        printf("| [5] para menu do histórico.                                        |\n");
        printf("| [0] para sair.                                                     |\n");
        printf("|                                                                    |\n======================================================================\n");

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 5){
            limpar_buffer();
            printf("ERRO! DIGITE NOVAMENTE.\n");
            printf("Digite o que deseja fazer: ");
        }

        switch(opcao){
            case 1:
                menu_pilotos(&lista, &removidos);
                limpar_tela();
                break;
            case 2:
                menu_corrida(central, &historico, &oficina, lista, estoque, &campeonato);
                limpar_tela();
                break;
            case 3:
                menu_oficina(&oficina);
                limpar_tela();
                break;
            case 4:
                menu_camp(campeonato, &contador, lista, central);
                limpar_tela();
                break;
            case 5:
                
                menu_historico(historico, temp, lista);
                limpar_tela();
                break;
            case 0:
                break;
        }
    } while(opcao != 0);

    free(estoque);
    free(central);
    
    return 0;
}