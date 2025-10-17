#ifndef INVENTARIO_H
#define INVENTARIO_H

// Bibliotecas necessárias (incluídas aqui para serem usadas em FreeFire.c e utils.c)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// 1. Definição da Constante
// -----------------------------------------------------------------------------
#define CAPACIDADE_MAXIMA 10
extern int numItens;

// -----------------------------------------------------------------------------
// 2. Definição de Enum
// -----------------------------------------------------------------------------
typedef enum {
    TIPO_INVALIDO = 0,
    TIPO_ARMA,
    TIPO_MUNICAO,
    TIPO_CURA,
    TIPO_FERRAMENTA,
    TIPO_PROTECAO,
    TOTAL_TIPOS
} TipoItem;

// -----------------------------------------------------------------------------
// 3. Definição da Struct (Estrutura de Dados Composta)
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    TipoItem tipo;
    int quantidade;
} Item;

// -----------------------------------------------------------------------------
// 4. Protótipos das Funções Públicas (Interface do Módulo)
// -----------------------------------------------------------------------------
void inserirItem();
void removerItem();
void listarItens();
const char* tipoItemToString(TipoItem tipo);

#endif