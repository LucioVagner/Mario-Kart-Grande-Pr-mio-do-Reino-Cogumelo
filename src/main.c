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
    
    int opcao;
    limpar_tela();
    do {
        printf("\n ================= SIMULADOR DE CORRIDAS DE KART =====================\n");
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
                if(central->tamanho == 0){
                    printf("Nenhuma pista disponivel na Central Digital.\n");
                } else {
                    Corrida atual = remover_corrida(central);
                    exibir_corrida(atual);

                    //seleciona ate 4 pilotos disponiveis (status == 0) percorrendo a lista dupla
                    NoPiloto *participantes[4];
                    int num_participantes = 0;
                    NoPiloto *aux = lista;
                    while(aux != NULL && num_participantes < 4){
                        if(aux->piloto.status == 0){
                            participantes[num_participantes] = aux;
                            num_participantes++;
                        }
                        aux = aux->proximo;
                    }

                    if(num_participantes < 2){
                        printf("Pilotos disponiveis insuficientes (minimo 2). Corrida cancelada.\n");
                    } else {
                        // fase de simulacao
                        ResultadoPiloto ranking[4];
                        simular_corrida(&atual, participantes, num_participantes, estoque, ranking);
                        exibir_ranking(&atual, ranking, num_participantes);

                        //integracao campeonato (arvore AVL)
                        int pontos_pos[4] = {15, 12, 10, 8};
                        for(int i = 0; i < num_participantes; i++){
                            if(search(campeonato, ranking[i].no->piloto.nome) == NULL){
                                //att_pont() nao cadastra piloto novo (so atualiza quem ja existe),
                                //entao na primeira corrida do piloto inseri
                                campeonato = inserir(campeonato, ranking[i].no->piloto.nome, pontos_pos[i]);
                            } else {
                                campeonato = att_pont(campeonato, ranking[i].no->piloto.nome, pontos_pos[i]);
                            }
                        }

                        // integracao historico
                        Piloto posicoes_hist[4];
                        for(int i = 0; i < num_participantes; i++){
                            posicoes_hist[i] = ranking[i].no->piloto;
                        }
                        historico = registro_fim(historico, atual, 1, posicoes_hist, num_participantes);

                        // integracao oficina e danos, conforme os eventos sofridos
                        for(int i = 0; i < num_participantes; i++){
                            if(ranking[i].evento == EVENTO_BOBOMB){
                                ranking[i].no->piloto.kart.status = 2; //Destruido
                                ranking[i].no->piloto.status = 1;      //Suspenso
                                put_destroyed(&oficina.destruct, ranking[i].no->piloto.kart, ranking[i].no->piloto.nome);
                            } else if(ranking[i].evento == EVENTO_BANANA){
                                ranking[i].no->piloto.kart.status = 1; //Danificado
                                put_kart(&oficina.damaged, ranking[i].no->piloto.kart, ranking[i].no->piloto.nome);
                            }
                        }
                    }
                }
                printf("\nAperte ENTER para retornar...");
                limpar_buffer();
                getchar();
                limpar_tela();
                break;
            case 3:
                consulta_oficina(&oficina);
                printf("\nAperte ENTER para retornar...");
                limpar_buffer();
                getchar();
                limpar_tela();
                break;
            case 4:
                /*  pendente ate decidirmos como a arvore AVL sera alimentada
                   pelos resultados das corridas. */
                printf("Menu do campeonato ainda nao implementado.\n");
                esperar(3000);
                limpar_tela();
                break;
            case 5:
                /* historico (sem prototipo de menu_historico em historico.h). */
                printf("Menu do historico ainda nao implementado.\n");
                esperar(3000);
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