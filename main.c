// main.c
#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "catalogo.h"
#include "pedidos.h"
#include "interface.h"

void exibir_menu() {
    printf("=== SISTEMA DE GESTAO - %s ===\n", NOME_ATELIE);
    printf("1. Lancar Servico (Nova Nota)\n");
    printf("2. Cadastrar Servico no Catalogo\n");
    printf("3. Listar Servicos do Catalogo\n");
    printf("4. Editar Servico do Catalogo\n");
    printf("5. Excluir Servico do Catalogo\n");
    printf("6. Listar Notas por Data de Entrega\n");
    printf("7. Sair do Sistema\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao = 0;

    do {
        limpar_tela();
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer(); // Trata o buffer logo após a escolha do menu

        switch (opcao) {
            case 1:
                limpar_tela();
                lancar_servico();
                aguardar_enter();
                break;
            case 2:
                limpar_tela();
                cadastrar_servico();
                aguardar_enter();
                break;
            case 3:
                limpar_tela();
                listar_servicos();
                aguardar_enter();
                break;
            case 4:
                limpar_tela();
                editar_servico();
                aguardar_enter();
                break;
            case 5:
                limpar_tela();
                excluir_servico();
                aguardar_enter();
                break;
            case 6:
                limpar_tela();
                listar_notas_por_data();
                aguardar_enter();
                break;
            case 7:
                printf("\nObrigado por utilizar o sistema. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                aguardar_enter();
        }
    } while (opcao != 7);

    return 0;
}