#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"

// Limpa a tela do console de forma mais robusta e portável
void limpar_tela(void) {
    printf("\033[2J\033[H");
}

// Renderiza a mesa de jogo (RF-04)
void exibir_estado_jogo(Jogo* jogo, Jogador* atual) {
    if (jogo == NULL || atual == NULL) return;

    limpar_tela();
    printf("=========================================\n");
    printf("         SIMULADOR MULTIPLAYER UNO\n");
    printf("=========================================\n\n");

    printf("[Sentido do Jogo]: %s\n", jogo->sentido_jogo == 1 ? "Horario (->)" : "Anti-Horario (<-)");
    
    Carta topo = top(jogo->monte_descarte);
    printf("\n--- TOPO DO DESCARTE ---\n");
    printf("      ");
    exibir_carta(topo);
    printf("\n\n");

    printf("=========================================\n");
    printf(">>> VEZ DO JOGADOR: %s\n", atual->nome);
    printf("=========================================\n");
    printf("Sua Mao:\n");
    
    // Renderiza as opções das cartas usando a Lista Circular
    NodeCarta* node_atual = atual->mao_cartas->sentinela->proximo;
    int i = 0;
    while (node_atual != atual->mao_cartas->sentinela) {
        printf(" [%d] ", i);
        exibir_carta(node_atual->c);
        printf("\n");
        node_atual = node_atual->proximo;
        i++;
    }
    
    printf("\n [%d] Comprar uma carta / Passar a vez\n", i);
    printf("=========================================\n");
}

// Captura e sanitiza a entrada do usuário (RNF-06)
int ler_entrada_inteira(const char* prompt, int min, int max) {
    char buffer[100];
    int escolha;
    int valido = 0;

    while (!valido) {
        printf("%s", prompt);
        
        // Lê a linha inteira como string para evitar buffer preso
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Tenta extrair um inteiro da string digitada
            if (sscanf(buffer, "%d", &escolha) == 1) {
                if (escolha >= min && escolha <= max) {
                    valido = 1;
                } else {
                    printf(">> Erro: Por favor, digite um numero entre %d e %d.\n", min, max);
                }
            } else {
                printf(">> Erro: Entrada invalida. Voce digitou texto. Digite um NUMERO.\n");
            }
        }
    }
    return escolha;
}

// Pausa a tela para mostrar avisos (ex: "Jogada Inválida", "Voce comprou X")
void exibir_mensagem(const char* msg) {
    printf("\n>> %s\n", msg);
    printf("Pressione [ENTER] para continuar...");
    
    int c;
    // Como o fgets já limpou o buffer na leitura da jogada, 
    // este getchar() vai simplesmente esperar o próximo Enter do usuário.
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Tela final (UC-06)
void exibir_vencedor(Jogador* vencedor) {
    if (vencedor == NULL) return;
    limpar_tela();
    printf("=========================================\n");
    printf("                FIM DE JOGO!             \n");
    printf("=========================================\n\n");
    printf("   PARABENS, %s! VOCE ESVAZIOU SUA MAO!\n", vencedor->nome);
    printf("             VOCE E O CAMPEAO!           \n\n");
    printf("=========================================\n");
}
