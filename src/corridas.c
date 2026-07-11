#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pilotos.h"
#include "karts.h"
#include "corridas.h"
#include "portabilidade.h"

//funcao para inicializar as pistas no começo do codigo, assim que iniciar o programa
Corrida *cria_pistas(){
    Corrida *pistas = (Corrida*) malloc(5 * sizeof(Corrida));

    if(pistas == NULL){
        printf("ERRO DE ALOCAÇÃO!\n");
        return NULL;
    }

    strcpy(pistas[0].nome, "Rainbow Road");
    strcpy(pistas[1].nome, "Bowser's Castle");
    strcpy(pistas[2].nome, "Mario Circuit");
    strcpy(pistas[3].nome, "Sherbet Land");
    strcpy(pistas[4].nome, "Coconut Mall");

    pistas[0].perigo = 95;
    pistas[1].perigo = 85;
    pistas[2].perigo = 40;
    pistas[3].perigo = 60;
    pistas[4].perigo = 25;
    
    pistas[0].voltas = 3;
    pistas[1].voltas = 3;
    pistas[2].voltas = 5;
    pistas[3].voltas = 4;
    pistas[4].voltas = 3;


    for(int i = 0; i < 5; i++){
        pistas[i].clima = (rand() % 3 ) + 1;
        pistas[i].status = 0;
        pistas[i].prioridade = i;
    }

    return pistas;
}
//lista todas as pistas para serem simuladas
void lista_pistas(HeapCorridas *heap){
    if(heap->tamanho == 0){
        printf("Nenhuma pista disponível na Central Digital.\n");
        return;
    }

    printf("\n------------------------------------------\n\n|\tPISTAS RESTANTES NA CENTRAL CORRIDAS\t|\n\n------------------------------------------\n");
    for(int i = 0; i < heap->tamanho; i++){
        printf("[%d] %s\nPerigo: %d\nVoltas: %d\n", i+1, heap->corridas[i].nome, heap->corridas[i].perigo, heap->corridas[i].voltas);   
    }
}
//inicia as prioridade das corridas
void iniciar_heap(HeapCorridas *heap, Corrida *pistas){
    heap->tamanho = 0;
    heap->capacidade = 5;


    for(int i = 0; i < 5; i++){
        heap->corridas[i] = pistas[i];
        heap->tamanho++;
        heap->corridas[i].prioridade = i;
        heapify_up(heap, i); //entra na funçao para colocar a com a maior prioridade no topo do heap
    }
}
//funcao pra colocar no topo
void heapify_up(HeapCorridas *heap, int i){
    int pai = (i-1)/2;

    if (i > 0){
        if((heap->corridas[i].perigo > heap->corridas[pai].perigo) || (heap->corridas[i].perigo == heap->corridas[pai].perigo && heap->corridas[i].prioridade < heap->corridas[pai].prioridade)){
            Corrida aux = heap->corridas[i];
            heap->corridas[i] = heap->corridas[pai];
            heap->corridas[pai] = aux;

            heapify_up(heap, pai); //se chama recursivamente
        }
    }
}

void heapify_down(HeapCorridas *heap, int i){
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int maior = i;

    if(esq < heap->tamanho && ((heap->corridas[esq].perigo > heap->corridas[maior].perigo ) || (heap->corridas[esq].perigo == heap->corridas[maior].perigo && heap->corridas[esq].prioridade < heap->corridas[maior].prioridade))){
        maior = esq;
    }
    if(dir < heap->tamanho && ((heap->corridas[dir].perigo > heap->corridas[maior].perigo )|| (heap->corridas[dir].perigo == heap->corridas[maior].perigo && heap->corridas[dir].prioridade < heap->corridas[maior].prioridade))){
        maior = dir;
    }

    if (maior != i){ //mudou de lugar
        Corrida aux = heap->corridas[i];
        heap->corridas[i] = heap->corridas[maior];
        heap->corridas[maior] = aux;

        heapify_down(heap, maior); //precisa conferir todos
    }
}

Corrida remover_corrida(HeapCorridas *heap){
    if(heap->tamanho == 0){
        printf("Nenhuma pista disponível na Central Digital.\n");
        Corrida vazia = {"", 0, 0, 0, 0, 0, {0}}; // Correção do warning aqui!
        return vazia;
    }

    Corrida topo = heap->corridas[0];
    heap->corridas[0] = heap->corridas[heap->tamanho - 1];

    heap->tamanho--;

    if (heap->tamanho > 0){
        heapify_down(heap, 0);
    }

    return topo;
}

// ESTA FUNÇÃO PRECISA ESTAR AQUI (ANTES DO MENU)
static void exibir_corrida(Corrida corrida){
    char *climas[4] = {"", "Ensolarado", "Chuvoso", "Nevando"};
    printf("\n========================= CORRIDA PREPARADA =========================\n");
    printf("Pista: %s\n", corrida.nome);
    printf("Numero de Voltas: %d\n", corrida.voltas);
    printf("Nivel de Perigo: %d\n", corrida.perigo);
    if(corrida.clima >= 1 && corrida.clima <= 3){
        printf("Condicao Climatica: %s\n", climas[corrida.clima]);
    }
    printf("=======================================================================\n");
}

// NOVO MENU
void menu_corrida(HeapCorridas *central){
    int opcao;
    do{
        printf("\n========================== Corridas ==================================\n");
        printf("| [1] Visualizar pistas restantes na Central.                        |\n");        
        printf("| [2] Preparar proxima corrida (remove a de maior prioridade).       |\n");        
        printf("| [0] para voltar.                                                   |\n");        
        printf("|                                                                    |\n======================================================================\n");        
        printf("Digite o que deseja fazer: ");        
        while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 2){            
            limpar_buffer();            
            printf("ERRO! DIGITE NOVAMENTE.\n");        
        }        
        switch(opcao){            
            case 1:                
                lista_pistas(central);                
                printf("\nAperte ENTER para retornar...");                
                limpar_buffer();                
                getchar();                
                limpar_tela();                
                break;            
            case 2:                
                if(central->tamanho == 0){                    
                    printf("Nenhuma pista disponivel na Central Digital.\n");                
                } else {                    
                    Corrida atual = remover_corrida(central);                    
                    exibir_corrida(atual);                    
                    /* TODO(próxima missão): repassar 'atual' para a Fase de Simulacao */                
                }                
                esperar(5000);                
                limpar_tela();                
                break;            
            case 0:                
                break;        
        }    
    }while(opcao != 0);
}