#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogo.h"
#include "controller.h"
#include "view.h"

int main(void) {
    // Semente única de aleatoriedade garantida fora dos loops
    srand((unsigned int)time(NULL));

    limpar_tela();
    printf("=========================================\n");
    printf("        PREPARACAO DA PARTIDA UNO        \n");
    printf("=========================================\n\n");

    int num_jogadores = ler_entrada_inteira(">> Quantos jogadores vao participar (2 a 4)? ", 2, 4);
    char nomes[4][50];
    
    // Captura os nomes
    for (int i = 0; i < num_jogadores; i++) {
        char prompt[50];
        snprintf(prompt, sizeof(prompt), ">> Nome do Jogador %d: ", i + 1);
        printf("%s", prompt);
        
        if (fgets(nomes[i], sizeof(nomes[i]), stdin) != NULL) {
            // Remove o \n do final da string lida pelo fgets
            nomes[i][strcspn(nomes[i], "\n")] = '\0'; 
        }
    }

    // Inicializa o Model Global
    Jogo* jogo = inicializar_jogo();
    configurar_jogadores(jogo, num_jogadores, nomes);
    preparar_partida(jogo);

    Jogador* vencedor = NULL;

    // LOOP PRINCIPAL (Execução dos Turnos)
    while (1) {
        // Consulta quem é o jogador do turno sem tirá-lo da fila ainda
        Jogador* atual = proximo_jogador(jogo->fila_turnos);
        
        // Renderiza a interface
        exibir_estado_jogo(jogo, atual);

        int indice_compra = atual->mao_cartas->tamanho;
        int escolha = ler_entrada_inteira(">> Digite o numero da carta ou compre: ", 0, indice_compra);

        // Variáveis seguras declaradas no topo do escopo para evitar ponteiros soltos
        Carta carta_jogada; 
        int realizou_jogada = 0; 
        Carta c_temp;

        if (escolha == indice_compra) {
            // O jogador optou por comprar
            comprar_carta_turno(jogo, atual);
            
            // CUMPRIMENTO DO RF-06: Checar se a carta comprada pode ser jogada
            NodeCarta* ultimo = atual->mao_cartas->sentinela->anterior; // Última carta adicionada
            Carta topo_atual = top(jogo->monte_descarte);
            
            if (validar_jogada(topo_atual, ultimo->c)) {
                exibir_estado_jogo(jogo, atual); // Renderiza a tela para mostrar a nova mão
                printf(">> VOCE COMPROU: ");
                exibir_carta(ultimo->c);
                printf("\n");
                
                int jogar_agora = ler_entrada_inteira(">> A carta comprada e valida! Jogar agora? (1 - Sim / 0 - Nao): ", 0, 1);
                
                if (jogar_agora == 1) {
                    // Remove a carta que acabou de entrar no fim da lista circular
                    c_temp = remover_carta(atual->mao_cartas, atual->mao_cartas->tamanho - 1);
                    push(jogo->monte_descarte, c_temp);
                    
                    // Copia a carta de forma segura e ativa a flag
                    carta_jogada = c_temp; 
                    realizou_jogada = 1;
                    
                    // Checa vitória rápida
                    if (atual->mao_cartas->tamanho == 0) {
                        vencedor = atual;
                        break;
                    }
                } else {
                    exibir_mensagem("Voce escolheu guardar a carta e passar a vez.");
                }
            } else {
                exibir_mensagem("Voce comprou uma carta e ela nao serve na mesa. Passando a vez...");
            }
        } else {
            // O jogador optou por tentar jogar uma carta que já estava na mão
            NodeCarta* n = atual->mao_cartas->sentinela->proximo;
            for (int k = 0; k < escolha; k++) {
                n = n->proximo;
            }
            
            Carta topo_atual = top(jogo->monte_descarte);
            
            if (validar_jogada(topo_atual, n->c)) {
                // Jogada válida: remove da mão e joga no descarte
                c_temp = remover_carta(atual->mao_cartas, escolha);
                push(jogo->monte_descarte, c_temp);
                
                // Copia a carta de forma segura e ativa a flag
                carta_jogada = c_temp;
                realizou_jogada = 1;
                
                // Condição de Vitória (RF-11)
                if (atual->mao_cartas->tamanho == 0) {
                    vencedor = atual;
                    break; 
                }
            } else {
                exibir_mensagem("JOGADA INVALIDA! A carta nao corresponde a cor, valor ou tipo do topo.");
                continue; // Repete a iteração forçando o jogador a tentar novamente, SEM avançar a fila
            }
        }

        // O Controller agora gerencia internamente a fila e os efeitos especiais
        finalizar_turno(jogo, realizou_jogada ? &carta_jogada : NULL);
    }

    // Rotina de Encerramento (UC-06)
    exibir_vencedor(vencedor);
    liberar_jogo(jogo);

    return 0;
}
