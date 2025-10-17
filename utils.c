#include "FreeFire.h"

// -----------------------------------------------------------------------------
// 1. Variáveis Globais (Dados do Módulo)
// -----------------------------------------------------------------------------
Item mochila[CAPACIDADE_MAXIMA];
int numItens = 0;

// -----------------------------------------------------------------------------
// 2. Implementação das Funções
// -----------------------------------------------------------------------------

const char* tipoItemToString(TipoItem tipo) {
    switch (tipo) {
        case TIPO_ARMA: return "Arma";
        case TIPO_MUNICAO: return "Municao";
        case TIPO_CURA: return "Cura";
        case TIPO_FERRAMENTA: return "Ferramenta";
        case TIPO_PROTECAO: return "Protecao";
        case TIPO_INVALIDO:
        default: return "INVÁLIDO";
    }
}

void exibirDadosItem(int indice) {
    if (indice >= 0 && indice < numItens) {
        printf("Nome: %s\n", mochila[indice].nome);
        printf("Tipo: %s\n", mochila[indice].tipo);
        printf("Quantidade: %d\n", mochila[indice].quantidade);
    }
}

// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    printf("\n#### ITENS NA MOCHILA (%d/%d) ####\n", numItens, CAPACIDADE_MAXIMA);
    if (numItens == 0) {
        printf("A mochila está vazia. Colete alguns itens!\n");
        return;
    }

    printf("NRO.| %-28s | %-18s | %s \n", "NOME", "TIPO", "QUANTIDADE");
    // Percorre o vetor de structs
    for (int i = 0; i < numItens; i++) {
        printf("--------------------------------------------------------------------\n");
        printf("%-4d| %-28s | %-18s | %-12d \n",
            i + 1,
            mochila[i].nome,
            tipoItemToString(mochila[i].tipo),
            mochila[i].quantidade
        );
    }
    printf("--------------------------------------------------------------------\n");
}

int buscarItem(const char *nomeBusca) {
    // Procura o item na listagem
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Produto encontrado
            return i;
        }
    }
    // Produto não encontrado
    return -1;
}

// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (numItens >= CAPACIDADE_MAXIMA) {
        printf("\n[ALERTA] A mochila está cheia! Não é possível carregar mais itens.\n");
        return;
    }
    int tipo_int;
    printf("\n### NOVO ITEM ####\n");
    // Leitura do Nome
    printf("Nome do Item (sem espaços, max 29 chars): ");
    if (scanf("%29s", mochila[numItens].nome) != 1) {
        printf("[ERRO] Falha na leitura do nome, máximo de 29 caracteres.\n");
        return;
    }

    // Leitura do Tipo
    printf("\n[SELECIONE UM TIPO ABAIXO]\n");
    printf("1: Arma | 2: Municao | 3: Cura | 4: Ferramenta | 5: Protecao\n");
    printf("Número do Tipo do Item: ");
    // Verifica se foi digitado um número inteiro
    if (scanf("%d", &tipo_int) != 1) {
        printf("[ERRO] Entrada inválida. Digite um número de 1-5! Item não cadastrado.\n");
        while (getchar() != '\n');
        return;
    }
    //Converte o inteiro lido para o TipoItem (enum)
    TipoItem novo_tipo = (TipoItem)tipo_int;

    //Verifica se a opção existe
    if (novo_tipo <= TIPO_INVALIDO || novo_tipo >= TOTAL_TIPOS) {
        printf("[ERRO] Tipo inválido, digite um número de 1-5! Item não cadastrado.\n");
        return;
    }
    // Armazena o enum válido na struct
    mochila[numItens].tipo = novo_tipo;

    // Leitura da Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &mochila[numItens].quantidade) != 1) {
        printf("[ERRO] Quantidade inválida. Item não cadastrado.\n");
        while (getchar() != '\n'); // Limpa buffer
        return;
    }

    // aumenta a quantidade de produtos na lista
    numItens++;
    printf("\n[SUCESSO] Item '%s' adicionado à mochila!\n", mochila[numItens - 1].nome);
    // retorna a lista com os produtos inseridos
    listarItens();
}

// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    char nomeParaRemover[30];
    
    if (numItens == 0) {
        printf("\n[ALERTA] A mochila está vazia. Nada para remover.\n");
        return;
    }
    // Exibe a listagem com os itens a serem removidos
    listarItens();
    printf("\n#### REMOVER ITEM ####\n");
    printf("Digite o Nome do Item para remover (sem espaços): ");
    if (scanf("%29s", nomeParaRemover) != 1) {
        printf("[ERRO] Falha na leitura do nome.\n");
        return;
    }
    
    // Localiza o item que será removido
    int indice = buscarItem(nomeParaRemover);

    // Verifica se o item existe
    if (indice == -1) {
        printf("\n[ALERTA] Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    } else {
        // Reordena a lista de itens
        for (int i = indice; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        // Reduz um item no contador
        numItens--;
        
        printf("\n[SUCESSO] Item '%s' removido da mochila.\n", nomeParaRemover);
        listarItens(); 
    }
}