// pedidos.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos.h"
#include "catalogo.h"
#include "dados.h"
#include "interface.h"

int gerar_proximo_id_pedido() {
    FILE *arq = fopen("pedidos.txt", "r");
    if (!arq) return 1;

    int id_pedido, d, m, a, qtd;
    float total;
    char nome[50], tel[20], servicos_str[100];
    int maior_id = 0;

    // Lendo o formato atualizado com a string de serviços no meio
    while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%d;%f;%d/%d/%d\n", 
           &id_pedido, nome, tel, servicos_str, &qtd, &total, &d, &m, &a) != EOF) {
        if (id_pedido > maior_id) {
            maior_id = id_pedido;
        }
    }
    fclose(arq);
    return maior_id + 1;
}

void lancar_servico() {
    FILE *valida = fopen("catalogo.txt", "r");
    if (!valida) {
        printf("\n[Erro] Voce precisa cadastrar servicos no catalogo antes de fazer um pedido.\n");
        return;
    }
    fclose(valida);

    Pedido p;
    p.id_pedido = gerar_proximo_id_pedido();
    p.qtd_servicos = 0;
    p.valor_total = 0.0;

    printf("\n--- LANCAR NOVO SERVICO (MULTIPLOS) ---\n");
    
    printf("Nome do Cliente (Pode usar espacos): ");
    scanf(" %[^\n]", p.nome_cliente);
    
    printf("Telefone do Cliente: ");
    scanf("%s", p.telefone_cliente);

    char continuar;
    do {
        limpar_tela();
        printf("\n--- SELECIONE UM SERVICO (Nota #%03d) ---\n", p.id_pedido);
        listar_servicos();

        int id_escolhido;
        printf("\nDigite o ID do servico desejado: ");
        scanf("%d", &id_escolhido);
        limpar_buffer();

        Servico s;
        if (buscar_servico_por_id(id_escolhido, &s)) {
            p.ids_servicos[p.qtd_servicos] = s.id;
            p.valor_total += s.preco;
            p.qtd_servicos++;
            printf("\n=> [%s] adicionado com sucesso! (Subtotal: R$ %.2f)\n", s.nome, p.valor_total);
        } else {
            printf("\n[Erro] ID de servico invalido!\n");
        }

        if (p.qtd_servicos >= MAX_SERVICOS_POR_NOTA) {
            printf("\nLimite maximo de servicos por nota atingido!\n");
            break;
        }

        printf("\nDeseja adicionar mais um servico nesta nota? (S/N): ");
        scanf(" %c", &continuar);
        limpar_buffer();

    } while (continuar == 'S' || continuar == 's');

    printf("\nData de Entrega (DD MM AAAA separados por espaco): ");
    scanf("%d %d %d", &p.entrega.dia, &p.entrega.mes, &p.entrega.ano);
    limpar_buffer();

    // Montando a string de IDs separados por vírgula para gravar no arquivo (ex: "1,2,5")
    char servicos_str[100] = "";
    for (int i = 0; i < p.qtd_servicos; i++) {
        char buffer_id[10];
        sprintf(buffer_id, "%d", p.ids_servicos[i]);
        strcat(servicos_str, buffer_id);
        if (i < p.qtd_servicos - 1) {
            strcat(servicos_str, ",");
        }
    }

    // Salvando no arquivo de pedidos
    FILE *arq = fopen("pedidos.txt", "a");
    if (!arq) {
        printf("Erro ao salvar o pedido.\n");
        return;
    }
    fprintf(arq, "%d;%s;%s;%s;%d;%.2f;%02d/%02d/%04d\n", 
            p.id_pedido, p.nome_cliente, p.telefone_cliente, 
            servicos_str, p.qtd_servicos, p.valor_total, 
            p.entrega.dia, p.entrega.mes, p.entrega.ano);
    fclose(arq);

    // Exibição do Comprovante detalhado com todos os serviços selecionados
    limpar_tela();
    printf("========================================\n");
    printf("          %s\n", NOME_ATELIE);
    printf("     Contato: %s\n", TELEFONE_ATELIE);
    printf("========================================\n");
    printf(" NOTA DE SERVICO NUMERO: #%03d\n", p.id_pedido);
    printf(" Cliente: %s | Tel: %s\n", p.nome_cliente, p.telefone_cliente);
    printf("----------------------------------------\n");
    printf(" Servicos contratados:\n");
    for (int i = 0; i < p.qtd_servicos; i++) {
        Servico s;
        buscar_servico_por_id(p.ids_servicos[i], &s);
        printf("  - %-25s : R$ %.2f\n", s.nome, s.preco);
    }
    printf("----------------------------------------\n");
    printf(" TOTAL A PAGAR: R$ %.2f\n", p.valor_total);
    printf(" DATA DE ENTREGA: %02d/%02d/%04d\n", p.entrega.dia, p.entrega.mes, p.entrega.ano);
    printf("========================================\n\n");
}

void listar_notas_por_data() {
    int d, m, a;
    printf("\nFiltrar Notas por Data de Entrega (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    limpar_buffer();

    FILE *arq = fopen("pedidos.txt", "r");
    if (!arq) {
        printf("\nNenhum pedido lancado no sistema.\n");
        return;
    }

    int id_pedido, entrega_d, entrega_m, entrega_a, qtd;
    float total;
    char nome[50], tel[20], servicos_str[100];
    int encontrou = 0;

    printf("\n--- NOTAS PARA ENTREGA EM %02d/%02d/%04d ---\n", d, m, a);

    while (fscanf(arq, "%d;%[^;];%[^;];%[^;];%d;%f;%d/%d/%d\n", 
           &id_pedido, nome, tel, servicos_str, &qtd, &total, 
           &entrega_d, &entrega_m, &entrega_a) != EOF) {
        
        if (entrega_d == d && entrega_m == m && entrega_a == a) {
            printf("\n========================================\n");
            printf("Nota #%03d | Cliente: %s | Tel: %s\n", id_pedido, nome, tel);
            printf("Servicos:\n");
            
            // Processando a string de IDs separados por vírgula (ex: "1,2") usando strtok
            char *token = strtok(servicos_str, ",");
            while (token != NULL) {
                int id_serv = atoi(token);
                Servico s;
                if (buscar_servico_por_id(id_serv, &s)) {
                    printf("  * %s (R$ %.2f)\n", s.nome, s.preco);
                }
                token = strtok(NULL, ",");
            }
            printf("TOTAL DA NOTA: R$ %.2f\n", total);
            printf("========================================\n");
            encontrou = 1;
        }
    }
    fclose(arq);

    if (!encontrou) {
        printf("Nenhuma nota encontrada para esta data.\n");
    }
}