#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portabilidade.h"
#include "historico.h"
#include "corridas.h"
#include "pilotos.h"
#include "karts.h"
#include "itens.h"
//lista os vencedores pelo historico
void listar_vencedores (Historico *fila){
    Historico *aux = fila;
    if (aux == NULL){
        printf("ERRO! HISTÓRICO VAZIO.\n");
        return;
    }
    printf("\n================= TEMPORADA %d =================\n", aux->temp);
    while (aux != NULL){
        
        printf("Corrida: %s\n", aux->corrida.nome);
        printf("Vencedor: %s\n", aux->posicao[0].nome);
        for(int i = 1; i < aux->num_pilots; i++){
            printf("Posição[%d]: %s\t", i, aux->posicao[i].nome);
        }
        printf("\n");
        aux = aux->proximo;
    }
}
//ao fim da corrida chama esse codigo pra registrar todos esses valores no historico
Historico *registro_fim(Historico *fila, Corrida corrida, int temp, Piloto posicao[], int num_pilots){
    Historico *att = (Historico *)malloc(sizeof(Historico));

    att->corrida = corrida;
    att->temp = temp;
    att->num_pilots = num_pilots;
    for(int i = 0; i < num_pilots; i++){
        att->posicao[i] = posicao[i];
    }
    att->proximo = fila;
    att->anterior = NULL;
    if(fila != NULL){
        fila->anterior = att;
    }

    return att;
}
//faz uma consulta so da temporada atual
void consulta_temp(Historico *atual, int temp){
    Historico *aux = atual;
    int find = 0;
    while (aux != NULL){
        if(aux->temp == temp){
            find = 1;
            listar_rank(aux);
        }

        aux = aux->proximo;
    }
    if (find == 0){
        printf("Nenhum registro para essa temporada.\n");
    }
}
//ve com o item mais utilizado ate o momento, quase sempre vai ser itens comuns
void item_usados(Historico *atual){
    int maior = 0, cont[7] = {0, 0, 0, 0, 0, 0, 0};
    char *names[7] = {"Banana", "Casco Verde", "Cogumelo", "Casco Vermelho", "Bob-omb", "Raio", "Bullet Bill"};
    Historico *aux = atual;

    while (aux != NULL){
        for(int i = 0; i < 7; i++){
            cont[i] += aux->corrida.itens[i];
        }
        aux = aux->proximo;
    }

    for(int i = 0; i < 7; i++){
        if(cont[i] > cont[maior]){
            maior = i;
        }
    }

    printf("Item mais utilizado: %s\nUsado: %d vezes", names[maior], cont[maior]);

}
//confere no historico quais pilotos se enfrentaram mais vezes durante todas as temporadas
void rivals(Historico *topo){
    Rivalidade rivais[50];
    int cont_rivais = 0;
    Historico * aux = topo;
    int maior = 0;
    if(topo == NULL){
        printf("SEM CORRIDAS DISPUTADAS.\n");
        return;
    }
    while (aux != NULL){
        for (int i = 0; i < aux->num_pilots; i++){
            for(int j = i + 1; j < aux->num_pilots; j++){
                int find = 0;
                for(int k = 0; k < cont_rivais; k++){
                    if((strcmp(rivais[k].pilot1, aux->posicao[i].nome) == 0 && strcmp(rivais[k].pilot2, aux->posicao[j].nome) == 0 || (strcmp(rivais[k].pilot1, aux->posicao[j].nome) == 0 && strcmp(rivais[k].pilot2, aux->posicao[i].nome) == 0))){
                        rivais[k].encontros++;
                        find = 1;
                    }
               }
               if(find == 0){
                strcpy (rivais[cont_rivais].pilot1, aux->posicao[i].nome);
                strcpy (rivais[cont_rivais].pilot2, aux->posicao[j].nome);
                rivais[cont_rivais].encontros = 1;
                cont_rivais++;
               }
            }
        }
        aux = aux->proximo;       
    }
    for(int i = 0; i < cont_rivais; i++){
            if(rivais[i].encontros > rivais[maior].encontros){
                maior = i;
            }
        }

        printf("Maior rivalidade: %s vs %s\nNúmero de corridas disputadas: %d",rivais[maior].pilot1, rivais[maior].pilot2, rivais[maior].encontros);

}
//ve quem é o piloto que mais participou de corridas
void maior_participacao(Historico *atual, NoPiloto *lista){
    NoPiloto *aux_lista = lista;
    char nome[50];
    int maior = 0;


    while(aux_lista != NULL){
        int count = 0;
        Historico *aux = atual;

        while(aux != NULL){
            for(int i = 0; i < aux->num_pilots; i++){
                if (strcmp(aux->posicao[i].nome, aux_lista->piloto.nome) == 0){
                    count++;
                }
            }
            aux = aux->proximo;
        }
        if(count > maior){
            maior = count;
            strcpy(nome, aux_lista->piloto.nome);
        }
        aux_lista = aux_lista->proximo;
    }

    printf("O piloto com maior taxa de participações é: %s\nParticipações: %d", nome, maior);

}
// lista todas as corridas com seus resultados
void listar_rank(Historico *hist){
    Historico *aux = hist;
    printf("\nCORRIDA: %s | Temp: %d\n", aux->corrida.nome, aux->temp);
    for(int i = 0; i < aux->num_pilots; i++){
        printf("%dº lugar: %s\n", i+1, aux->posicao[i].nome);
    }
}


void menu_historico(Historico *historico, int temp, NoPiloto *lista){
    int opcao;
    limpar_tela();
    do {
        printf("\n=========================== HISTÓRICO ================================\n");
        printf("\n| [1] para listar os vencedores.                                     |\n");
        printf("| [2] para listar a temporada.                                       |\n");
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