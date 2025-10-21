#include "FreeFire.h"

// -----------------------------------------------------------------------------
// Variáveis Globais
// -----------------------------------------------------------------------------
Item mochilaVetor[CAPACIDADE_MAXIMA];
int numItensVetor = 0;
int numItensLista = 0;
No* cabecaLista = NULL;
long long int contComparacoes = 0;
// 1=Vetor, 2=Lista
int estruturaAtual = 0;


// Funções Internas
// -----------------------------------------------------------------------------
void exibirDadosItem();
// VETOR
void _inserirVetor();
void _removerVetor();
void _listarVetor();
int _buscarSequencialVetor(const char *nomeBusca);
int _localizarVetor(const char* nomeBusca);
void _ordenarVetor(CriterioOrdenacao criterio);
// LISTA ENCADEADA
void _inserirLista();
void _removerLista();
void _listarLista();
No* _buscarSequencialLista(const char *nomeBusca);
No* _localizarLista(const char* nomeBusca, No** noEncontrado);
Item _preencherItem();

// FUNÇÕES AUXILIARES
// -----------------------------------------------------------------------------
const char* tipoItemToString(TipoItem tipo) {
    switch (tipo) {
        case TIPO_ESTRUTURAL: return "Estrutural";
        case TIPO_ELETRONICO: return "Eletronico";
        case TIPO_ENERGIA: return "Energia";
        case TIPO_SUPORTE: return "Suporte";
        case TIPO_CONTROLE: return "Controle";
        case TIPO_INVALIDO:
        default: return "INVÁLIDO";
    }
}

const char* criterioToString(CriterioOrdenacao criterio) {
    switch (criterio) {
        case CRITERIO_NOME: return "Nome";
        case CRITERIO_TIPO: return "Tipo";
        case CRITERIO_PRIORIDADE: return "Prioridade";
        default: return "INVÁLIDO";
    }
}

void exibirDadosItem(const Item *item, int nro) {
    printf("%-4d| %-28s | %-18s | %-10d | %-12d \n",
        nro,
        item->nome,
        tipoItemToString(item->tipo),
        item->quantidade,
        item->prioridade
    );
}

void pressioneEnter() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
}

void limparTela() {
    printf("\n\n\n\n\n\n\n");
}

void exibirDetalhesItem(const Item *item) {
    if (item == NULL) {
        printf("[ERRO] Não é possível exibir detalhes: Item inválido (NULL).\n");
        return;
    }
    printf("Nome:       %s\n", item->nome);
    printf("Tipo:       %s\n", tipoItemToString(item->tipo));
    printf("Quantidade: %d\n", item->quantidade);
}

void exibirMenuOperacoes(const char* nome_estrutura) {
    int qdeItens = (estruturaAtual == 1) ? numItensVetor : numItensLista;
    printf("\n#### PLANO DE FUGA - CODIGO DA ILHA ####\n");
    printf("Quantidade de itens: %d/%d\n", qdeItens, CAPACIDADE_MAXIMA);
    printf("\n---------- MENU DE ITENS ----------\n");
    printf("1. Adicionar Componente\n");
    printf("2. Remover Componente\n");
    printf("3. Listar Componentes (Inventário)\n");

    // As opções de 4 a 6 mudam dependendo da estrutura
    if (strcmp(nome_estrutura, "VETOR") == 0) {
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        // printf("5. Buscar Item\n"); desativado para o nível mestre
        printf("5. Buscar Binária por Componente-Chave (por nome)\n");
    } else {
        printf("4. Buscar Item\n");
    }

    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("------------------------------------------\n");
    printf("Escolha uma opção: ");
}

void menuDeOrdenacao() {
    int opcao_ordenacao;
    do {
        printf("\n#### Estratégia de Organização ####\n");
        printf("------------------------------------------\n");
        printf("Como deseja ordenar os componentes?\n");
        printf("1. Por NOME (Ordem Alfabética)\n");
        printf("2. Por TIPO\n");
        printf("3. Por PRIORIDADE de Montagem\n");
        printf("0. Cancelar e Voltar\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao_ordenacao) != 1) {
            opcao_ordenacao = -1;
        }
        while (getchar() != '\n');
        if (opcao_ordenacao >= 1 && opcao_ordenacao <= 3) {
            CriterioOrdenacao criterio = (CriterioOrdenacao)(opcao_ordenacao - 1);
            ordenarItens(criterio);
            break;
        } else {
            switch (opcao_ordenacao) {
                case 0:
                    printf("\nOrdenação cancelada.\n");
                    break;
                default:
                    printf("\n[ERRO] Opção inválida. Tente novamente.\n");
                    break;
            }
        }
    } while (opcao_ordenacao > 0 && opcao_ordenacao < 3);
}

// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (estruturaAtual == 1) {
        _inserirVetor();
    } else if (estruturaAtual == 2) {
        _inserirLista();
    } else {
        printf("[ERRO] Estrutura não selecionada. Escolha a opção 1 ou 2 no Menu Principal.\n");
    }
    limparTela();
}

// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    if (estruturaAtual == 1) {
        _removerVetor();
    } else if (estruturaAtual == 2) {
        _removerLista();
    } else {
        printf("[ERRO] Estrutura não selecionada. Escolha a opção 1 ou 2 no Menu Principal.\n");
    }
    limparTela();
}

// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void mostrarComponentes() {
    if (estruturaAtual == 1) {
        _listarVetor();
    } else if (estruturaAtual == 2) {
        _listarLista();
    } else {
        printf("[ERRO] Estrutura não selecionada. Escolha a opção 1 ou 2 no Menu Principal.\n");
    }
}

void ordenarItens(CriterioOrdenacao criterio) {
    if (estruturaAtual == 1) {
        _ordenarVetor(criterio);
    } else if (estruturaAtual == 2) {
        printf("[ALERTA] Ordenação por nome não é necessária ou eficiente em Listas Encadeadas.\n");
    } else {
        printf("[ERRO] Estrutura não selecionada. Escolha a opção 1 ou 2 no Menu Principal.\n");
    }
}

// Verifica se a lista está em ordem
bool verificarOrdenacao() {
    if (numItensVetor <= 1) {
        return true;
    }
    // Percorre os itens e verifica a ordem
    for (int i = 1; i < numItensVetor; i++) {
        // Verifica se o registro anterior é maior que o atual
        if (strcmp(mochilaVetor[i - 1].nome, mochilaVetor[i].nome) > 0) {
            return false;
        }
    }
    return true;
}

Item* buscarItem(const char *nomeBusca, bool buscaBinaria) {
    if (estruturaAtual == 1) {
        int indice;
        if (buscaBinaria) {
            indice = buscaBinariaPorNome(mochilaVetor, nomeBusca);
        } else {
            indice = _buscarSequencialVetor(nomeBusca);
        }
        if (indice != -1) {
            return &(mochilaVetor[indice]);
        }
        return NULL;
    } else if (estruturaAtual == 2) {
        if (buscaBinaria) {
            printf("[ERRO] Não é possível realizar a busca.\n");
        }
        No* noEncontrado = _buscarSequencialLista(nomeBusca);
        if (noEncontrado != NULL) {
            return &(noEncontrado->dados);
        }
        return NULL;
    }
    printf("[ERRO] Estrutura não selecionada.\n");
    return NULL;
}

// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
int buscaBinariaPorNome(Item mochila[], const char *nomeBusca) {
    contComparacoes = 0;
    clock_t inicio_tempo = clock();
    int inicio = 0;
    int fim = numItensVetor - 1;
    int meio;
    int resultadoComparacao;
    // Verifica quantidade de itens
    if (numItensVetor == 0) {
        clock_t fim_tempo = clock();
        medirTempo(inicio_tempo, fim_tempo, contComparacoes);
        return -1;
    }
    // Loop para busca Binária
    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        contComparacoes++;
        resultadoComparacao = strcmp(mochila[meio].nome, nomeBusca);
        // Item encontrado
        if (resultadoComparacao == 0) {
            clock_t fim_tempo = clock();
            medirTempo(inicio_tempo, fim_tempo, contComparacoes);
            return meio;
        }
        // Nome buscado é "menor", busca na primeira metade
        // Nome buscado é "maior", busca na segunda metade
        if (resultadoComparacao > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    // Item não encontrado
    clock_t fim_tempo = clock();
    medirTempo(inicio_tempo, fim_tempo, contComparacoes);
    return -1;
}

void medirTempo(clock_t inicio, clock_t fim, long long comparacoes) {
    // Calcula o tempo em segundos
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("---------- Resultado ----------\n");
    printf("Comparações realizadas: %lld\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
    printf("------------------------------------------\n");
}

void bubbleSortNome(Item mochila[], int tamanho) {
    int i, j;
    Item temp;
    contComparacoes = 0;
    clock_t inicio = clock();
    // Loop Bubble Sort
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {
            contComparacoes++;
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
    clock_t fim = clock();
    medirTempo(inicio, fim, contComparacoes);
}

void insertionSortTipo(Item mochila[], int tamanho) {
    int i, j;
    Item temp;
    contComparacoes = 0;
    clock_t inicio = clock();
    // Loop Insertion Sort
    for (i = 0; i < tamanho - 1; i++) {
        temp = mochila[i];
        j = i - 1;
        while (j >= 0) {
            contComparacoes++;
            if (strcmp(tipoItemToString(mochila[j].tipo), tipoItemToString(temp.tipo)) > 0) {
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break;
            }
        }
        mochila[j + 1] = temp;
    }
    clock_t fim = clock();
    medirTempo(inicio, fim, contComparacoes);
}

void selectionSortPrioridade(Item mochila[], int tamanho) {
    int i, j, indiceMaximo;
    Item temp;
    contComparacoes = 0;
    clock_t inicio = clock();
    // Loop Selection Sort
    for (i = 0; i < tamanho - 1; i++) {
        indiceMaximo = i;
        for (j = i + 1; j < tamanho; j++) {
            contComparacoes++;
            if (mochila[j].prioridade > mochila[indiceMaximo].prioridade) {
                indiceMaximo = j;
            }
        }
        if (indiceMaximo != i) {
            temp = mochila[i];
            mochila[i] = mochila[indiceMaximo];
            mochila[indiceMaximo] = temp;
        }
    }

    clock_t fim = clock();
    medirTempo(inicio, fim, contComparacoes);
}

// FUNÇÕES DE VETOR
// -----------------------------------------------------------------------------
void _inserirVetor() {
    if (numItensVetor >= CAPACIDADE_MAXIMA) {
        printf("\n[ALERTA] A mochila está cheia! Não é possível carregar mais itens.\n");
        return;
    }
    printf("\n#### NOVO ITEM ####\n");
    // preenche as informações do Item
    Item novoItem = _preencherItem();

    // Verifica se teve algum erro no preenchimento das perguntas
    if (novoItem.quantidade <= 0) {
        printf("[ERRO] Item não cadastrado!\n");
        return;
    }
    // Coloca o novo item na próxima posição livre do vetor
    mochilaVetor[numItensVetor] = novoItem;
    // aumenta a quantidade de produtos na lista
    numItensVetor++;

    printf("\n[SUCESSO] Item '%s' adicionado à mochila (Total: %d/%d)!\n",
       novoItem.nome
       , numItensVetor
       , CAPACIDADE_MAXIMA
    );
    // lista os itens cadastrados
    _listarVetor();
}

void _removerVetor() {
    char nomeParaRemover[30];
    if (numItensVetor == 0) {
        printf("\n[ALERTA] A mochila está vazia. Nada para remover.\n");
        return;
    }
    // Exibe a listagem com os itens a serem removidos
    _listarVetor();
    printf("\n#### REMOVER ITEM ####\n");
    printf("Digite o Nome do Item para remover (sem espaços): ");
    if (scanf("%29s", nomeParaRemover) != 1) {
        printf("[ERRO] Falha na leitura do nome.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    int indiceRemover = _localizarVetor(nomeParaRemover);

    // Verifica se o item existe
    if (indiceRemover == -1) {
        printf("\n[ALERTA] Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    } else {
        // Exclui e reorganiza os nós
        for (int i = indiceRemover; i < numItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        // Reduz um item no contador
        numItensVetor--;

        printf("\n[SUCESSO] Item '%s' removido da mochila. (Total: %d/%d)\n",
           nomeParaRemover
           , numItensVetor
           , CAPACIDADE_MAXIMA
        );
    }
}

void _listarVetor() {
    // Exibe o total de itens no cabeçalho
    printf("\n#### ITENS NA MOCHILA (%d/%d) ####\n", numItensVetor, CAPACIDADE_MAXIMA);
    if (numItensVetor == 0) {
        printf("A mochila está vazia. Colete alguns itens!\n");
        return;
    }

    printf("NRO.| %-28s | %-18s | %-10s | %s \n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------------------------\n");

    // Percorre a lista para exibição
    for (int i = 0; i < numItensVetor; i++) {
        exibirDadosItem(&(mochilaVetor[i]), i + 1);
    }
    printf("---------------------------------------------------------------------------------\n");
}

void _ordenarVetor(CriterioOrdenacao criterio) {
    // verifica quantidade de itens para ordenação
    if (numItensVetor <= 1) {
        printf("\n[ALERTA] A mochila tem 0 ou 1 item. Não é possível ordenar.\n");
        return;
    }

    int i, j, indiceMinimo;
    Item temp;

    const char *nomeCriterio = criterioToString(criterio);
    printf("\n[ALERTA] Ordenando por '%s'...\n", nomeCriterio);
    switch (criterio) {
        case CRITERIO_NOME:
            bubbleSortNome(mochilaVetor, numItensVetor);
            break;
        case CRITERIO_TIPO:
            insertionSortTipo(mochilaVetor, numItensVetor);
            break;
        case CRITERIO_PRIORIDADE:
            selectionSortPrioridade(mochilaVetor, numItensVetor);
            break;
        default:
            printf("[ERRO] Critério de ordenação inválido.\n");
            break;
    }

    // retorna mensagem de sucesso
    printf("[SUCESSO] Itens ordenados por '%s'(Total: %d/%d).\n"
        , nomeCriterio
        , numItensVetor
        , CAPACIDADE_MAXIMA
    );
    // lista os itens cadastrados
    _listarVetor();
}

int _localizarVetor(const char* nomeBusca) {
    contComparacoes = 0;
    clock_t inicio = clock();
    for (int i = 0; i < numItensVetor; i++) {
        contComparacoes++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            clock_t fim = clock();
            medirTempo(inicio, fim, contComparacoes);
            return i;
        }
    }
    clock_t fim = clock();
    medirTempo(inicio, fim, contComparacoes);
    return -1;
}

int _buscarSequencialVetor(const char *nomeBusca) {
    int indiceEncontrado = _localizarVetor(nomeBusca);
    if (indiceEncontrado != -1) {
        // Item existe
        return indiceEncontrado;
    } else {
        // Item não existe
        return -1;
    }
}

Item _preencherItem() {
    int tipo_int;
    Item novoItem;
    // Inicializa a quantidade como 0 para indicar falha em caso de erro
    novoItem.quantidade = 0;

    // Leitura do Nome
    printf("Nome do Item (sem espaços, max 29 chars): ");
    if (scanf("%29s", novoItem.nome) != 1) {
        printf("[ERRO] Falha na leitura do nome, máximo de 29 caracteres.\n");
        return novoItem;
    }
    while (getchar() != '\n');

    // Leitura do Tipo (Enum)
    printf("\n[SELECIONE UM TIPO ABAIXO]\n");
    printf("1: Estrutural | 2: Eletronico | 3: Energia | 4: Suporte | 5: Controle\n");
    printf("Número do Tipo do Item: ");
    // Verifica se foi digitado um número inteiro
    if (scanf("%d", &tipo_int) != 1) {
        printf("[ERRO] Entrada inválida. Digite um número de 1-5!\n");
        while (getchar() != '\n');
        return novoItem;
    }
    //Converte o inteiro lido para o TipoItem (enum)
    TipoItem novo_tipo = (TipoItem)tipo_int;

    //Verifica se a opção existe
    if (novo_tipo <= TIPO_INVALIDO || novo_tipo >= TOTAL_TIPOS) {
        printf("[ERRO] Tipo inválido, digite um número de 1-5!\n");
        return novoItem;
    }
    // Armazena os dados do Tipo na struct
    novoItem.tipo = (TipoItem)tipo_int;
    while (getchar() != '\n');

    // Leitura da Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("[ERRO] Quantidade inválida.\n");
        while (getchar() != '\n');
        novoItem.quantidade = 0;
        return novoItem;
    }
    while (getchar() != '\n');

    // Leitura da Prioridade
    printf("Prioridade de Montagem (1-5): ");
    if (scanf("%d", &novoItem.prioridade) != 1 || novoItem.prioridade < 1 || novoItem.prioridade > 5) {
        printf("[ERRO] Prioridade inválida. Digite um número de 1 a 5.\n");
        while (getchar() != '\n');
        novoItem.quantidade = 0;
        return novoItem;
    }
    while (getchar() != '\n');

    return novoItem;
}

// FUNÇÕES DE LISTA ENCADEADA
// -----------------------------------------------------------------------------
void _inserirLista() {
    if (numItensLista >= CAPACIDADE_MAXIMA) {
        printf("\n[ALERTA] A mochila está cheia! Não é possível carregar mais itens.\n");
        return;
    }
    printf("\n#### NOVO ITEM ####\n");
    // preenche as informações do Item
    Item novoItem = _preencherItem();
    // Verifica se teve algum erro no preenchimento das perguntas
    if (novoItem.quantidade <= 0) {
        printf("[ERRO] Item não cadastrado!\n");
        return;
    }
    // reserva espaço na memória
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n[ERRO FATAL] Falha ao alocar memória para novo item! Memória insuficiente.\n");
        return;
    }
    // preenche as informações
    novoNo->dados = novoItem;
    novoNo->proximo = cabecaLista;
    cabecaLista = novoNo;

    // aumenta a quantidade de produtos na lista
    numItensLista++;
    // retorna mensagem de sucesso
    printf("\n[SUCESSO] Item '%s' adicionado à mochila (Total: %d/%d)!\n",
       novoItem.nome
       , numItensLista
       , CAPACIDADE_MAXIMA
    );
    // lista os itens cadastrados
    _listarLista();
}

void _removerLista() {
    char nomeParaRemover[30];
    if (cabecaLista == NULL) {
        printf("\n[ALERTA] A mochila está vazia. Nada para remover.\n");
        return;
    }
    // Exibe a listagem com os itens a serem removidos
    _listarLista();
    printf("\n#### REMOVER ITEM ####\n");
    printf("Digite o Nome do Item para remover (sem espaços): ");
    if (scanf("%29s", nomeParaRemover) != 1) {
        printf("[ERRO] Falha na leitura do nome.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    No* atual = NULL;
    No* anterior = _localizarLista(nomeParaRemover, &atual);

    // Verifica se o item existe
    if (atual == NULL) {
        printf("\n[ALERTA] Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    } else {
        // Exclui e reorganiza os nós
        if (anterior == NULL) {
            cabecaLista = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        // Libera a memória alocada para o Nó removido
        free(atual);
        // Reduz um item no contador
        numItensLista--;

        printf("\n[SUCESSO] Item '%s' removido da mochila. (Total: %d/%d)\n",
           nomeParaRemover
           , numItensLista
           , CAPACIDADE_MAXIMA
        );
    }
}

void _listarLista() {
    // Exibe o total de itens no cabeçalho
    printf("\n#### ITENS NA MOCHILA (%d/%d) ####\n", numItensLista, CAPACIDADE_MAXIMA);
    if (numItensLista == 0) {
        printf("A mochila está vazia. Colete alguns itens!\n");
        return;
    }

    printf("NRO.| %-28s | %-18s | %-10s | %s \n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------------------------\n");

    No* atual = cabecaLista;
    int contador = 1;

    // Percorre a lista para exibição
    while (atual != NULL) {
        exibirDadosItem(&(atual->dados), contador);
        atual = atual->proximo;
        contador++;
    }
    printf("---------------------------------------------------------------------------------\n");
}

No* _localizarLista(const char* nomeBusca, No** noEncontrado) {
    contComparacoes = 0;
    clock_t inicio = clock();
    No* atual = cabecaLista;
    No* anterior = NULL;
    *noEncontrado = NULL;
    while (atual != NULL) {
        contComparacoes++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            *noEncontrado = atual;
            clock_t fim = clock();
            medirTempo(inicio, fim, contComparacoes);
            return anterior;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    clock_t fim = clock();
    medirTempo(inicio, fim, contComparacoes);
    return NULL;
}

No* _buscarSequencialLista(const char *nomeBusca) {
    No* encontrado = NULL;
    _localizarLista(nomeBusca, &encontrado);
    return encontrado;
}