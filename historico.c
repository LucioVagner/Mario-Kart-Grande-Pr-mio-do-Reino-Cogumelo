#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"
#include "corridas.h"
#include "pilotos.h"
#include "karts.h"
#include "itens.h"

void listar_vencedores (Historico *fila){
    Historico *aux = fila;
    if (aux == NULL){
        printf("ERRO! HISTÓRICO VAZIO");
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

void rivals(Historico *topo){
    Rivalidade rivais[50];
    int cont_rivais = 0;
    Historico * aux = topo;
    int maior = 0;
    
    while (aux != NULL){
        for (int i = 0; i < aux->num_pilots; i++){
            int find = 0;
            for(int j = i + 1; j < aux->num_pilots; j++){
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

    printf("O piloto com maior taxa de vitória é: %s\nParticipações: %d", nome, maior);

}