#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criar_fila(void) {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f == NULL) {
        fprintf(stderr, "Erro de alocacao para Fila.\n");
        exit(EXIT_FAILURE);
    }
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila* f, Jogador* j) {
    if (f == NULL || j == NULL) return;
    
    NodeJogador* novo = (NodeJogador*)malloc(sizeof(NodeJogador));
    if (novo == NULL) {
        fprintf(stderr, "Erro de alocacao para NodeJogador.\n");
        exit(EXIT_FAILURE);
    }
    novo->jogador = j;
    novo->proximo = NULL;

    if (f->tamanho == 0) {
        f->frente = novo;
    } else {
        f->tras->proximo = novo;
    }
    f->tras = novo;
    f->tamanho++;
}

Jogador* desenfileirar(Fila* f) {
    if (f == NULL || f->tamanho == 0) {
        fprintf(stderr, "Erro: Tentativa de desenfileirar fila vazia.\n");
        exit(EXIT_FAILURE);
    }
    
    NodeJogador* temp = f->frente;
    Jogador* j = temp->jogador;
    
    f->frente = f->frente->proximo;
    if (f->frente == NULL) {
        f->tras = NULL;
    }
    
    free(temp);
    f->tamanho--;
    return j;
}

Jogador* proximo_jogador(Fila* f) {
    if (f == NULL || f->tamanho == 0) return NULL;
    return f->frente->jogador; // Retorna o jogador sem retirá-lo da fila
}

void liberar_fila(Fila* f) {
    if (f == NULL) return;
    // O NodeJogador é limpo aqui. 
    // OBS: A struct Jogador em si será liberada no jogo.c, para manter a hierarquia.
    while (f->tamanho > 0) {
        desenfileirar(f); 
    }
    free(f);
}
