#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"
#include "corridas.h"
#include "pilotos.h"
#include "karts.h"
#include "itens.h"
#include "portabilidade.h"
//lista os vencedores pelo historico
void listar_vencedores (Historico *fila){
    Historico *aux = fila;
    if (aux == NULL){
        printf("ERRO! HISTÓRICO VAZIO");
        return;
    }
    printf(CYAN BOLD"\n======================================== TEMPORADA %d =========================================\n"RESET, aux->temp);
    while (aux != NULL){
        printf("\n-----------------------------------------------------------------------------------------------------\n");
        printf("Corrida: "MAGENTA BOLD"%s"RESET"\n", aux->corrida.nome);
        printf("Vencedor: "YELLOW"%s"RESET"\n", aux->posicao[0].nome);
        for(int i = 0; i < 3; i++){
            printf("Posição[%d]: "YELLOW BOLD"%s"RESET"\t    ", i+1, aux->posicao[i].nome);
        }
       
        aux = aux->proximo;
    }
    printf(CYAN BOLD"\n==============================================================================================\n"RESET);
    printf("\n");
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
    printf("Digite a temporada que deseja conferir: ");
    scanf("%d", &temp);
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

    printf("Item mais utilizado: "YELLOW BOLD"%s"RESET"\nUsado:"MAGENTA BOLD" %d"RESET" vezes\n", names[maior], cont[maior]);

}
//confere no historico quais pilotos se enfrentaram mais vezes durante todas as temporadas
void rivals(Historico *topo){
    Rivalidade rivais[50];
    int cont_rivais = 0;
    Historico * aux = topo;
    int maior = 0;
    
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
    if(cont_rivais == 0){
        printf("NENHUMA RIVALIDADE REGISTRADA AINDA.\n");
        return;
    }
    for(int i = 0; i < cont_rivais; i++){
            if(rivais[i].encontros > rivais[maior].encontros){
                maior = i;
            }
        }

        printf("Maior rivalidade: "RED BOLD"%s "RESET"vs"BLUE BOLD" %s"RESET"\nNúmero de corridas disputadas: %d\n",rivais[maior].pilot1, rivais[maior].pilot2, rivais[maior].encontros);

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

    printf("O piloto com maior taxa de participações é: "YELLOW"%s"RESET"\nParticipações: %d\n", nome, maior);

}
// lista todas as corridas com seus resultados
void listar_rank(Historico *hist){
    Historico *aux = hist;
    printf("\nCORRIDA: %s | Temp: %d\n", aux->corrida.nome, aux->temp);
    for(int i = 0; i < aux->num_pilots; i++){
        printf(MAGENTA BOLD"%dº"RESET" lugar: "YELLOW BOLD"%s"RESET"\n", i+1, aux->posicao[i].nome);
    }
}
