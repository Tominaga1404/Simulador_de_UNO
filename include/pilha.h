#ifndef PILHA_H
#define PILHA_H

#include "carta.h"

typedef struct NodePilha {
    Carta c;
    struct NodePilha* abaixo;
} NodePilha;

typedef struct {
    NodePilha* topo;
    int tamanho;
} Pilha;

Pilha* criar_pilha(void);
void push(Pilha* p, Carta c);
Carta pop(Pilha* p);
Carta top(Pilha* p);
int pilha_vazia(Pilha* p);
void liberar_pilha(Pilha* p);

#endif
