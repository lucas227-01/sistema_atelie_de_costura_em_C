// catalogo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "interface.h"

int gerar_proximo_id_servico() {
    FILE *arq = fopen("catalogo.txt", "r");
    if (!arq) return 1;

    int id, maior_id = 0, ativo;
    char nome[50];
    float preco;

    while (fscanf(arq, "%d;%[^;];%f;%d\n", &id, nome, &preco, &ativo) != EOF) {
        if (id > maior_id) {
            maior_id = id;
        }
    }
    fclose(arq);
    return maior_id + 1;
}

void cadastrar_servico() {
    FILE *arq = fopen("catalogo.txt", "a");
    if (!arq) {
        printf("Erro ao abrir o arquivo do catalogo!\n");
        return;
    }

    Servico s;
    s.id = gerar_proximo_id_servico();
    s.ativo = 1;

    printf("\n--- CADASTRO DE SERVICO ---\n");
    printf("ID Gerado: %d\n", s.id);
    
    printf("Nome do Servico (Pode usar espacos): ");
    scanf(" %[^\n]", s.nome); // <-- Agora aceita espaços!
    
    printf("Preco Base: R$ ");
    scanf("%f", &s.preco);
    limpar_buffer(); 

    fprintf(arq, "%d;%s;%.2f;%d\n", s.id, s.nome, s.preco, s.ativo);
    fclose(arq);

    printf("\nServico cadastrado com sucesso!\n");
}

void listar_servicos() {
    FILE *arq = fopen("catalogo.txt", "r");
    if (!arq) {
        printf("\nNenhum servico cadastrado ainda no sistema.\n");
        return;
    }

    int id, ativo;
    char nome[50];
    float preco;
    int encontrou = 0;

    printf("\n--- SERVICOS DISPONIVEIS ---\n");
    printf("ID  | Nome do Servico       | Preco\n");
    printf("------------------------------------\n");

    while (fscanf(arq, "%d;%[^;];%f;%d\n", &id, nome, &preco, &ativo) != EOF) {
        if (ativo == 1) {
            printf("%-3d | %-21s | R$ %.2f\n", id, nome, preco);
            encontrou = 1;
        }
    }
    fclose(arq);

    if (!encontrou) {
        printf("Nenhum servico ativo encontrado.\n");
    }
}

int buscar_servico_por_id(int id_busca, Servico *s_retorno) {
    FILE *arq = fopen("catalogo.txt", "r");
    if (!arq) return 0;

    int id, ativo;
    char nome[50];
    float preco;
    int achou = 0;

    while (fscanf(arq, "%d;%[^;];%f;%d\n", &id, nome, &preco, &ativo) != EOF) {
        if (id == id_busca && ativo == 1) {
            s_retorno->id = id;
            strcpy(s_retorno->nome, nome);
            s_retorno->preco = preco;
            s_retorno->ativo = ativo;
            achou = 1;
            break;
        }
    }
    fclose(arq);
    return achou;
}

void editar_servico() {
    int id_busca;
    printf("\nDigite o ID do servico que deseja editar: ");
    scanf("%d", &id_busca);
    limpar_buffer(); 

    Servico s;
    if (!buscar_servico_por_id(id_busca, &s)) {
        printf("Servico nao encontrado ou inativo.\n");
        return;
    }

    FILE *arq = fopen("catalogo.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    int id, ativo;
    char nome[50];
    float preco;

    printf("\nDados atuais: %s - R$ %.2f\n", s.nome, s.preco);
    printf("Novo Nome (Pode usar espacos): ");
    scanf(" %[^\n]", s.nome); // <-- Agora aceita espaços!
    
    printf("Novo Preco: R$ ");
    scanf("%f", &s.preco);
    limpar_buffer(); 

    while (fscanf(arq, "%d;%[^;];%f;%d\n", &id, nome, &preco, &ativo) != EOF) {
        if (id == id_busca) {
            fprintf(temp, "%d;%s;%.2f;%d\n", s.id, s.nome, s.preco, s.ativo);
        } else {
            fprintf(temp, "%d;%s;%.2f;%d\n", id, nome, preco, ativo);
        }
    }

    fclose(arq);
    fclose(temp);

    remove("catalogo.txt");
    rename("temp.txt", "catalogo.txt");

    printf("Servico atualizado com sucesso!\n");
}

void excluir_servico() {
    int id_busca;
    printf("\nDigite o ID do servico que deseja excluir: ");
    scanf("%d", &id_busca);
    limpar_buffer(); 

    FILE *arq = fopen("catalogo.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    int id, ativo, achou = 0;
    char nome[50];
    float preco;

    while (fscanf(arq, "%d;%[^;];%f;%d\n", &id, nome, &preco, &ativo) != EOF) {
        if (id == id_busca) {
            fprintf(temp, "%d;%s;%.2f;0\n", id, nome, preco); 
            achou = 1;
        } else {
            fprintf(temp, "%d;%s;%.2f;%d\n", id, nome, preco, ativo);
        }
    }

    fclose(arq);
    fclose(temp);

    remove("catalogo.txt");
    rename("temp.txt", "catalogo.txt");

    if (achou) printf("Servico excluido com sucesso!\n");
    else printf("Servico nao encontrado.\n");
}