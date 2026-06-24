#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include "carta.h"

typedef struct NodeCarta {
    Carta c;
    struct NodeCarta* proximo;
    struct NodeCarta* anterior;
} NodeCarta;

typedef struct {
    NodeCarta* sentinela; // Usando um nó sentinela para facilitar a circularidade
    int tamanho;
} Lista;

Lista* criar_lista(void);
void inserir_carta(Lista* l, Carta c, int posicao);
Carta remover_carta(Lista* l, int posicao);
int buscar_carta(Lista* l, Carta c);
void percorrer_lista(Lista* l, int sentido);
void liberar_lista(Lista* l);

#endif
