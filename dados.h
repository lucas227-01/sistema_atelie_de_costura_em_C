// dados.h
#ifndef DADOS_H
#define DADOS_H

#define NOME_ATELIE "Atelie Agulha de Ouro"
#define TELEFONE_ATELIE "(11) 99999-8888"
#define MAX_SERVICOS_POR_NOTA 10 // Limite de serviços por cliente na mesma nota

typedef struct {
    int id;
    char nome[50];
    float preco;
    int ativo; 
} Servico;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int id_pedido;
    char nome_cliente[50];
    char telefone_cliente[20];
    int ids_servicos[MAX_SERVICOS_POR_NOTA]; // Vetor para guardar vários IDs
    int qtd_servicos;                        // Quantos serviços foram inseridos
    float valor_total;
    Data entrega;
} Pedido;

#endif