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
void menu_camp(Camp *campeonato, int *contador, NoPiloto *lista, HeapCorridas *central){
    int opcao, last = -1;
    char name[50];
    limpar_tela();
    do {
        printf("\n=========================== CAMPEONATO ===============================\n");
        printf("| [1] para imprimir o rank total.                                    |\n");
        printf("| [2] para imprimir o rank atual.                                    |\n");
        printf("| [3] para imprimir o atual campeão.                                 |\n");
        printf("| [4] para consultar a pontuação de um jogador.                      |\n");
        printf("| [0] para sair.                                                     |\n");
        printf("|                                                                    |\n======================================================================\n");

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 4){
            getchar();
            printf("ERRO! DIGITE NOVAMENTE.\n");
        }

        switch(opcao){
            case 1:
                limpar_buffer();
                ranking(campeonato, contador);
                printf("Aperte ENTER para voltar...");
                getchar();
                limpar_tela();
                break;
            case 2:
                limpar_buffer();
                rank_tot(campeonato, contador, &last);
                printf("Aperte ENTER para voltar...");
                getchar();
                limpar_tela();
                break;
            case 3:
                champion(campeonato, central);
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
    do{
        printf("\n=========================== Pilotos ==================================\n");
        printf("| [1] Cadastrar piloto.                                              |\n");
        printf("| [2] Remover piloto.                                                |\n");
        printf("| [3] Listar pilotos.                                                |\n");
        printf("| [4] Consultar piloto.                                              |\n");
        printf("| [5] Listar pilotos por categoria.                                  |\n");
        printf("| [6] Listar pilotos suspensos.                                      |\n");
        printf("| [7] Listar piloto com mais trofeus.                                |\n");
        printf("| [0] para voltar.                                                   |\n");
        printf("|                                                                    |\n======================================================================\n");
        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 7){
            getchar();
            printf("ERRO! DIGITE NOVAMENTE.\n");
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
                printf("Aperte ENTER para voltar...");
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
                printf("Aperte ENTER para retornar...");
                getchar();
                limpar_tela();
                break;
            case 7:
                exibir_trofeu(*lista);
                esperar(5000);
                limpar_tela();
                break;
            case 0:
                break;
        }
    }while(opcao != 0);
}


void menu_historico(Historico *historico, int temp, NoPiloto *lista){
    int opcao;
    limpar_tela();
    do {
        printf("\n=========================== HISTÓRICO ================================\n");
        printf("|                                                                    |\n");
        printf("| [1] para listar os vencedores.                                     |\n");
        printf("| [2] para listar uma temporada especifica.                          |\n");
        printf("| [3] para consultar os itens mais usados.                           |\n");
        printf("| [4] para exibir a maior rivalidade(mais corridas disputadas contra)|\n");
        printf("| [5] para exibir a maior participação.                              |\n");
        printf("| [0] para sair.                                                     |\n");
        printf("|                                                                    |\n======================================================================\n");

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 5){
            getchar();
            printf("ERRO! DIGITE NOVAMENTE.\n");
        }

        switch(opcao){
            case 1:
                limpar_buffer();
                listar_vencedores(historico);
                printf("Aperte ENTER para retornar...");
                getchar();
                limpar_tela();
                break;
            case 2:
                limpar_buffer();
                consulta_temp(historico, temp);
                printf("Aperte ENTER para retornar...");
                getchar();
                limpar_tela();
                break;
            case 3:
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
            case 0:
                break;
        }
    } while(opcao != 0);

}








void menu_corrida(HeapCorridas *central, Historico **historico, Oficina *oficina, NoPiloto *lista, Itens *estoque, Camp **campeonato){
    int opcao;

    do{
        printf("\n========================== Corridas ==================================\n");
        printf("| [1] Visualizar pistas restantes na Central.                        |\n");
        printf("| [2] Preparar proxima corrida (remove a de maior prioridade).       |\n");
        printf("| [0] para voltar.                                                   |\n");
        printf("|                                                                    |\n======================================================================\n");
        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 2){
            limpar_buffer();
            printf("ERRO! DIGITE NOVAMENTE.\n");
            printf("Digite o que deseja fazer: ");
        }

        switch(opcao){
            case 1:
                lista_pistas(central);
                printf("\nAperte ENTER para retornar...");
                limpar_buffer();
                getchar();
                limpar_tela();
                break;
            case 2:
                simulacao_final(central, historico, oficina, lista, estoque, campeonato);
                break;
            case 0:
                break;
        }
    }while(opcao != 0);
}

void menu_oficina(Oficina *oficina){
    int opcao;
    Kart reparado;
    limpar_tela();
    do {
        printf("\n========================== OFICINA ================================\n");
        printf("| [1] para ver a oficina.                                            |\n");
        printf("| [2] para reparar destruidos.                                       |\n");
        printf("| [3] para reparar danificados.                                      |\n");
        printf("|                                                                    |\n======================================================================\n");

        printf("Digite o que deseja fazer: ");
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 3){
            getchar();
            printf("ERRO! DIGITE NOVAMENTE.\n");
        }

        switch(opcao){
            case 1:
                limpar_buffer();
                consulta_oficina(oficina);
                printf("Aperte ENTER para retornar...");
                getchar();
                limpar_tela();
                break;
            case 2:
                reparado = repair_destructed(&oficina->destruct);
                printf("Kart %s reparado com sucesso.\n", reparado.nome);
                esperar(5000);
                limpar_tela();
                break;
            case 3:
                reparado = repair_damaged(&oficina->damaged);
                printf("Kart %s reparado com sucesso.\n", reparado.nome);
                esperar(5000);
                limpar_tela();
                break;
            case 0:
                break;
        }
    } while(opcao != 0);
}