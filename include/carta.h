#ifndef CARTA_H
#define CARTA_H

typedef enum { NORMAL, INVERTER, COMPRAR_DOIS, PULAR } TipoCarta;
typedef enum { VERMELHO, VERDE, AZUL, AMARELO } CorCarta;

typedef struct {
    CorCarta cor;
    int valor; // 0 a 9 para normais; -1 para especiais
    TipoCarta tipo;
} Carta;

const char* obter_nome_cor(CorCarta cor);
const char* obter_nome_tipo(TipoCarta tipo);
void exibir_carta(Carta c);
Carta carta_criar(CorCarta cor, int valor, TipoCarta tipo);

#endif
