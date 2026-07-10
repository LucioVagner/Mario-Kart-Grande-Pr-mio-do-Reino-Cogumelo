#ifndef HISTORICO_H
#define HISTORICO_H
#include "corridas.h"
#include "pilotos.h"

typedef struct history{
    Corrida corrida;
    Piloto posicao[10];
    int num_pilots;
    int temp;
    struct history *proximo;
    struct history *anterior; 
}Historico;
typedef struct {
    char pilot1[50];
    char pilot2[50];
    int encontros;
}Rivalidade;

void listar_vencedores(Historico *fila);

Historico *registro_fim(Historico *fila, Corrida corrida, int temp, Piloto posicao[], int num_pilotos);

void consulta_temp(Historico *atual, int temp);

void item_usados(Historico *atual);

void rivals(Historico *topo);

void maior_participacao(Historico *atual, NoPiloto *lista);

void listar_rank(Historico *hist);

void menu_historico(Historico *historico, int temp, NoPiloto *lista);

#endif