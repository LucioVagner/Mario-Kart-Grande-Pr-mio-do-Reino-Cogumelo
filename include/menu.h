#ifndef MENU_H
#define MENU_H

#include "pilotos.h"
#include "corridas.h"
#include "itens.h"
#include "historico.h"
#include "oficina.h"
#include "camp.h"

void menu_pilotos(NoPiloto **lista, NoPiloto **removidos);

void menu_corrida(HeapCorridas *central, Historico **historico, Oficina *oficina, NoPiloto *lista, Itens *estoque, Camp **campeonato);

void menu_item(Itens *itens, HeapCorridas *heap);

void menu_oficina(Oficina *oficina);

void menu_camp(Camp *campeonato, int *contador, NoPiloto *lista, HeapCorridas *central);

void menu_historico(Historico *historico, int temp, NoPiloto *lista);

void menu_oficina(Oficina *oficina);
#endif