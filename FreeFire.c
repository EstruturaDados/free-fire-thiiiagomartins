// inclui o arquivo de cabeçalho com as definições e protótipos
#include "FreeFire.h"

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
int main() {
    int opcao_principal;
    int opcao_operacao;

    printf("#### MOCHILA DE SOBREVIVÊNCIA - CODIGO DA ILHA ####\n");
    do {
        printf("\n##### MENU PRINCIPAL #####\n");
        printf("------------------------------------------\n");
        printf("1. Gerenciar MOCHILA (VETOR)\n");
        printf("2. Gerenciar MOCHILA (LISTA ENCADEADA)\n");
        printf("3. Comparar Desempenho (Contadores)\n");
        printf("0. Sair do Jogo\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao_principal) != 1) {
            opcao_principal = -1;
        }
        while (getchar() != '\n');

        switch (opcao_principal) {
            case 1:
            case 2: {
                estruturaAtual = opcao_principal;
                const char* nome_estrutura = (estruturaAtual == 1) ? "VETOR" : "LISTA ENCADEADA";
                do {
                    // exibe o menu de operações
                    exibirMenuOperacoes(nome_estrutura);
                    if (scanf("%d", &opcao_operacao) != 1) {
                        opcao_operacao = -1;
                    }
                    while (getchar() != '\n');

                    // Chama a função correspondente à operação escolhida
                    switch (opcao_operacao) {
                        case 1: inserirItem(); break;
                        case 2: removerItem(); break;
                        case 3: mostrarComponentes(); break;
                        case 4:
                            // Opção 4 é Busca Sequencial na LISTA, OU Ordenar/Buscar no VETOR
                            if (estruturaAtual == 1) {
                                // 4. Ordenar os itens por critério (nome, tipo, prioridade)
                                if (numItensVetor <= 1) {
                                    printf("\n[ALERTA] É necessário ter pelo menos 2 itens para ordenar.\n");
                                    break;
                                }
                                // chama o menu de ordenar
                                menuDeOrdenacao();
                            } else {
                                char nomeBusca[30];
                                Item* itemEncontrado = NULL;

                                printf("Digite o Nome do Item: ");
                                if (scanf("%29s", nomeBusca) == 1) {
                                    itemEncontrado = buscarItem(nomeBusca, false);
                                }
                                while (getchar() != '\n');
                                if (itemEncontrado != NULL) {
                                    printf("\n[SUCESSO] Item '%s' encontrado.\n", nomeBusca);
                                    exibirDetalhesItem(itemEncontrado);
                                    printf("------------------------------------------\n");
                                } else {
                                    printf("\n[ALERTA] Item '%s' NÃO encontrado na mochila.\n", nomeBusca);
                                    printf("------------------------------------------\n");
                                }
                            }
                            break;
                        case 5:
                        case 6: {
                            // 5. Realizar busca binária por nome
                            if (estruturaAtual == 2) {
                                printf("\n[ERRO] Opção inválida. Escolha uma opção de 0 - 4\n");
                                break;
                            }
                            if (!verificarOrdenacao()) {
                                printf("\n[ALERTA] A busca binária requer que a mochila esteja ordenada por NOME.\n");
                                printf("Use a opção [4] para organizar a mochila primeiro.\n");
                                pressioneEnter();
                                limparTela();
                                break;
                            }
                            char nomeBusca[30];
                            Item* itemEncontrado = NULL;
                            // faz a busca do Item
                            // removido pois não existe mais a busca sequencial em vetor
                            // bool tipoBusca = (opcao_operacao == 6);
                            bool tipoBusca = true;
                            const char *mensagem = tipoBusca
                                ? "Nome do componente a buscar (Binária - exige ordenação): "
                                : "Nome do componente a buscar (Sequencial): ";
                            printf("%s", mensagem);

                            if (scanf("%29s", nomeBusca) == 1) {
                                itemEncontrado = buscarItem(nomeBusca, tipoBusca);
                            }
                            while (getchar() != '\n');

                            if (itemEncontrado != NULL) {
                                printf("\n[SUCESSO] Item '%s' encontrado.\n", nomeBusca);
                                exibirDetalhesItem(itemEncontrado);
                                printf("------------------------------------------\n");
                            } else {
                                printf("\n[ALERTA] Item '%s' NÃO encontrado na mochila.\n", nomeBusca);
                                printf("------------------------------------------\n");
                            }

                            break;
                        }
                        case 0:
                            break;
                        default:
                            printf("\n[ERRO] Opção inválida!\n");
                            break;
                    }
                } while (opcao_operacao != 0);
                break;
            }
            case 3:
                printf("\n[EM DESENVOLVIMENTO] Aqui será exibido o comparativo de desempenho.\n");
                break;
            case 0:
                printf("\n[FIM DE JOGO] Inventário encerrado. Boa sorte na sua sobrevivência!\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida. Tente novamente!\n");
                break;
        }
    } while (opcao_principal != 0);

    return 0;
}

// Struct Item: - OK
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila: - OK
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem(): - OK
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem(): - OK
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens(): - OK
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

// buscaBinariaPorNome(): - OK
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
