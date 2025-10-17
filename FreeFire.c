// inclui o arquivo de cabeçalho com as definições e protótipos
#include "FreeFire.h"

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
int main() {
    int opcao;
    char nomeBusca[30];
    int indiceEncontrado;

    printf("#### MOCHILA DE SOBREVIVÊNCIA - CODIGO DA ILHA ####\n");
    printf("Quantidade de itens: %d/%d\n", numItens, CAPACIDADE_MAXIMA);
    do {
        // Menu principal com opções:
        printf("\n--- MENU DE ITENS ---\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Todos os Itens na Mochila\n");
        printf("0. Sair do Jogo\n");
        printf("--------------------------------\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            while (getchar() != '\n');
        }

        // Estrutura de controle para a interface
        // A estrutura switch trata cada opção chamando a função correspondente.
        // A ordenação e busca binária exigem que os dados estejam bem organizados.
        switch (opcao) {
            case 1:
                // 1. Adicionar um item
                inserirItem();
                break;
            case 2:
                // 2. Remover um item
                removerItem();
                break;
            case 3:
                // 3. Listar todos os itens
                listarItens();
                break;
            case 0:
                // 0. Sair
                printf("\n[FIM DE JOGO] Inventário encerrado. Boa sorte na sua sobrevivência!\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida. Tente novamente!\n");
                break;
        }
    } while (opcao != 0);

    return 0;

    // Menu principal com opções:
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
