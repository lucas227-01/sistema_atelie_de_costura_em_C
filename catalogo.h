// catalogo.h
#ifndef CATALOGO_H
#define CATALOGO_H

#include "dados.h"

void cadastrar_servico();
void listar_servicos();
void editar_servico();
void excluir_servico();

// Funções utilitárias usadas entre módulos
int buscar_servico_por_id(int id, Servico *s);
int gerar_proximo_id_servico();

#endif