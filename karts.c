#include <stdio.h>
#include <stdlib.h>
#include "pilotos.h"
#include "karts.h"

Kart select_kart(){
    Kart karts[3];
    int choose;

    strcpy(karts[0].nome, "Standard Kart");
    karts[0].vel = 50;
    karts[0].acel = 50;
    karts[0].controle = 50;
    karts[0].durabil = 50;
    karts[0].status = 0;

    strcpy(karts[1].nome, "Pipe Frame");
    karts[1].vel = 70;
    karts[1].acel = 40;
    karts[1].controle = 60;
    karts[1].durabil = 30;
    karts[1].status = 0;

     strcpy(karts[2].nome, "Mach 8");
    karts[2].vel = 90;
    karts[2].acel = 30;
    karts[2].controle = 40;
    karts[2].durabil = 40;
    karts[2].status = 0;

    listar_karts(karts, 3);
    printf("[0] Standard Kart.\t [1] Pipe Frame.\t [2] Mach 8\n");
    printf("Selecione o tipo do kart: ");
    while(scanf("%d", &choose) != 1 || choose < 0 || choose > 2){
        while(getchar() != '\n');
        printf("ERRO! DIGITE UMA ENTRADA VALIDA.\n");
    }

    return karts[choose];
}

void listar_karts(Kart karts[], int tam){
    printf("====================== STATUS DOS KARTS ======================\n\n");
    for(int i = 0; i < tam; i++){
        printf("TIPO: %s\n", karts[i].nome);
        printf("Velocidade: %d\n", karts[i].vel);
        printf("Aceleração: %d\n", karts[i].acel);
        printf("Controle: %d\n", karts[i].controle);
        printf("Durabilidade: %d\n", karts[i].durabil);
        printf("========================================\n\n");
    }
}

void exibir_kart(NoPiloto *lista){
    printf("TIPO: %s\n", lista->piloto.kart.nome);
        printf("Velocidade: %d\n", lista->piloto.kart.vel);
        printf("Aceleração: %d\n", lista->piloto.kart.acel);
        printf("Controle: %d\n", lista->piloto.kart.controle);
        printf("Durabilidade: %d\n", lista->piloto.kart.durabil);
}

void att_kart_status(NoPiloto *lista, int status){
    
    lista->piloto.kart.status = status;
}