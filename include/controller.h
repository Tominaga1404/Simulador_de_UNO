#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "jogo.h"

// Gera 100 cartas padrão (0-9, +2, Inverter, Pular) e coloca no monte de compra
void gerar_baralho(Pilha* monte_compra);

// Remove as cartas da pilha para um array dinâmico, embaralha e devolve para a pilha
void embaralhar_pilha(Pilha* p);

// Distribui 7 cartas para cada jogador presente na fila de turnos
void distribuir_cartas(Jogo* jogo);

// Função que orquestra a preparação inicial
void preparar_partida(Jogo* jogo);

// Validacoes e Regras de Negocio
int validar_jogada(Carta topo_descarte, Carta jogada);
void reciclar_baralho(Jogo* jogo);
void comprar_carta_turno(Jogo* jogo, Jogador* jogador);
void inverter_ordem_fila(Fila* fila);
void finalizar_turno(Jogo* jogo, Carta* carta_jogada);

#endif
