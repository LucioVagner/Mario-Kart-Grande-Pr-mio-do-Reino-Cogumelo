
#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"
#include "pilotos.h"
#include "karts.h"
#include "corridas.h"
#include "itens.h"

//formulando o desempenho

int desempenho_piloto(Piloto *piloto){
    int base;

    switch(piloto->categoria){
        case 1: base = 60; break; //leve
        case 2: base = 50; break; //medio
        case 3: base = 40; break; //pesado
        default: base = 50; break;
    }

    int experiencia = piloto->trofeus * 3;
    if(experiencia > 25){
        experiencia = 25;
    }

    return base + experiencia;
}

int bonus_kart(Kart *kart){
    return (kart->vel * 2 + kart->acel + kart->controle) / 4;
}

int efeito_item(Piloto *piloto, Itens *estoque){
    if(piloto->item < 0 || piloto->item > 6){
        return 0;
    }
    int efeito = estoque[piloto->item].power;
    piloto->item = -1;
    return efeito;
}

int fator_sorte(){
    return (rand() % 21) - 10;
}

int dificuldade_pista(Corrida *corrida){
    int dificuldade = corrida->perigo;
    if(corrida->clima == 2){ dificuldade += 5; }
    else if(corrida->clima == 3){ dificuldade += 10; }
    return dificuldade;
}

int calcular_resultado(Piloto *piloto, Corrida *corrida, Itens *estoque){
    return desempenho_piloto(piloto)
         + bonus_kart(&piloto->kart)
         + efeito_item(piloto, estoque)
         + fator_sorte()
         - dificuldade_pista(corrida);
}

//sorteando os eventos

TipoEvento sortear_evento(){
    int chance = rand() % 100;
    if(chance < 45){ return EVENTO_NENHUM; }
    else if(chance < 57){ return EVENTO_CASCO_AZUL; }
    else if(chance < 72){ return EVENTO_BANANA; }
    else if(chance < 84){ return EVENTO_COGUMELO; }
    else if(chance < 94){ return EVENTO_BOBOMB; }
    else { return EVENTO_RAIO; }
}

const char *nome_evento(TipoEvento evento){
    switch(evento){
        case EVENTO_CASCO_AZUL: return "Casco Azul";
        case EVENTO_BANANA: return "Banana";
        case EVENTO_COGUMELO: return "Cogumelo";
        case EVENTO_BOBOMB: return "Bob-omb";
        case EVENTO_RAIO: return "Raio";
        case EVENTO_NENHUM:
        default: return "Nenhum";
    }
}

void aplicar_evento(TipoEvento evento, ResultadoPiloto ranking[], int num_participantes){
    int alvo;
    if(num_participantes <= 0){ return; }

    switch(evento){
        case EVENTO_CASCO_AZUL:{
            int lider = 0;
            for(int i = 1; i < num_participantes; i++){
                if(ranking[i].resultado > ranking[lider].resultado){ lider = i; }
            }
            ranking[lider].resultado -= 15;
            ranking[lider].evento = EVENTO_CASCO_AZUL;
            break;
        }
        case EVENTO_BANANA:
            alvo = rand() % num_participantes;
            ranking[alvo].resultado -= 10;
            ranking[alvo].evento = EVENTO_BANANA;
            break;
        case EVENTO_COGUMELO:
            alvo = rand() % num_participantes;
            ranking[alvo].resultado += 15;
            ranking[alvo].evento = EVENTO_COGUMELO;
            break;
        case EVENTO_BOBOMB:
            alvo = rand() % num_participantes;
            ranking[alvo].resultado -= 25;
            ranking[alvo].evento = EVENTO_BOBOMB;
            break;
        case EVENTO_RAIO:
            for(int i = 0; i < num_participantes; i++){
                ranking[i].resultado -= 8;
                ranking[i].evento = EVENTO_RAIO;
            }
            break;
        case EVENTO_NENHUM:
        default:
            break;
    }
}

static int comparar_resultado(const void *a, const void *b){
    const ResultadoPiloto *ra = (const ResultadoPiloto*) a;
    const ResultadoPiloto *rb = (const ResultadoPiloto*) b;
    return rb->resultado - ra->resultado;
}

void simular_corrida(Corrida *corrida, NoPiloto *participantes[], int num_participantes, Itens *estoque, ResultadoPiloto ranking[]){
    if(num_participantes <= 0){ return; }
    if(num_participantes > MAX_PARTICIPANTES){ num_participantes = MAX_PARTICIPANTES; }

    for(int i = 0; i < num_participantes; i++){
        ranking[i].no = participantes[i];
        ranking[i].resultado = calcular_resultado(&participantes[i]->piloto, corrida, estoque);
        ranking[i].evento = EVENTO_NENHUM;
    }

    TipoEvento evento = sortear_evento();
    aplicar_evento(evento, ranking, num_participantes);

    qsort(ranking, num_participantes, sizeof(ResultadoPiloto), comparar_resultado);
}

void exibir_ranking(Corrida *corrida, ResultadoPiloto ranking[], int num_participantes){
    printf("\n===================== RESULTADO DA CORRIDA =====================\n");
    printf("Pista: %s\n\n", corrida->nome);
    for(int i = 0; i < num_participantes; i++){
        printf("%dº lugar | Piloto: %-20s | Resultado: %d", i + 1, ranking[i].no->piloto.nome, ranking[i].resultado);
        if(ranking[i].evento != EVENTO_NENHUM){
            printf("  [Evento: %s]", nome_evento(ranking[i].evento));
        }
        printf("\n");
    }
    printf("==================================================================\n");
}