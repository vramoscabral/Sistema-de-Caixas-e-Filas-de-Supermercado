#include "fila.h"

void inicializarFila(FilaPrioridade *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void inicializarCaixa(Caixa *caixa, int id) {
    caixa->id = id;
    caixa->estado = true;
    inicializarFila(&(caixa->fila));
}

si escolherCaixa(Caixa *caixas, si tipo) {
    int resultado;
    si numcaixa;

    do {
        if (tipo == 4) {
            printf("\nCAIXAS FECHADOS: ");
            for (int i=0; i < MAX_CAIXAS; i++)
            {
                if (!caixas[i].estado)
                    printf("%d   ",i+1);
            }
        }
        else if (tipo == 2) {
            printf("\nCAIXAS COM CLIENTES EM ESPERA: ");
            for (int i=0; i < MAX_CAIXAS; i++)
            {
                if (caixas[i].estado && quantclientes(&caixas[i].fila) > 0)
                    printf("%d  ",i+1);
            }
        }
        else {
            printf("\nCAIXAS ABERTOS: ");
            for (int i=0; i < MAX_CAIXAS; i++)
            {
                if (caixas[i].estado)
                    printf("%d  ",i+1);
            }
        }

        if (tipo == 1)
            printf("\nEscolha um caixa para inserir cliente: ");
        else if (tipo == 2)
            printf("\nEscolha um caixa para fazer atendimento: ");
        else if (tipo == 3)
            printf("\nEscolha um caixa para fechar: ");
        else
            printf("\nEscolha um caixa para abrir: ");
        resultado = scanf("%hd", &numcaixa);

        if (tipo == 4) {
            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n');
            } else if (caixas[numcaixa-1].estado || numcaixa < 1 || numcaixa > 5) {
                printf("Erro: Escolha um caixa disponivel.\n");
                resultado = 0;
            }
        }
        else if (tipo == 2) {
            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n');
            } else if (!caixas[numcaixa-1].estado || quantclientes(&caixas[numcaixa-1].fila) == 0 || numcaixa < 1 || numcaixa > 5) {
                printf("Erro: Escolha um caixa disponivel.\n");
                resultado = 0;
            }
        }
        else {
            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n');
            } else if (!caixas[numcaixa-1].estado || numcaixa < 1 || numcaixa > 5) {
                printf("Erro: Escolha um caixa disponivel.\n");
                resultado = 0;
            }
        }
    } while (resultado != 1);

    return numcaixa-1;
}

void cadastrar(FilaPrioridade *fila, Cliente *c) {
    Cliente *f = (Cliente*) malloc(sizeof(Cliente));
    Cliente *atual = fila->inicio;
    strcpy(f->nome, c->nome);
    strcpy(f->cpf, c->cpf);
    f->prioridade = c->prioridade;
    f->itens = c->itens;
    f->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = f;
        fila->fim = f;
    }
    else if (fila->fim->prioridade == 1) {
        fila->fim->prox = f;
        fila->fim = f;
    }
    else if (fila->fim->prioridade == 2) {
        if (c->prioridade == 2 || c->prioridade == 3) {
            fila->fim->prox = f;
            fila->fim = f;
        }
        else {
            while (atual != NULL)
            {
                if (atual->prioridade == 2 && atual == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (atual->prox->prioridade == 2) {
                    f->prox = atual->prox;
                    atual->prox = f;
                    break;
                }
                atual = atual->prox;
            }
        }
    }
    else {
        if (c->prioridade == 3) {
            fila->fim->prox = f;
            fila->fim = f;
        }
        else if (c->prioridade == 2) {
            while (atual != NULL)
            {
                if (atual->prioridade == 3 && atual == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (atual->prox->prioridade == 3) {
                    f->prox = atual->prox;
                    atual->prox = f;
                    break;
                }
                atual = atual->prox;
            }
        }
        else {
            while (atual != NULL)
            {
                if (atual->prioridade == 2 && atual == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (atual->prioridade == 3 && atual == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (atual->prox->prioridade == 2) {
                    f->prox = atual->prox;
                    atual->prox = f;
                    break;
                }
                else if (atual->prox->prioridade == 3) {
                    f->prox = atual->prox;
                    atual->prox = f;
                    break;
                }
                atual = atual->prox;
            }
        }
    }
}

void imprimirfila(FilaPrioridade *fila) {
    Cliente *atual = fila->inicio;
    si cl = 1;
    while (atual != NULL) {
        printf("\nCliente %hd -> ",cl);
        printf("Prioridade: %hd / ",atual->prioridade);
        printf("Nome: %s / ",atual->nome);
        printf("CPF: %c%c%c.%c%c%c.%c%c%c-%c%c / ", 
               atual->cpf[0], atual->cpf[1], atual->cpf[2], 
               atual->cpf[3], atual->cpf[4], atual->cpf[5], 
               atual->cpf[6], atual->cpf[7], atual->cpf[8], 
               atual->cpf[9], atual->cpf[10]);
        printf("Itens: %hd\n",atual->itens);
        atual = atual->prox;
        cl++;
    }
    printf("\n");
}

Cliente* remover(FilaPrioridade *fila) {
    Cliente *f = (Cliente*) malloc(sizeof(Cliente));
    Cliente *removido = fila->inicio;
    strcpy(f->nome, removido->nome);
    strcpy(f->cpf, removido->cpf);
    f->prioridade = removido->prioridade;
    f->itens = removido->itens;
    fila->inicio = removido->prox;
    
    free(removido);
    return f;
}

si filaVazia(FilaPrioridade *fila) {
    return fila->inicio == NULL;
}

si quantclientes(FilaPrioridade *fila) {
    Cliente *atual = fila->inicio;
    si cl = 0;
    while (atual != NULL) {
        atual = atual->prox;
        cl++;
    }
    return cl;
}

bool existeCpf(Caixa *caixas, int numcaixas, char *cpf) {
    for (int i = 0; i < numcaixas; i++) {
        Cliente *atual = caixas[i].fila.inicio;
        
        while (atual != NULL) {
            if (strcmp(cpf, atual->cpf) == 0) {
                return true;
            }
            atual = atual->prox;
        }
    }
    return false;
}

void liberarFila(FilaPrioridade *fila) {
    Cliente *atual = fila->inicio;
    while (atual != NULL) {
        Cliente *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

bool mercadoVazio(Caixa* caixas) {
    int quant = 0;
    for (int i = 0; i < MAX_CAIXAS; i++) {
        quant = quantclientes(&caixas[i].fila);
        if (quant > 0) {
            return false;
        }
    }
    return true;
}