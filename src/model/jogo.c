#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

Jogo* inicializar_jogo(void) {
    Jogo* jogo = (Jogo*)malloc(sizeof(Jogo));
    if (jogo == NULL) {
        fprintf(stderr, "Erro de alocacao para Jogo.\n");
        exit(EXIT_FAILURE);
    }
    
    jogo->monte_compra = criar_pilha();
    jogo->monte_descarte = criar_pilha();
    jogo->fila_turnos = criar_fila();
    jogo->sentido_jogo = 1; // 1 = Sentido Horário
    
    return jogo;
}

void configurar_jogadores(Jogo* jogo, int num_jogadores, char nomes[][50]) {
    if (jogo == NULL || num_jogadores < 2 || num_jogadores > 4) {
        fprintf(stderr, "Numero de jogadores invalido. Deve ser entre 2 e 4.\n");
        return;
    }
    
    for (int i = 0; i < num_jogadores; i++) {
        Jogador* j = (Jogador*)malloc(sizeof(Jogador));
        if (j == NULL) {
            fprintf(stderr, "Erro de alocacao para Jogador.\n");
            exit(EXIT_FAILURE);
        }
        
        j->id = i + 1;
        strncpy(j->nome, nomes[i], 49);
        j->nome[49] = '\0'; // Garante o fechamento da string
        j->mao_cartas = criar_lista(); // Instancia a Mão (Lista Circular)
        
        // Coloca o jogador na ordem de turnos
        enfileirar(jogo->fila_turnos, j);
    }
}

void liberar_jogo(Jogo* jogo) {
    if (jogo == NULL) return;
    
    // 1. Limpa as cartas da mesa (Pilhas)
    liberar_pilha(jogo->monte_compra);
    liberar_pilha(jogo->monte_descarte);
    
    // 2. Esvazia a fila corretamente usando a interface da Fila
    while (jogo->fila_turnos->tamanho > 0) {
        Jogador* j = desenfileirar(jogo->fila_turnos);
        liberar_lista(j->mao_cartas); // Libera a Lista Circular (Mão)
        free(j);                      // Libera a struct Jogador
    }
    
    // 3. Libera a Fila (que agora está garantidamente vazia) e o Jogo
    liberar_fila(jogo->fila_turnos);
    free(jogo);
}
