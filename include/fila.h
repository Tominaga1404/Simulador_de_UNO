#ifndef FILA_H
#define FILA_H

#include "lista_circular.h" // Necessário pois o Jogador possui uma Lista (mão de cartas)

// Estrutura do Jogador conforme o diagrama de classes
typedef struct Jogador {
    int id;
    char nome[50];
    Lista* mao_cartas;
} Jogador;

typedef struct NodeJogador {
    Jogador* jogador;
    struct NodeJogador* proximo;
} NodeJogador;

typedef struct {
    NodeJogador* frente;
    NodeJogador* tras;
    int tamanho;
} Fila;

Fila* criar_fila(void);
void enfileirar(Fila* f, Jogador* j);
Jogador* desenfileirar(Fila* f);
Jogador* proximo_jogador(Fila* f);
void liberar_fila(Fila* f);

#endif
