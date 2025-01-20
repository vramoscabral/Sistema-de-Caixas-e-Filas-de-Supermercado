#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fila.h"
#include "cliente.h"

int main() {
    Caixa caixas[MAX_CAIXAS];
    for (int i = 0; i < MAX_CAIXAS; i++) {
        inicializarCaixa(&caixas[i], i+1);
    }
    printf("\n");
    si opcao, caixa, resultado=0, caixasAtivos = MAX_CAIXAS;
    int destino;
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));

    while (1) {
        do {
            printf("\nMENU OPCOES\n");
            printf("1. Cadastrar Cliente \n2. Atender Cliente\n3. Fechar Caixa\n4. Abrir Caixa\n5. Imprimir Lista de Clientes\n0. Sair\n");
            printf("\nEscolha uma opcao: ");
            resultado = scanf("%hd", &opcao);

            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); 
            }
        } while (resultado != 1);

        switch(opcao) {
            case 1:
                limparBufferEntrada();
                printf("\n");
                cadnome(novo);
                do {
                    cadcpf(novo);
                    resultado = 2;
                    if (existeCpf(caixas, MAX_CAIXAS, novo->cpf)) {
                        printf ("O cpf %s ja foi cadastrado. Insira outro valor.\n",novo->cpf);
                        resultado = 1;
                    }
                } while (resultado !=2);
                cadprior(novo);
                caditens(novo);
                caixa = escolherCaixa(caixas, 1);
                cadastrar(&caixas[caixa].fila, novo);
                printf("\nCliente cadastrado\nNome: %s // CPF: %s // ",novo->nome,novo->cpf);
                printf("Prioridade: %hd // Itens: %hd // Caixa: %hd\n",novo->prioridade,novo->itens,caixa+1);
                break;
            case 2:
                caixa = escolherCaixa(caixas, 2);
                if (filaVazia(&caixas[caixa].fila))
                    printf("\nA fila do caixa %hd esta vazia!\n", caixa+1);
                else {
                    novo = remover(&caixas[caixa].fila);
                    printf("\nCliente atendido\nNome: %s // CPF: %s, ",novo->nome,novo->cpf);
                    printf("Prioridade: %hd, Itens: %hd, Caixa: %hd\n",novo->prioridade,novo->itens,caixa+1);
                }
                break;
            case 3:
                if (caixasAtivos == 1)
                    printf("Deve haver ao menos um caixa ativo.\n");
                else {
                    caixa = escolherCaixa(caixas, 3);
                    caixasAtivos--;
                    caixas[caixa].estado = false;
                    if (filaVazia(&caixas[caixa].fila))
                        printf("\nO caixa %hd foi fechado, nao havia clientes.\n",caixa+1);
                    else {
                        destino = -1;
                        for (int i=0; i<MAX_CAIXAS; i++) {
                            if (caixas[i].estado) {
                                if (destino == -1 || quantclientes(&caixas[i].fila) < quantclientes(&caixas[destino].fila)) {
                                    destino = i;
                                }
                            }
                        }
                        while (!filaVazia(&caixas[caixa].fila)) {
                            cadastrar(&caixas[destino].fila, remover(&caixas[caixa].fila));
                        }
                        printf("\nO caixa %hd foi fechado e os clientes mandados pra fila do caixa %d.\n",caixa+1,destino+1);
                    }
                }
                break;
            case 4:
                if (caixasAtivos == 5)
                    printf("\nTodos os caixas ja estao abertos.\n");
                else {
                    caixa = escolherCaixa(caixas, 4);
                    caixasAtivos++;
                    caixas[caixa].estado = true;
                    printf("\nO caixa %hd foi aberto.\n",caixa+1);
                }
                break;
            case 5:
                printf("\nDADOS DOS CLIENTES DO MERCADO\n");
                for (int i=0; i<MAX_CAIXAS; i++) {
                    if (!caixas[i].estado)
                        printf("\n------ CAIXA %hd ESTA FECHADO. SEM CLIENTES. ------\n",caixas[i].id);
                    else if (caixas[i].fila.inicio == NULL)
                        printf("\n------ CAIXA %hd ESTA ABERTO, MAS SEM CLIENTES. ------\n",caixas[i].id);
                    else {
                        printf("\n------ CAIXA %hd ESTA ABERTO, COM %hd CLIENTES. ------\n",caixas[i].id,quantclientes(&caixas[i].fila));
                        imprimirfila(&caixas[i].fila);
                    }
                }
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return 0;
            default:
                printf("Opcao invalida. Escolha de 0 a 4.\n");
                break;
        }
    }
}