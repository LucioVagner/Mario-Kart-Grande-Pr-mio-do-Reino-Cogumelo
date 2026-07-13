#ifndef PILOTOS_H
#define PILOTOS_H

#include "karts.h"

typedef struct pilotos{
    char nome[50];
    int categoria;
    int trofeus;
    int status;
    Kart kart;
    int item;
    
}Piloto;

typedef struct NoPiloto{
    Piloto piloto;
    struct NoPiloto* proximo;
    struct NoPiloto* anterior;
}NoPiloto;

NoPiloto* criar_lista_pilotos();

NoPiloto* cadastrar_piloto (NoPiloto *lista);

void listar_pilotos(NoPiloto *lista);

NoPiloto* remover_piloto(NoPiloto *lista, NoPiloto **removidos);

void listar_piloto_nome(NoPiloto* lista, char name[50]);

void att_piloto(NoPiloto **lista, char name[50]);

void listar_suspensos (NoPiloto *removidos);

void listar_categoria(NoPiloto *lista);

void exibir_trofeu(NoPiloto *lista);

void listar_pilotos_all(NoPiloto *lista);

void liberar_lista_pilotos(NoPiloto *lista);

NoPiloto* inserir_piloto_direto(NoPiloto *lista, char nome[], int categoria, char nome_kart[], int vel, int acel, int controle, int durabil);
NoPiloto* inicializar_pilotos_padrao();

#endif