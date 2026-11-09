
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila_prioridade.h"

// Lendo os números:

int lerInteiro(const char* mensagem) {

    char entrada[100];
    char* fim;
    long valor;

    while (1) {

        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            return -1;
        }

        valor = strtol(entrada, &fim, 10);

        if (fim == entrada) {
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

        return (int)valor;
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

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {

            // CADASTRAR CHAMADO
            case 1:

                printf("\n========== NOVO CHAMADO ==========\n");

                printf("Digite a descricao do chamado: ");

                if (fgets(descricao, sizeof(descricao), stdin) == NULL) {
                    printf("\nErro ao ler descricao!\n");
                    break;
                }

                descricao[strcspn(descricao, "\n")] = '\0';

                if (descricao[0] == '\0') {
                    printf("\nA descricao nao pode ficar vazia!\n");
                    break;
                }

                printf("\nNiveis de prioridade:\n");
                printf("1 - Normal\n");
                printf("2 - Alta\n");
                printf("3 - Critica\n");

                prioridade = lerInteiro("Escolha a prioridade: ");

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
