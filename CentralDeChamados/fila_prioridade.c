
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila_prioridade.h"
//Aqui fica a parte principal do código >A lógica<
// Criação da fila abaixo:

FilaPrioridade* criarFila() {

    FilaPrioridade* fila = malloc(sizeof(FilaPrioridade));

    if (fila == NULL) {
        return NULL;
    }

    fila->inicio = NULL;
    fila->total_chamados = 0;
    fila->proximo_id = 1;

    return fila;
}

//  Nome das prioridades:

const char* obterNomePrioridade(NivelPrioridade p) {

    switch (p) {

        case NORMAL:
            return "Normal";

        case ALTA:
            return "Alta";

        case CRITICA:
            return "Critica";

        default:
            return "Desconhecida";
    }
}


//  Inserção de maneira organizada:

void inserirChamado(
    FilaPrioridade* fila,
    const char* descricao,
    NivelPrioridade prioridade
) {

    if (fila == NULL || descricao == NULL) {
        printf("\nErro: fila ou descricao invalida!\n");
        return;
    }

    if (prioridade < NORMAL || prioridade > CRITICA) {
        printf("\nErro: prioridade invalida!\n");
        return;
    }

    // Alocacao dinamica do novo chamado:
    Chamado* novo = malloc(sizeof(Chamado));

    if (novo == NULL) {
        printf("\nErro: falha ao alocar memoria!\n");
        return;
    }

    novo->id = fila->proximo_id++;

    strncpy(
        novo->descricao,
        descricao,
        sizeof(novo->descricao) - 1
    );

    novo->descricao[sizeof(novo->descricao) - 1] = '\0';

    novo->prioridade = prioridade;
    novo->proximo = NULL;

    // Procura a posicao correta na fila:
    Chamado** atual = &fila->inicio;

    while (
        *atual != NULL &&
        (*atual)->prioridade >= prioridade
    ) {
        atual = &(*atual)->proximo;
    }

    // Insere o novo chamado:
    novo->proximo = *atual;
    *atual = novo;

    fila->total_chamados++;

    printf("\nChamado cadastrado com sucesso!\n");
    printf("ID: %d\n", novo->id);

    printf(
        "Prioridade: %s\n",
        obterNomePrioridade(novo->prioridade)
    );
}

// Atendimento e/ou remoção:

void atenderChamado(FilaPrioridade* fila) {

    if (fila == NULL || fila->inicio == NULL) {

        printf("\nNao existem chamados para atender!\n");
        return;
    }

    // Guarda o primeiro chamado:
    Chamado* removido = fila->inicio;

    // Atualiza o inicio da fila:
    fila->inicio = removido->proximo;

    printf("\n========== CHAMADO ATENDIDO ==========\n");

    printf("ID: %d\n", removido->id);

    printf("Descricao: %s\n", removido->descricao);

    printf(
        "Prioridade: %s\n",
        obterNomePrioridade(removido->prioridade)
    );

    printf("======================================\n");

    // Libera a memoria do chamado atendido:
    free(removido);

    fila->total_chamados--;

    printf("\nChamado removido da fila com sucesso!\n");
}

// Exibição da fila:

void exibirFila(const FilaPrioridade* fila) {

    if (fila == NULL || fila->inicio == NULL) {

        printf("\nA fila de chamados esta vazia!\n");
        return;
    }

    Chamado* atual = fila->inicio;

    printf("\n========== FILA DE PRIORIDADE ==========\n");

    printf("Total de chamados: %d\n\n",
           fila->total_chamados);

    while (atual != NULL) {

        printf("ID: %d\n", atual->id);

        printf("Descricao: %s\n", atual->descricao);

        printf(
            "Prioridade: %s\n",
            obterNomePrioridade(atual->prioridade)
        );

        printf("---------------------------------------\n");

        atual = atual->proximo;
    }

    printf("========================================\n");
}

// Liberação da memória:

void liberarFila(FilaPrioridade* fila) {

    if (fila == NULL) {
        return;
    }

    Chamado* atual = fila->inicio;

    while (atual != NULL) {

        Chamado* proximo = atual->proximo;

        free(atual);

        atual = proximo;
    }

    free(fila);

    printf("\nMemoria liberada com sucesso!\n");
}
