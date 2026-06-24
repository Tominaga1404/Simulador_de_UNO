#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "controller.h"

void gerar_baralho(Pilha* monte_compra) {
    if (monte_compra == NULL) return;

    CorCarta cores[] = {VERMELHO, VERDE, AZUL, AMARELO};
    
    // Para cada uma das 4 cores
    for (int c = 0; c < 4; c++) {
        CorCarta cor = cores[c];

        // Cartas Normais: Um '0' e duas de '1' a '9' por cor
        for (int valor = 0; valor <= 9; valor++) {
            Carta carta = {cor, valor, NORMAL};
            push(monte_compra, carta);
            if (valor != 0) { 
                push(monte_compra, carta); // Duplica as cartas de 1 a 9
            }
        }

        // Cartas Especiais: Duas de cada tipo por cor
        TipoCarta especiais[] = {INVERTER, COMPRAR_DOIS, PULAR};
        for (int e = 0; e < 3; e++) {
            Carta especial = {cor, -1, especiais[e]};
            push(monte_compra, especial);
            push(monte_compra, especial); // Duplica as especiais
        }
    }
}

void embaralhar_pilha(Pilha* p) {
    if (p == NULL || p->tamanho == 0) return;

    int n = p->tamanho;
    
    // Aloca um array temporário para permitir o embaralhamento
    Carta* array_temp = (Carta*)malloc(n * sizeof(Carta));
    if (array_temp == NULL) {
        fprintf(stderr, "Erro de alocacao no embaralhamento.\n");
        exit(EXIT_FAILURE);
    }

    // 1. Desempilha tudo para o array
    for (int i = 0; i < n; i++) {
        array_temp[i] = pop(p);
    }

    // 2. Algoritmo de Fisher-Yates Shuffle
    // AVISO: O srand(time(NULL)) foi removido daqui e DEVE ser colocado no main.c
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = array_temp[i];
        array_temp[i] = array_temp[j];
        array_temp[j] = temp;
    }

    // 3. Empilha de volta
    for (int i = 0; i < n; i++) {
        push(p, array_temp[i]);
    }

    free(array_temp);
}

void distribuir_cartas(Jogo* jogo) {
    if (jogo == NULL || jogo->fila_turnos->tamanho == 0) return;

    int qtd_jogadores = jogo->fila_turnos->tamanho;
    
    // Distribui 7 cartas por jogador (RF-03)
    for (int i = 0; i < 7; i++) { 
        for (int j = 0; j < qtd_jogadores; j++) {
            // Desenfileira o jogador atual
            Jogador* atual = desenfileirar(jogo->fila_turnos);

            // Tira uma carta do topo do monte de compra
            if (!pilha_vazia(jogo->monte_compra)) {
                Carta c = pop(jogo->monte_compra);
                // Insere sempre no final da lista circular da mão do jogador
                inserir_carta(atual->mao_cartas, c, atual->mao_cartas->tamanho);
            }

            // Re-enfileira o jogador no final
            enfileirar(jogo->fila_turnos, atual);
        }
    }
}

void preparar_partida(Jogo* jogo) {
    if (jogo == NULL) return;
    
    // 1. Gera as cartas e coloca no monte de compra
    gerar_baralho(jogo->monte_compra);
    
    // 2. Embaralha
    embaralhar_pilha(jogo->monte_compra);
    
    // 3. Distribui as mãos iniciais
    distribuir_cartas(jogo);
    
    // 4. Vira a primeira carta do descarte (inaugura a mesa)
    if (!pilha_vazia(jogo->monte_compra)) {
        Carta primeira_carta = pop(jogo->monte_compra);
        push(jogo->monte_descarte, primeira_carta);
    }
}

int validar_jogada(Carta topo, Carta jogada) {
    // Mesma cor
    if (jogada.cor == topo.cor) return 1;
    // Mesmo número (apenas para cartas normais, valor != -1)
    if (jogada.tipo == NORMAL && topo.tipo == NORMAL && jogada.valor == topo.valor) return 1;
    // Mesmo tipo especial (ex: Inverter num Inverter de outra cor)
    if (jogada.tipo != NORMAL && jogada.tipo == topo.tipo) return 1;
    
    return 0; // Jogada Inválida
}

