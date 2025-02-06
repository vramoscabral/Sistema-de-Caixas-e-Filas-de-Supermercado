#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cliente.h"

#define MAX_CAIXAS 4

typedef short int si;

typedef struct FilaPrioridade {
    Cliente *inicio;
    Cliente *fim;
} FilaPrioridade;

typedef struct Caixa {
    int id;
    bool estado;
    FilaPrioridade fila;
} Caixa;

void inicializarFila(FilaPrioridade *fila);
void inicializarCaixa(Caixa *caixa, int id);
si escolherCaixa(Caixa *caixas, si tipo);
void cadastrar(FilaPrioridade *fila, Cliente* c);
Cliente* remover(FilaPrioridade *fila);
void imprimirfila(FilaPrioridade *fila);
si filaVazia(FilaPrioridade *fila);
si quantclientes(FilaPrioridade *fila);
bool existeCpf(Caixa *caixas, int numcaixas, char *cpf);
void liberarFila(FilaPrioridade *fila);
bool mercadoVazio(Caixa *caixas);

#endif