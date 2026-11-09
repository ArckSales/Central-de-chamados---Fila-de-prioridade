
#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H
// Estou colocando tudo explicado pra podermos ter uma organização melhor!!
// Niveis de prioridade dos chamados:
typedef enum {
    NORMAL = 1,
    ALTA = 2,
    CRITICA = 3
} NivelPrioridade;


// Estrutura de cada chamado:
typedef struct Chamado {
    int id;
    char descricao[100];
    NivelPrioridade prioridade;
    struct Chamado* proximo;
} Chamado;


// Estrutura principal da fila:
typedef struct {
    Chamado* inicio;
    int total_chamados;
    int proximo_id;
} FilaPrioridade;


// Prototipos das funcoes:
FilaPrioridade* criarFila();

void inserirChamado(
    FilaPrioridade* fila,
    const char* descricao,
    NivelPrioridade prioridade
);

void atenderChamado(FilaPrioridade* fila);

void exibirFila(const FilaPrioridade* fila);

void liberarFila(FilaPrioridade* fila);

const char* obterNomePrioridade(NivelPrioridade p);

#endif
