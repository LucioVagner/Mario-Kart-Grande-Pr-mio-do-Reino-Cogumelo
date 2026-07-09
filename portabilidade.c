#include "portabilidade.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>


void inicializar_terminal() {
    system("chcp 65001 > nul");
    SetConsoleOutputCP(CP_UTF8);
}

void limpar_tela() {
    system("cls");
}

void esperar(int ms) {
    Sleep(ms);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#else

#include <unistd.h>



void inicializar_terminal() {}

void limpar_tela() {
    system("clear");
}

void esperar(int ms) {
    usleep(ms * 1000);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#endif