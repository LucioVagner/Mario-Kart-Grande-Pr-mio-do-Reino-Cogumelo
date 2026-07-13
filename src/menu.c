#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "portabilidade.h"
#include "pilotos.h"
#include "corridas.h"
#include "itens.h"
#include "historico.h"
#include "oficina.h"
#include "camp.h"
#include "menu.h"
#include "simulacao.h"
void menu_camp(Camp *campeonato, NoPiloto *lista, HeapCorridas *central, Camp *total){
    int opcao, last = -1, contador;
    char name[50];
    limpar_tela();
    do {
        printf(BLUE "\n=========================== CAMPEONATO ===============================\n");
        printf(RESET);
        printf("|                                                                    |\n");
        printf("| [1] Imprimir o rank total.                                    |\n");
        printf("| [2] Imprimir o top 10.                                        |\n");
        printf("| [3] Imprimir o atual campeão.                                 |\n");
        printf("| [4] Consultar a pontuação de um jogador.                      |\n");
        printf("| [0] Sair.                                                     |\n");
        printf("|                                                                    |\n" BLUE "======================================================================\n");
        printf(RESET);
        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 4){
            getchar();
            printf(RED "ERRO! DIGITE NOVAMENTE.\n");
            printf(RESET);
        }

        switch(opcao){
            case 1:
                contador = 0;
                limpar_buffer();
                ranking(campeonato, &contador);
                printf(GREEN "Aperte ENTER para voltar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 2:
                contador = 0;
                limpar_buffer();
                rank_tot(campeonato, &contador, &last);
                printf(GREEN "Aperte ENTER para voltar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 3:
                champion(total, central);
                esperar(5000);
                limpar_tela();
                break;
            case 4:limpar_buffer();
                printf("Digite o nome do Piloto que deseja buscar: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                consult_player(campeonato, name, lista);
                esperar(5000);
                limpar_tela();
                
                break;

            case 0:
                break;
            }
        }while(opcao != 0);
}
void menu_pilotos(NoPiloto **lista, NoPiloto **removidos){
    int opcao;
    char name[50];
    limpar_tela();
    do{
        printf(BLUE "\n=========================== Pilotos ==================================\n");
        printf(RESET);
        printf("|                                                                    |\n");
        printf("| [1] Cadastrar piloto.                                              |\n");
        printf("| [2] Remover piloto.                                                |\n");
        printf("| [3] Listar pilotos.                                                |\n");
        printf("| [4] Consultar piloto.                                              |\n");
        printf("| [5] Listar pilotos por categoria.                                  |\n");
        printf("| [6] Listar pilotos suspensos.                                      |\n");
        printf("| [7] Listar piloto com mais trofeus.                                |\n");
        printf("| [8] para atualizar algum piloto.                                   |\n");
        printf("| [0] para voltar.                                                   |\n");
        printf("|                                                                    |\n" BLUE "======================================================================\n");
        printf(RESET);
        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 8){
            getchar();
            printf(RED "ERRO! DIGITE NOVAMENTE.\n");
            printf(RESET);
        }
        switch(opcao){
            case 1:
                (*lista) = cadastrar_piloto(*lista);
                limpar_tela();
                break;
            case 2:
                (*lista) = remover_piloto(*lista, removidos);
                esperar(3000);
                limpar_tela();
                break;
            case 3:
                limpar_buffer();
                listar_pilotos_all(*lista);
                printf(GREEN "\nAperte ENTER para voltar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 4:
                limpar_buffer();
                printf("Digite o nome do Piloto que deseja buscar: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                listar_piloto_nome(*lista, name);
                esperar(5000);
                limpar_tela();
                break;
            case 5:
                limpar_buffer();
                listar_categoria(*lista);
                esperar(5000);
                limpar_tela();
                break;
            case 6:
                limpar_buffer();
                listar_suspensos(*removidos);
                printf(GREEN "\nAperte ENTER para retornar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 7:
                exibir_trofeu(*lista);
                esperar(5000);
                limpar_tela();
                break;
            case 8:
                printf("Digite o nome do piloto que deseja atualizar: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                att_piloto(lista, name);
                esperar(5000);
                limpar_tela();
            case 0:
                break;
        }
    }while(opcao != 0);
}


void menu_historico(Historico *historico, int temp, NoPiloto *lista, Camp *total){
    int opcao;
    int contador;
    limpar_tela();
    do {
        
        printf(BLUE "\n=========================== HISTÓRICO ================================\n");
        printf(RESET);
        printf("|                                                                    |\n");
        printf("| [1] Listar os vencedores.                                     |\n");
        printf("| [2] Listar uma temporada especifica.                          |\n");
        printf("| [3] Consultar os itens mais usados.                           |\n");
        printf("| [4] Exibir a maior rivalidade(mais corridas disputadas contra)|\n");
        printf("| [5] Exibir a maior participação.                              |\n");
        printf("| [6] Consultar o ranking geral.                                |\n");
        printf("| [0] Sair.                                                     |\n");
        printf("|                                                                    |\n" BLUE "======================================================================\n");
        printf(RESET);

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 6){
            getchar();
            printf(RED "ERRO! DIGITE NOVAMENTE.\n");
            printf(RESET);
        }

        switch(opcao){
            case 1:
                limpar_buffer();
                listar_vencedores(historico);
                printf(GREEN "\nAperte ENTER para retornar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 2:
                limpar_buffer();
                consulta_temp(historico, temp);
                printf(GREEN "\nAperte ENTER para retornar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 3:
                limpar_buffer();
                item_usados(historico);
                esperar(5000);
                limpar_tela();
                break;
            case 4:
                rivals(historico);
                esperar(5000);
                limpar_tela();
                break;

            case 5:
                maior_participacao(historico, lista);
                esperar(5000);
                limpar_tela();
                break;
            case 6:
                contador = 0;
                limpar_buffer();
                ranking(total, &contador);
                printf(GREEN "Aperte ENTER para voltar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 0:
                break;
        }
    } while(opcao != 0);

}


void menu_corrida(HeapCorridas *central, Historico **historico, Oficina *oficina, NoPiloto *lista, Itens *estoque, Camp **campeonato, Camp **total, int *temp){
    int opcao;

    do{
        printf(BLUE "\n========================== Corridas ==================================\n");
        printf(RESET);
        printf("|                                                                    |\n");
        printf("| [1] Visualizar pistas restantes na Central.                        |\n");
        printf("| [2] Correr.       |\n");
        printf("| [3] Encerrar a temporada.                                     |\n");
        printf("| [0] voltar.                                                   |\n");
        printf("|                                                                    |\n" BLUE"======================================================================\n");
        printf(RESET);
        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 3){
            limpar_buffer();
            printf(RED"ERRO! DIGITE NOVAMENTE.\n"RESET);
            printf("Digite o que deseja fazer: ");
        }

        switch(opcao){
            case 1:
                lista_pistas(central);
                printf(GREEN"\nAperte ENTER para retornar...");
                printf(RESET);
                limpar_buffer();
                getchar();
                limpar_tela();
                break;
            case 2:
                simulacao_final(central, historico, oficina, lista, estoque, campeonato, total, *temp);
                break;
            case 3:
                end_temp(campeonato, central, temp);
                break;
            case 0:
                break;
        }
    }while(opcao != 0);
}

void menu_oficina(Oficina *oficina, NoPiloto *lista){
    int opcao;
    limpar_tela();
    do {
        printf(BLUE "\n========================== OFICINA ================================\n");
        printf(RESET);
        printf("|                                                                    |\n");
        printf("| [1] Ver a oficina.                                            |\n");
        printf("| [2] Reparar destruidos.                                       |\n");
        printf("| [3] Reparar danificados.                                      |\n");
        printf("| [0] Voltar.                                                   |\n");
        printf("|                                                                    |\n" BLUE "======================================================================\n");
        printf(RESET);
        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 3){
            getchar();
            printf(RED "ERRO! DIGITE NOVAMENTE.\n");
            printf(RESET);
        }

        switch(opcao){
            case 1:
                limpar_buffer();
                consulta_oficina(oficina);
                printf(GREEN "\nAperte ENTER para retornar...");
                printf(RESET);
                getchar();
                limpar_tela();
                break;
            case 2:
                if(oficina->destruct.tam != 0){
                   
                    repair_destructed(&oficina->destruct, lista);
                    
                    
                   
                }else {
                    printf(RED "NENHUM KART NA OFICINA.\n" RESET);
                }
                esperar(5000);  
                limpar_tela();   
                break;
            case 3:
            if(oficina->damaged.tam != 0){
                
                repair_damaged(&oficina->damaged, lista);
                
            }else{
                    printf(RED"NENHUM KART NA OFICINA.\n"RESET);
                }
                esperar(5000);
                limpar_tela();
                break;
            case 0:
                break;
        }
    } while(opcao != 0);
}
void menu_item(Itens *itens, HeapCorridas *heap){
    int opcao;
    limpar_tela();
    do {
        printf(BLUE"\n========================= ITENS ==============================\n"RESET);
        printf("|                                                                    |\n");
        printf("| [1] Listar os itens.                                          |\n");
        printf("| [2] Adicionar item ao estoque                                 |\n");
        printf("| [3] Ver os itens que estão sendo usados.                      |\n");
        printf("| [4] Rastrear um item especifico.                              |\n");
        printf("| [0] para sair.                                                     |\n");
        printf("|                                                                    |\n"BLUE"======================================================================"RESET"\n");

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 3){
            getchar();
            printf(RED"ERRO! DIGITE NOVAMENTE.\n"RESET);
        }

        switch(opcao){
            case 1:
                limpar_buffer();
                visualizar_itens(itens);
                printf(GREEN"Aperte ENTER para retornar..."RESET);
                getchar();
                limpar_tela();
                break;
            case 2:
                itens = add_item(itens);
                limpar_tela();
                break;
            case 3:
                itens_uso(heap);
                esperar(5000);
                limpar_tela();
                break;
            case 4:
                limpar_buffer();
                identify_item(heap, itens);
                printf(GREEN"Aperte ENTER para retornar..."RESET);
                getchar();
                limpar_tela();
            case 0:
                break;
        }
    } while(opcao != 0);

}