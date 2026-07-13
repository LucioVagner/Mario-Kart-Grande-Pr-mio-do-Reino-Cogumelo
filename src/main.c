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
    Camp *total = NULL;
    Itens *estoque = inicializar_itens();
    HeapCorridas *central = (HeapCorridas*) malloc(sizeof(HeapCorridas));
    Corrida *pistas = cria_pistas();
    iniciar_heap(central, pistas);

    free(pistas);

    NoPiloto *lista = inicializar_pilotos_padrao();
    NoPiloto *removidos = criar_lista_pilotos();
    Oficina oficina;
    oficina.damaged.inicio = NULL;
    oficina.destruct.tam = 0;
    oficina.damaged.fim = NULL;
    oficina.damaged.tam = 0;
    int temp = 1;
    int opcao;
    limpar_tela();
    do {
        printf(RED BOLD"\n================== SIMULADOR DE CORRIDAS DE KART =====================\n");
        printf(RESET);
        printf("|                                                                    |\n");
        printf("| [1] Menu dos pilotos.                                              |\n");
        printf("| [2] Menu das corridas.                                             |\n");
        printf("| [3] Consultar a oficina.                                           |\n");
        printf("| [4] Menu do campeonato.                                            |\n");
        printf("| [5] Menu do histórico.                                             |\n");
        printf("| [6] Conferir o estoque.                                            |\n");
        printf("| [0] Sair.                                                          |\n");
        printf("|                                                                    |\n"RED BOLD"======================================================================\n");
        printf(RESET);

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 6){
            limpar_buffer();
            printf(RED "ERRO! DIGITE NOVAMENTE.\n");
            printf(RESET);
            printf("Digite o que deseja fazer: ");
        }

        switch(opcao){
            case 1:
                menu_pilotos(&lista, &removidos);
                limpar_tela();
                break;
            case 2:
                menu_corrida(central, &historico, &oficina, lista, estoque, &campeonato, &total, &temp);
                limpar_buffer();
                limpar_tela();
                break;
            case 3:
                menu_oficina(&oficina, lista);
                limpar_tela();
                break;
            case 4:
                menu_camp(campeonato, lista, central, total);
                limpar_tela();
                break;
            case 5:
                
                menu_historico(historico, temp, lista, total);
                limpar_buffer();
                limpar_tela();
                break;
            case 6:
                menu_item(estoque, central);
                limpar_tela();
                break;
            case 0:
                break;
        }
    } while(opcao != 0);

    

    return 0;
    liberar_oficina(&oficina.damaged);
    free(estoque);
    free(central);
    free(lista);
    free(removidos);
    free(campeonato);
    free(historico);
    liberar_lista_pilotos(lista);
    liberar_lista_pilotos(removidos);
    liberar_historico(historico);
    liberar_camp(campeonato);
    liberar_camp(total); 
}
 



