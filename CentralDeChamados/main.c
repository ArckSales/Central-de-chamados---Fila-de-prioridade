
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "fila_prioridade.h"

// Lendo os números:

int lerInteiro(const char* mensagem, int* resultado) {

    char entrada[100];
    char* fim;
    long valor;

    while (1) {

        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            return 0;
        }

        errno = 0;
        valor = strtol(entrada, &fim, 10);

        if (fim == entrada || errno == ERANGE || valor < INT_MIN || valor > INT_MAX) {
            printf("Entrada invalida! Digite um numero.\n");
            continue;
        }

        while (*fim == ' ' || *fim == '\t') {
            fim++;
        }

        if (*fim != '\n' && *fim != '\0') {
            printf("Entrada invalida! Digite apenas numeros.\n");
            continue;
        }

        *resultado = (int)valor;
        return 1;
    }
}
 
// "Menu" principal:

int main() {

    FilaPrioridade* fila = criarFila();

    if (fila == NULL) {

        printf(
            "Erro critico: falha ao alocar memoria para a fila!\n"
        );

        return 1;
    }

    int opcao;
    char descricao[100];
    int prioridade;

    do {

        printf("\n");
        printf("========================================\n");
        printf("       CENTRAL DE CHAMADOS\n");
        printf("          FILA DE PRIORIDADE\n");
        printf("========================================\n");

        printf("1 - Cadastrar chamado\n");
        printf("2 - Atender chamado\n");
        printf("3 - Exibir fila de chamados\n");
        printf("0 - Encerrar programa\n");

        printf("========================================\n");

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            printf("\nFim da entrada. Encerrando o programa...\n");
            break;
        }

        switch (opcao) {

            // CADASTRAR CHAMADO
            case 1:

                printf("\n========== NOVO CHAMADO ==========\n");

                printf("Digite a descricao do chamado: ");

                if (fgets(descricao, sizeof(descricao), stdin) == NULL) {
                    printf("\nFim da entrada. Encerrando o programa...\n");
                    break;
                }

                size_t tamanho = strcspn(descricao, "\n");
                if (descricao[tamanho] == '\n') {
                    descricao[tamanho] = '\0';
                } else {
                    int caractere;
                    while ((caractere = getchar()) != '\n' && caractere != EOF) {
                        // Descarta o restante da descricao longa.
                    }
                    printf("\nDescricao muito longa. Use ate 99 caracteres.\n");
                    break;
                }

                if (descricao[0] == '\0') {
                    printf("\nA descricao nao pode ficar vazia!\n");
                    break;
                }

                printf("\nNiveis de prioridade:\n");
                printf("1 - Normal\n");
                printf("2 - Alta\n");
                printf("3 - Critica\n");

                if (!lerInteiro("Escolha a prioridade: ", &prioridade)) {
                    printf("\nFim da entrada. Encerrando o programa...\n");
                    opcao = 0;
                    break;
                }

                if (prioridade < NORMAL || prioridade > CRITICA) {

                    printf("\nPrioridade invalida! Tente novamente.\n");

                    break;
                }

                inserirChamado(
                    fila,
                    descricao,
                    (NivelPrioridade)prioridade
                );

                break;


            // ATENDER CHAMADO
            case 2:

                atenderChamado(fila);

                break;


            // EXIBIR FILA
            case 3:

                exibirFila(fila);

                break;


            // ENCERRAR PROGRAMA
            case 0:

                printf("\nEncerrando Central de Chamados...\n");

                break;


            // OPCAO INVALIDA
            default:

                printf("\nOpcao invalida! Tente novamente.\n");

                break;
        }

    } while (opcao != 0);

    // Libera a memoria antes de encerrar:
    liberarFila(fila);

    return 0;
}
