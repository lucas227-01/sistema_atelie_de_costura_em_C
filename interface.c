// interface.c
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void limpar_tela() {
    // Detecta o Sistema Operacional para rodar o comando correto de terminal
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limpar_buffer() {
    int c;
    // Consome todos os caracteres restantes no buffer até o fim da linha
    while ((c = getchar()) != '\n' && c != EOF);
}

void aguardar_enter() {
    printf("\nPressione [Enter] para continuar...");
    limpar_buffer();
}