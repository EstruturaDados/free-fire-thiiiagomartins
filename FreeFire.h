#ifndef FREEFIRE_H
#define FREEFIRE_H

// Bibliotecas necessárias (incluídas aqui para serem usadas em FreeFire.c e utils.c)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// Definição da Constante
// -----------------------------------------------------------------------------
#define CAPACIDADE_MAXIMA 10
extern int estruturaAtual;
extern int numItensVetor;
extern int numItensLista;
extern struct No* cabecaLista;
extern long long int contComparacoes;

// -----------------------------------------------------------------------------
// Definição de Enum
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
// Definição da Struct (Estrutura de Dados Composta)
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    TipoItem tipo;
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// -----------------------------------------------------------------------------
// Protótipos das Funções
// -----------------------------------------------------------------------------

// Funções utilitárias (no utils.c)
void exibirMenuOperacoes(const char* nome_estrutura);
void exibirDadosItem(const Item *item, int nro);
void exibirDetalhesItem(const Item *item);
void inserirItem();
void removerItem();
void listarItens();
void ordenarItens();
Item* buscarItem(const char *nomeBusca, bool buscaBinaria);

const char* tipoItemToString(TipoItem tipo);

#endif