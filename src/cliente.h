#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>

typedef short int si;

typedef struct Cliente {
    char nome[102];
    char cpf[13];
    si prioridade;
    si itens;
    struct Cliente *prox;
} Cliente;

void cadnome(Cliente *c);
void cadcpf(Cliente *c);
void cadprior(Cliente *c);
void caditens(Cliente *c);
void limparBufferEntrada();

#endif