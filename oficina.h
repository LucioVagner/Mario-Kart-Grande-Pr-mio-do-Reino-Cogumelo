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
    char piloto[10][50];
    int tam;
}HeapOficina;

typedef struct{
    FilaOficina damaged;
    HeapOficina destruct;
} Oficina;


void put_kart(FilaOficina *atual, Kart kart, char pilot[]);

void put_destroyed(HeapOficina *heap, Kart kart, char pilot[]);

void heapup_oficina(HeapOficina *heap, int tam);

void heapdown_oficina(HeapOficina *heap, int tam);

Kart repair_destructed(HeapOficina *heap);

Kart repair_damaged(FilaOficina *fila);

void consulta_oficina(Oficina *oficina);

void menu_oficina(Oficina *oficina);
#endif