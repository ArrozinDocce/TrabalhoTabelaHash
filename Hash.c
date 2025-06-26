#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Hash.h"

// Matriz usada para gerar valores de hash por tabulação
uint32_t T[NUM_BYTES][TAB_SIZE];

// Vetor da tabela hash, contendo ponteiros para listas ligadas
No* tabela_hash[TAMANHO_TABELA] = { NULL };

// Preenche a matriz T com números pseudoaleatórios e zera a tabela
void inicializar_tabela() 
{
    srand((unsigned) time(NULL));  // Gera sementes aleatórias com base no tempo

    // Preenche a matriz T com números pseudoaleatórios de 32 bits
    for (int i = 0; i < NUM_BYTES; i++) 
    {
        for (int j = 0; j < TAB_SIZE; j++) 
        {
            T[i][j] = ((uint32_t) rand() << 16) ^ rand(); // Combina dois rand()
        }
    }

    // Zera todos os ponteiros da tabela hash
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_hash[i] = NULL;
    }
}

// Função de tabulação: mistura os bytes da chave usando XOR com T
uint32_t tabulation_hash(uint32_t chave) {
    uint32_t h = 0;
    for (int i = 0; i < NUM_BYTES; i++) {
        uint8_t byte = (chave >> (i * 8)) & 0xFF;
        h ^= T[i][byte];
    }
    return h;
}

// Insere uma nova chave/valor ou atualiza se a chave já existir
void inserir(uint32_t chave, int valor) {
    uint32_t indice = tabulation_hash(chave) % TAMANHO_TABELA;
    No* atual = tabela_hash[indice];

    while (atual != NULL) {
        if (atual->chave == chave) {
            atual->valor = valor; // Atualiza o valor existente
            return;
        }
        atual = atual->proximo;
    }

    // Cria um novo nó e insere na frente da lista
    No* novo = malloc(sizeof(No));
    if (!novo) return;
    novo->chave = chave;
    novo->valor = valor;
    novo->proximo = tabela_hash[indice];
    tabela_hash[indice] = novo;
}

// Remove um elemento baseado na chave, se encontrado
void remover(uint32_t chave) {
    uint32_t indice = tabulation_hash(chave) % TAMANHO_TABELA;
    No* atual = tabela_hash[indice];
    No* anterior = NULL;

    while (atual != NULL) {
        if (atual->chave == chave) {
            if (anterior == NULL)
                tabela_hash[indice] = atual->proximo; // Remove o primeiro nó
            else
                anterior->proximo = atual->proximo;   // Remove do meio/fim

            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

// Procura por uma chave e retorna o nó correspondente (ou NULL)
No* buscar(uint32_t chave) {
    uint32_t indice = tabulation_hash(chave) % TAMANHO_TABELA;
    No* atual = tabela_hash[indice];
    while (atual != NULL) {
        if (atual->chave == chave)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// Imprime todo o conteúdo da tabela hash (cada índice e sua lista)
void exibir_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("[%d]: ", i);
        No* atual = tabela_hash[i];
        while (atual != NULL) {
            printf("(%u => %d) -> ", atual->chave, atual->valor);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

// Função de teste com inserção, busca e remoção
void testar_tabela() {
    printf("🔍 Inserindo dados de teste...\n");
    inserir(100, 42);
    inserir(200, 84);
    inserir(300, 126);
    exibir_tabela();

    No* resultado = buscar(200);
    if (resultado)
        printf("✅ Chave 200 encontrada com valor: %d\n", resultado->valor);
    else
        printf("❌ Chave 200 não encontrada.\n");

    printf("🚮 Removendo a chave 100...\n");
    remover(100);
    exibir_tabela();
}

// Menu de operações para interação via terminal
void MenuHash() {
    int opcao, chave, valor;
    do {
        printf("\n📘 Menu da Tabela Hash:\n");
        printf("1. Inserir\n2. Remover\n3. Buscar\n4. Exibir\n0. Sair\n> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Chave: "); scanf("%d", &chave);
                printf("Valor: "); scanf("%d", &valor);
                inserir(chave, valor);
                break;
            case 2:
                printf("Chave: "); scanf("%d", &chave);
                remover(chave);
                break;
            case 3:
                printf("Chave: "); scanf("%d", &chave);
                No* n = buscar(chave);
                if (n) printf("Valor encontrado: %d\n", n->valor);
                else printf("Chave não encontrada.\n");
                break;
            case 4:
                exibir_tabela();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}
