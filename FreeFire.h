#ifndef FREEFIRE_H
#define FREEFIRE_H

// Bibliotecas necessárias (incluídas aqui para serem usadas em FreeFire.c e utils.c)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// -----------------------------------------------------------------------------
// Definição da Constante
// -----------------------------------------------------------------------------
#define CAPACIDADE_MAXIMA 10
#define TAMANHO_NOME 30
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
    TIPO_ESTRUTURAL,
    TIPO_ELETRONICO,
    TIPO_ENERGIA,
    TIPO_SUPORTE,
    TIPO_CONTROLE,
    TOTAL_TIPOS
} TipoItem;

typedef enum {
    CRITERIO_NOME,
    CRITERIO_TIPO,
    CRITERIO_PRIORIDADE
} CriterioOrdenacao;

// -----------------------------------------------------------------------------
// Definição da Struct (Estrutura de Dados Composta)
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    TipoItem tipo;
    int quantidade;
    int prioridade;
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
void mostrarComponentes();
void ordenarItens(CriterioOrdenacao criterio);
bool verificarOrdenacao();
Item* buscarItem(const char *nomeBusca, bool buscaBinaria);
void pressioneEnter();
void menuDeOrdenacao();
int buscaBinariaPorNome(Item mochila[], const char *nomeBusca);
void medirTempo(clock_t inicio, clock_t fim, long long comparacoes);
void bubbleSortNome(Item mochila[], int tamanho);
void insertionSortTipo(Item mochila[], int tamanho);
void selectionSortPrioridade(Item mochila[], int tamanho);
void limparTela();

const char* tipoItemToString(TipoItem tipo);
const char* criterioToString(CriterioOrdenacao criterio);

#endif