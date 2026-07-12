#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"
#include "karts.h"
#include "portabilidade.h"
//inicializa os karts e faz o player selecionar o tipo de kart
Kart select_kart(){
    Kart karts[3];
    int choose;

    strcpy(karts[0].nome, "Standard Kart");
    karts[0].vel = 50;
    karts[0].acel = 50;
    karts[0].controle = 50;
    karts[0].durabil = 50;
    karts[0].status = 0;
    karts[0].damage = 100;

    strcpy(karts[1].nome, "Pipe Frame");
    karts[1].vel = 70;
    karts[1].acel = 40;
    karts[1].controle = 60;
    karts[1].durabil = 30;
    karts[1].status = 0;
    karts[1].damage = 100;  

    strcpy(karts[2].nome, "Mach 8");
    karts[2].vel = 90;
    karts[2].acel = 30;
    karts[2].controle = 40;
    karts[2].durabil = 40;
    karts[2].status = 0;
    karts[2].damage = 100;

    listar_karts(karts, 3);
    printf("[0] Standard Kart.\t [1] Pipe Frame.\t [2] Mach 8\n");
    printf("Selecione o tipo do kart: ");
    while(scanf("%d", &choose) != 1 || choose < 0 || choose > 2){
        while(getchar() != '\n');
        printf(RED "ERRO! DIGITE UMA ENTRADA VALIDA.\n"RESET);
    }

    return karts[choose];
}
//lista os karts para a seleção 
void listar_karts(Kart karts[], int tam){
    printf(CYAN"====================== STATUS DOS KARTS ======================\n\n"RESET);
    for(int i = 0; i < tam; i++){
        printf("TIPO: "YELLOW BOLD" %s" RESET "\n", karts[i].nome);
        printf("Velocidade: "GREEN BOLD" %d"RESET"\n", karts[i].vel);
        printf("Aceleração: "MAGENTA BOLD"%d\n"RESET, karts[i].acel);
        printf("Controle: "CYAN BOLD"%d\n"RESET, karts[i].controle);
        printf("Durabilidade: "RED BOLD"%d\n"RESET, karts[i].durabil);
        printf(CYAN"\n========================================\n\n"RESET);
    }
}
//lista kart por piloto
void exibir_kart(Kart kart){
        printf("Nome: "YELLOW BOLD"%s\n"RESET, kart.nome);
        printf("Velocidade: "GREEN BOLD"%d\n" RESET, kart.vel);
        printf("Aceleração: "MAGENTA BOLD"%d\n"RESET, kart.acel);
        printf("Controle: "CYAN BOLD"%d\n"RESET, kart.controle);
        printf("Durabilidade: "RED BOLD"%d\n"RESET, kart.durabil);
}

