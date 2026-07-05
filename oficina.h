#ifndef OFICINA_H
#define OFICINA_H
#include "karts.h"

typedef struct nofila{
    Kart kart;
    char piloto[50];
    struct nofila *proximo;
}Nofila;

typedef struct fila{
    Nofila *inicio;
    Nofila *fim;
    int tam;
}FilaOficina;

typedef struct heap{
    Kart karts[10];
    int tam;
}HeapOficina;

typedef struct{
    FilaOficina damaged;
    HeapOficina destruct;
} Oficina;

#endif