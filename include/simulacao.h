#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "pilotos.h"
#include "corridas.h"
#include "itens.h"
#include "historico.h"
#include "oficina.h"
#include "camp.h"

#define MAX_PARTICIPANTES 10

//tipos de evento especial que podem ocorrer durante a Fase de Simulação
typedef enum {
    EVENTO_NENHUM = 0,
    EVENTO_CASCO_AZUL,
    EVENTO_BANANA,
    EVENTO_COGUMELO,
    EVENTO_BOBOMB,
    EVENTO_RAIO
} TipoEvento;

//resultado de um piloto em uma corrida ja simulada, junto do evento que o afetou (se algum)
typedef struct {
    NoPiloto *no;       //ponteiro para o nó original na lista de pilotos, pra permitir aplicar consequencias depois
    int resultado;
    TipoEvento evento;
} ResultadoPiloto;

//------- fórmula de desempenho -------
//Resultado = Desempenho do Piloto + Bônus do Kart + Efeito dos Itens + Sorte - Dificuldade da Pista
int desempenho_piloto(Piloto *piloto);
int bonus_kart(Kart *kart);
int efeito_item(Piloto *piloto, Itens *estoque);
int fator_sorte();
int dificuldade_pista(Corrida *corrida);
int calcular_resultado(Piloto *piloto, Corrida *corrida, Itens *estoque);

TipoEvento sortear_evento();
const char *nome_evento(TipoEvento evento);
void aplicar_evento(TipoEvento evento, ResultadoPiloto ranking[], int num_participantes);

//preenche 'ranking' (ja alocado pelo chamador, tamanho >= num_participantes) com o resultado
//de cada participante, aplica um evento especial sorteado e ordena do 1o ao ultimo colocado
void simular_corrida(Corrida *corrida, NoPiloto *participantes[], int num_participantes, Itens *estoque, ResultadoPiloto ranking[]);

void exibir_ranking(Corrida *corrida, ResultadoPiloto ranking[], int num_participantes);

void simulacao_final(HeapCorridas *central, Historico **historico, Oficina *oficina, NoPiloto *lista, Itens *estoque, Camp **campeonato, Camp **ranktot, int temporada);

void end_temp(Camp **campeonato, HeapCorridas *central, int *temporada);

#endif