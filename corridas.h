#ifndef CORRIDAS_H
#define CORRIDAS_H

typedef struct pista{
    char nome[50];
    int voltas;
    int perigo;
    int clima;
    int status;
    int prioridade;
}Corrida;

typedef struct {
    Corrida corridas[5];
    int tamanho;
    int capacidade;

} HeapCorridas;

#endif