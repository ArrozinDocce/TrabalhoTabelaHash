#ifndef HASH_H
#define HASH_H

#include <stdint.h> // Tipos de dados inteiros com tamanhos definidos

// Constantes que definem o funcionamento do hashing
#define NUM_BYTES 4        // Número de bytes por chave (32 bits = 4 bytes)
#define TAB_SIZE 256       // Tamanho das tabelas de tabulação (0 a 255)
#define TAMANHO_TABELA 101 // Tamanho da tabela hash (idealmente um número primo)

// Estrutura para representar um nó da lista encadeada
typedef struct No {
    uint32_t chave;         // Chave da entrada (ex: ID)
    int valor;              // Valor associado à chave
    struct No* proximo;     // Ponteiro para o próximo nó na lista
} No;

// Tabela de tabulação usada no cálculo de hash
extern uint32_t T[NUM_BYTES][TAB_SIZE];

// Vetor da tabela hash contendo ponteiros para os nós
extern No* tabela_hash[TAMANHO_TABELA];

// Funções públicas
void inicializar_tabela();            // Inicializa a tabela hash e a tabulação
uint32_t tabulation_hash(uint32_t);   // Retorna o índice gerado pela função de hash
void inserir(uint32_t, int);          // Insere chave e valor na tabela
void remover(uint32_t);               // Remove um par chave-valor
No* buscar(uint32_t);                 // Busca uma chave e retorna o nó correspondente
void exibir_tabela();                 // Mostra o conteúdo da tabela no terminal
void testar_tabela();                // Roda um teste rápido (inserir, buscar, remover)
void MenuHash();                      // Menu interativo via terminal

#endif
