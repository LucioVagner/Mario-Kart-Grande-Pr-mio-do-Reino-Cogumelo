#ifndef KARTS_H
#define KARTS_H

typedef struct car{
    char nome[50];
    int vel;
    int acel;
    int controle;
    int durabil;
    int status;
}Kart;

Kart select_kart();   

void listar_karts(Kart karts[], int tam);

void exibir_kart(Kart kart);

void att_kart_status(Kart *kart, int status);
#endif