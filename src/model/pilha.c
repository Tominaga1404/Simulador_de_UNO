#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* criar_pilha(void) {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para a Pilha.\n");
        exit(EXIT_FAILURE);
    }
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void push(Pilha* p, Carta c) {
    if (p == NULL) return;
    NodePilha* novo = (NodePilha*)malloc(sizeof(NodePilha));
    if (novo == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o NodePilha.\n");
        exit(EXIT_FAILURE);
    }
    novo->c = c;
    novo->abaixo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

Carta pop(Pilha* p) {
    if (p == NULL || pilha_vazia(p)) {
        fprintf(stderr, "Erro: Tentativa de pop em pilha vazia.\n");
        exit(EXIT_FAILURE);
    }
    NodePilha* antigo_topo = p->topo;
    Carta c = antigo_topo->c;
    p->topo = antigo_topo->abaixo;
    free(antigo_topo);
    p->tamanho--;
    return c;
}

Carta top(Pilha* p) {
    if (p == NULL || pilha_vazia(p)) {
        fprintf(stderr, "Erro: Tentativa de ler topo de pilha vazia.\n");
        exit(EXIT_FAILURE);
    }
    return p->topo->c;
}

int pilha_vazia(Pilha* p) {
    return (p == NULL || p->topo == NULL);
}

void liberar_pilha(Pilha* p) {
    if (p == NULL) return;
    while (!pilha_vazia(p)) {
        pop(p);
    }
    free(p);
}
