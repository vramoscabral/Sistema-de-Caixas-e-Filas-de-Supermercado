#include "cliente.h"
#include <string.h>
#include <ctype.h>

void limparBufferEntrada() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void cadnome(Cliente *c) {
    while (1) {
        printf ("Digite o nome do cliente: ");
        fgets(c->nome,102,stdin);

        if (c->nome[strlen(c->nome) - 1] != '\n') {
            limparBufferEntrada();
        } else {
            c->nome[strlen(c->nome)-1]='\0';
        }

        if (strlen(c->nome) == 0)
            printf("Erro: O nome nao pode estar vazio. Tente novamente.\n");
        else
            break;
    }
}

void cadcpf(Cliente *c) {
    si verify=0;
    
    while (1) {
        printf ("Digite o cpf do cliente: ");
        fgets(c->cpf,13,stdin);
        
        if (c->cpf[strlen(c->cpf) - 1] != '\n') {
            limparBufferEntrada();
        } else {
            c->cpf[strlen(c->cpf)-1]='\0';
        }

        for (int i = 0; i < 11; i++) {
            if (!isdigit(c->cpf[i])) {
                verify=1;
            }
        }

        if (strlen(c->cpf) != 11) {
            printf("Erro: O cpf deve ter 11 digitos. Tente novamente.\n");
            verify = 0;
        }
        else if (verify == 1) {
            printf("Erro: O cpf so pode ter numero. Tente novamente.\n");
            verify = 0;
        }
        else
            break;
    }
}

void cadprior(Cliente *c) {
    int resultado;
    do {
        printf("Prioridades: 1-Alta / 2-Media / 3-Baixa\n");
        printf("Digite a prioridade do cliente: ");
        resultado = scanf("%hd", &c->prioridade);

        if (resultado != 1) {
            printf("Erro: Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
        } else if (c->prioridade < 1 || c->prioridade > 3) {
            printf("Erro: Escolha entre 1, 2 ou 3.\n");
            resultado = 0;
        }
    } while (resultado != 1);
}

void caditens(Cliente *c) {
    int resultado;
    do {
        printf("Digite a quantidade de itens: ");
        resultado = scanf("%hd", &c->itens);

        if (resultado != 1) {
            printf("Erro: Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
        } else if (c->itens < 1 || c->itens > 300) {
            printf("Erro: Escolha de 1 a 300 itens.\n");
            resultado = 0;
        }
    } while (resultado != 1);
}