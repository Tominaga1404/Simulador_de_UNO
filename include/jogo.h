#ifndef JOGO_H
#define JOGO_H

#include "pilha.h"
#include "fila.h"

typedef struct {
    Pilha* monte_compra;
    Pilha* monte_descarte;
    Fila* fila_turnos;
    int sentido_jogo; // 1 para horário (padrão), -1 para anti-horário
} Jogo;

Jogo* inicializar_jogo(void);
void configurar_jogadores(Jogo* jogo, int num_jogadores, char nomes[][50]);
void liberar_jogo(Jogo* jogo);

#endif
