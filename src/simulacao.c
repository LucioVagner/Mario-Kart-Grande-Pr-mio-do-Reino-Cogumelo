
#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"
#include "pilotos.h"
#include "karts.h"
#include "corridas.h"
#include "itens.h"
#include "historico.h"
#include "camp.h"
#include "oficina.h"
#include "portabilidade.h"
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

    // Array temporário para guardar os eventos disparados pelos itens nesta corrida
    TipoEvento eventos_gerados[MAX_PARTICIPANTES];

    for(int i = 0; i < num_participantes; i++){
        ranking[i].no = participantes[i];
        ranking[i].evento = EVENTO_NENHUM;
        eventos_gerados[i] = EVENTO_NENHUM;

        int id_item = participantes[i]->piloto.item;

        // 1. Identifica qual evento o item vai causar ANTES de consumi-lo na fórmula
        if(id_item != -1) {
            switch(id_item){
                case 0: eventos_gerados[i] = EVENTO_BANANA; break;
                case 2: eventos_gerados[i] = EVENTO_COGUMELO; break;
                case 3: eventos_gerados[i] = EVENTO_CASCO_AZUL; break; // Casco vermelho engatilhado como evento pesado
                case 4: eventos_gerados[i] = EVENTO_BOBOMB; break;
                case 5: eventos_gerados[i] = EVENTO_RAIO; break;
                // Itens como Casco Verde ou Bullet Bill dão apenas o boost de 'power' e não rodam eventos colaterais de dano
            }
        }

        // 2. Calcula o resultado base (Isso soma o 'power' do item ao dono e reseta o slot para -1)
        ranking[i].resultado = calcular_resultado(&participantes[i]->piloto, corrida, estoque);
    }

    // 3. Aplica o caos na pista rodando os eventos gerados
    for(int i = 0; i < num_participantes; i++){
        if(eventos_gerados[i] != EVENTO_NENHUM){
            aplicar_evento(eventos_gerados[i], ranking, num_participantes);
        }
    }

    // 4. Ordena o ranking final
    qsort(ranking, num_participantes, sizeof(ResultadoPiloto), comparar_resultado);
}

void exibir_ranking(Corrida *corrida, ResultadoPiloto ranking[], int num_participantes){
    printf(GREEN BOLD"\n===================== RESULTADO DA CORRIDA =====================\n"RESET);
    printf("Pista: "CYAN BOLD"%s"RESET"\n\n", corrida->nome);
    for(int i = 0; i < num_participantes; i++){
        printf(MAGENTA BOLD"%dº"RESET" lugar | Piloto: "YELLOW BOLD"%s"RESET" | Resultado: %d pontos", i + 1, ranking[i].no->piloto.nome, ranking[i].resultado);
        if(ranking[i].evento != EVENTO_NENHUM){
            printf("  [Evento: "BOLD"%s"RESET"]", nome_evento(ranking[i].evento));
        }
        printf("\n");
    }
    printf(GREEN BOLD"\n==================================================================\n"RESET);
}

