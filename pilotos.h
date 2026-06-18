#ifndef PILOTOS_H
#define PILOTOS_H


typedef struct pilotos{
    char nome[50];
    int categoria;
    int vel;
    int trofeus;
    int status; 
}Piloto;

typedef struct NoPiloto{
    Piloto piloto;
    struct NoPiloto* proximo;
    struct NoPiloto* anterior;
}NoPiloto;

NoPiloto* criar_lista_pilotos();

#