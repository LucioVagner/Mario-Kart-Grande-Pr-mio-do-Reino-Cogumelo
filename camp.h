#ifndef CAMP_H
#define CAMP_H
#include "pilotos.h"
typedef struct camp{
    char nome[50];
    int pontos;
    int alt;
    struct camp *esq;
    struct camp *dir;
} Camp;

typedef struct{
    Camp *raiz;
}Championship;

int altura(Camp *no);

int height(Camp *no);

int balance(Camp *no);

Camp *rotation_dir(Camp *no);

Camp *rotation_esq(Camp *no);

Camp *balancear(Camp *no);

Camp *inserir(Camp *raiz, char nome[], int pontos);

void ranking(Camp *raiz, int *cont);

Camp* att_pont(Camp *raiz, char nome[], int pont);

Camp *remover(Camp *raiz, int ponto, char nome[]);

Camp *search(Camp *raiz, char nome[]);

Camp* menor(Camp *no);

void champion(Camp *raiz);

void rank_tot(Camp *raiz, int *cont, int *last_pont);

void consult_player(Camp *raiz, char nome[], NoPiloto *lista);

int calc_pos(int posicao);

void menu_camp(Camp *campeonato, int *contador, NoPiloto *lista);
#endif