void simulacao_final(HeapCorridas *central, Historico **historico, Oficina *oficina, NoPiloto *lista, Itens *estoque, Camp **campeonato, Camp **ranktot, int temporada){
    int diff;
    int vitoria_absoluta = 0; 

    if(central->tamanho == 0){
        printf("Nenhuma pista disponivel na Central Digital.\n");
        return; // Retorna para não processar nada com o Heap vazio
    } 
    
    Corrida atual = remover_corrida(central);
    limpar_tela();
    exibir_corrida(atual);
    printf("Simulando.");
    fflush(stdout);
    esperar(1000);
    printf(".");
    fflush(stdout);
    esperar(1000);
    printf(".\n\n");
    esperar(2000);

    
    // Agora escala dinamicamente até o limite imposto no .h (10)
    NoPiloto *participantes[MAX_PARTICIPANTES];
    int num_participantes = 0;
    NoPiloto *aux = lista;
    
    while(aux != NULL && num_participantes < MAX_PARTICIPANTES){
        if(aux->piloto.status == 0){
            int item = sorteio(estoque, num_participantes);
            participantes[num_participantes] = aux;
            participantes[num_participantes]->piloto.item = item;
            
            if(item != -1){
                atual.itens[item]++;
            }
            num_participantes++;
        }
        aux = aux->proximo;
    }

    if(num_participantes < 2){
        printf(RED"Pilotos disponiveis insuficientes (minimo 2). Corrida cancelada.\n"RESET);
        return; // Evita quebrar a execução se não tiver quórum
    } 
    
    // Fase de simulacao
    ResultadoPiloto ranking[MAX_PARTICIPANTES];
    simular_corrida(&atual, participantes, num_participantes, estoque, ranking);
    
    diff = ranking[0].resultado - ranking[1].resultado;
    if(diff >= 15){
        ranking[0].no->piloto.trofeus++;
        vitoria_absoluta = 1;
        printf("\nVitória Absoluta.\n\n");
    }else {
        vitoria_absoluta = 0;
        printf("Vitória apertada.\n\n");
    }
    
    for(int i = 0; i < num_participantes; i++){
        ranking[i].resultado = calc_pos(i + 1);
    }
    
    if(vitoria_absoluta != 1){
        ranking[0].resultado = ranking[0].resultado - 2;
    }
    
    exibir_ranking(&atual, ranking, num_participantes);
    
    // Integracao campeonato (arvore AVL)
    for(int i = 0; i < num_participantes; i++){
        if(search((*campeonato), ranking[i].no->piloto.nome) == NULL){
            (*campeonato) = inserir((*campeonato), ranking[i].no->piloto.nome, ranking[i].resultado);
        } else {
            (*campeonato) = att_pont((*campeonato), ranking[i].no->piloto.nome, ranking[i].resultado);
        }
        
        if(search((*ranktot), ranking[i].no->piloto.nome) == NULL){
            (*ranktot) = inserir((*ranktot), ranking[i].no->piloto.nome, ranking[i].resultado);
        } else {
            (*ranktot) = att_pont((*ranktot), ranking[i].no->piloto.nome, ranking[i].resultado);
        }
    }
            
    // Integracao historico dinâmico
    Piloto posicoes_hist[MAX_PARTICIPANTES];
    for(int i = 0; i < num_participantes; i++){
        posicoes_hist[i] = ranking[i].no->piloto;
    }
    (*historico) = registro_fim((*historico), atual, temporada, posicoes_hist, num_participantes);

    // Integracao oficina e danos
    for(int i = 0; i < num_participantes; i++){
        if(ranking[i].evento == EVENTO_BOBOMB){
            ranking[i].no->piloto.kart.damage = 0;
            ranking[i].no->piloto.kart.status = 2; // Destruido
            ranking[i].no->piloto.status = 1;      // Suspenso
            put_destroyed(&oficina->destruct, ranking[i].no->piloto.kart, ranking[i].no->piloto.nome);
        } else if(ranking[i].evento == EVENTO_BANANA){
            ranking[i].no->piloto.kart.damage -= 20;
            if(ranking[i].no->piloto.kart.damage < 20){
                ranking[i].no->piloto.kart.status = 1;
                ranking[i].no->piloto.status = 1;
                put_kart(&oficina->damaged, ranking[i].no->piloto.kart, ranking[i].no->piloto.nome);
            }
        }
    }
}

void end_temp(Camp **campeonato, HeapCorridas *central, int *temporada){
    champion(*campeonato, central);
    esperar(5000);

    liberar_camp(*campeonato);
    *campeonato = NULL;
    
    Corrida *pistas = cria_pistas();
    iniciar_heap(central, pistas);
    free(pistas);

    (*temporada)++;
    printf("\nTemporada %d iniciada!\n", *temporada);
    esperar(3000);

}