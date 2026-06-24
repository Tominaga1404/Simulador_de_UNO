#ifndef VIEW_H
#define VIEW_H

#include "jogo.h"
#include "carta.h"

// Funções de saída (Renderização)
void limpar_tela(void);
void exibir_estado_jogo(Jogo* jogo, Jogador* atual);
void exibir_mensagem(const char* msg);
void exibir_vencedor(Jogador* vencedor);

// Função de entrada segura (Input)
int ler_entrada_inteira(const char* prompt, int min, int max);

#endif