// Quando o baralho esvazia, pega o descarte e recicla (RF-10)
void reciclar_baralho(Jogo* jogo) {
    if (jogo == NULL || pilha_vazia(jogo->monte_descarte)) return;

    // Salva a carta atual do topo para não ser embaralhada
    Carta topo_atual = pop(jogo->monte_descarte);
    
    // Move o restante das cartas do descarte para o monte de compra
    while (!pilha_vazia(jogo->monte_descarte)) {
        push(jogo->monte_compra, pop(jogo->monte_descarte));
    }
    
    // Embaralha o novo monte de compra
    embaralhar_pilha(jogo->monte_compra);
    
    // Devolve o topo para a mesa
    push(jogo->monte_descarte, topo_atual);
}

// Lida com a ação de comprar carta no turno, checando se precisa reciclar (RF-06 e RF-10)
void comprar_carta_turno(Jogo* jogo, Jogador* jogador) {
    if (jogo == NULL || jogador == NULL) return;

    // Se a compra secou, recicla o descarte
    if (pilha_vazia(jogo->monte_compra)) {
        reciclar_baralho(jogo);
    }
    
    // Se, mesmo após reciclar, houver cartas, realiza a compra
    if (!pilha_vazia(jogo->monte_compra)) {
        Carta c = pop(jogo->monte_compra);
        inserir_carta(jogador->mao_cartas, c, jogador->mao_cartas->tamanho);
    }
}

// Inverte fisicamente a ordem dos jogadores na fila
void inverter_ordem_fila(Fila* f) {
    if (f == NULL || f->tamanho <= 1) return;
    
    int tam = f->tamanho;
    Jogador** temp_array = (Jogador**)malloc(tam * sizeof(Jogador*));
    
    // 1. Esvazia a fila no array
    for (int i = 0; i < tam; i++) {
        temp_array[i] = desenfileirar(f);
    }
    
    // 2. Re-enfileira de trás para frente
    for (int i = tam - 1; i >= 0; i--) {
        enfileirar(f, temp_array[i]);
    }
    
    free(temp_array);
}

void finalizar_turno(Jogo* jogo, Carta* carta_jogada) {
    if (jogo == NULL || jogo->fila_turnos->tamanho == 0) return;

    // 1. O Controller assume a responsabilidade isolada de tirar o jogador da vez
    Jogador* atual = desenfileirar(jogo->fila_turnos);

    // 2. Se nenhuma carta especial foi jogada (normal ou apenas passou a vez)
    if (carta_jogada == NULL || carta_jogada->tipo == NORMAL) {
        enfileirar(jogo->fila_turnos, atual);
        return;
    }

    // 3. Aplicacao dos Efeitos Especiais
    if (carta_jogada->tipo == INVERTER) {
        jogo->sentido_jogo *= -1; // Atualiza o log da UI
        
        // Inverte a fila com os restantes e DEPOIS insere o atual no final.
        // Isso garante que quem jogou antes dele se torne o proximo.
        inverter_ordem_fila(jogo->fila_turnos);
        enfileirar(jogo->fila_turnos, atual);
    } 
    else if (carta_jogada->tipo == PULAR) {
        // Atual vai pro final da fila
        enfileirar(jogo->fila_turnos, atual);
        
        // O proximo e sumariamente removido e jogado pro final (pulado)
        Jogador* pulado = desenfileirar(jogo->fila_turnos);
        enfileirar(jogo->fila_turnos, pulado);
    } 
    else if (carta_jogada->tipo == COMPRAR_DOIS) {
        // Atual vai pro final da fila
        enfileirar(jogo->fila_turnos, atual); 
        
        // Identifica a vitima, faz comprar e depois a pula
        Jogador* vitima = proximo_jogador(jogo->fila_turnos);
        if (vitima != NULL) {
            comprar_carta_turno(jogo, vitima);
            comprar_carta_turno(jogo, vitima);
            
            Jogador* pulado = desenfileirar(jogo->fila_turnos);
            enfileirar(jogo->fila_turnos, pulado);
        }
    }
}
