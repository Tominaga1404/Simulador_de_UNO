#include <stdio.h>
#include <stdlib.h>
#include "lista_circular.h"

Lista* criar_lista(void) {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    NodeCarta* s = (NodeCarta*)malloc(sizeof(NodeCarta));
    if (l == NULL || s == NULL) {
        fprintf(stderr, "Erro de alocacao para Lista Duplamente Encadeada.\n");
        exit(EXIT_FAILURE);
    }
    // Configura o nó sentinela apontando para si mesmo
    s->c.valor = -99; 
    s->c.tipo = NORMAL;
    s->c.cor = VERMELHO;

    s->proximo = s;
    s->anterior = s;
    l->sentinela = s;
    l->tamanho = 0;
    return l;
}

void inserir_carta(Lista* l, Carta c, int posicao) {
    if (l == NULL || posicao < 0 || posicao > l->tamanho){
        fprintf(stderr, "Erro: Tentativa de insercao em posicao invalida (%d).\n", posicao);
        return;
    };

    NodeCarta* novo = (NodeCarta*)malloc(sizeof(NodeCarta));
    if (novo == NULL) {
        fprintf(stderr, "Erro de alocacao para NodeCarta.\n");
        exit(EXIT_FAILURE);
    }
    novo->c = c;

    NodeCarta* atual = l->sentinela;
    // Caminha ate a posicao de insercao
    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }

    // Ajusta os ponteiros para inserir 'novo' entre 'atual' e 'atual->proximo'
    novo->proximo = atual->proximo;
    novo->anterior = atual;
    atual->proximo->anterior = novo;
    atual->proximo = novo;

    l->tamanho++;
}

Carta remover_carta(Lista* l, int posicao) {
    if (l == NULL || l->tamanho == 0 || posicao < 0 || posicao >= l->tamanho) {
        fprintf(stderr, "Erro: Posicao invalida para remocao.\n");
        exit(EXIT_FAILURE);
    }

    NodeCarta* atual = l->sentinela->proximo;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }

    Carta c = atual->c;
    atual->anterior->proximo = atual->proximo;
    atual->proximo->anterior = atual->anterior;
    
    free(atual);
    l->tamanho--;
    return c;
}

int buscar_carta(Lista* l, Carta c) {
    if (l == NULL) return -1;
    NodeCarta* atual = l->sentinela->proximo;
    int indice = 0;
    
    while (atual != l->sentinela) {
        if (atual->c.cor == c.cor && atual->c.valor == c.valor && atual->c.tipo == c.tipo) {
            return indice;
        }
        atual = atual->proximo;
        indice++;
    }
    return -1;
}

void percorrer_lista(Lista* l, int sentido) {
    if (l == NULL || l->tamanho == 0) {
        printf("Mao vazia.\n");
        return;
    }
    
    NodeCarta* atual;
    if (sentido >= 0) { // Horário / Frente
        atual = l->sentinela->proximo;
        while (atual != l->sentinela) {
            exibir_carta(atual->c);
            printf(" ");
            atual = atual->proximo;
        }
    } else { // Anti-horário / Trás
        atual = l->sentinela->anterior;
        while (atual != l->sentinela) {
            exibir_carta(atual->c);
            printf(" ");
            atual = atual->anterior;
        }
    }
    printf("\n");
}

void liberar_lista(Lista* l) {
    if (l == NULL) return;
    NodeCarta* atual = l->sentinela->proximo;
    while (atual != l->sentinela) {
        NodeCarta* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(l->sentinela);
    free(l);
}
