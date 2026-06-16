#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"

NoPiloto* criar_lista_pilotos(){
    return NULL;
}
NoPiloto* cadastrar_piloto (NoPiloto *lista){
    NoPiloto *aux = (NoPiloto*) malloc(sizeof(NoPiloto));

    if(aux == NULL){
        printf("ERRO DE ALOCAÇÃO!");
        return lista;
    }
    aux->proximo = NULL;
    
    getchar();
    
    printf("Digite o nome do Piloto: ");
    fgets(aux->piloto.nome, sizeof(aux->piloto.nome), stdin);
    aux->piloto.nome[strcspn(aux->piloto.nome, "\n")] = 0;


    printf("Selecione a categoria do piloto.\n");
    printf("[1] para leve.\n[2] para medio.\n[3] para pesado.\n");
    while (scanf("%d", &aux->piloto.categoria) != 1 || aux->piloto.categoria < 1 || aux->piloto.categoria >3){
        while (getchar() != '\n');
        printf("ERRO! DIGITE UMA ENTRADA VALIDA\n");

    }
    printf("Digite a velocidade do piloto [1 ... 100]: ");
    while (scanf("%d", &aux->piloto.vel) != 1 || aux->piloto.vel < 1 || aux->piloto.vel > 100){
        while (getchar() != '\n');
        printf("ERRO! DIGITE UMA ENTRADA VALIDA\n");
    }
    aux->piloto.trofeus = 0;
    aux->piloto.status = 0;

    if(lista == NULL){
        return aux;
    }
    
    NoPiloto *novo = lista;
    while (novo->proximo != NULL){
        novo = novo->proximo;
    }
    novo->proximo = aux;

    return lista;
}

void listar_pilotos(NoPiloto *lista){
    NoPiloto *aux = lista;


    if (aux == NULL){
        printf("ERRO AO ALOCAR MEMORIA.\n");
        return;
    }


    while (aux != NULL){
        printf("Nome do piloto: %s\n", aux->piloto.nome);
        printf("Categoria do piloto: ");
        switch(aux->piloto.categoria){
            case 1:
                printf("Leve.\n");
                break;
            case 2:
                printf("Medio.\n");
                break;
            case 3:
                printf("Pesado.\n");
                break;
        }
        printf("Velocidade: %d\n", aux->piloto.vel);
        printf("Quantidade de trofeus: %d\n", aux->piloto.trofeus);
        printf("STATUS DO PILOTO: ");
            switch(aux->piloto.status){
                case 0:
                    printf("DISPONIVEL.\n");
                    break;
                case 1:
                    printf("SUSPENSO.\n");
                    break;
                case 2:
                    printf("ACIDENTADO.\n");
                    break;
            }
        aux = aux->proximo;
        }
        
    }