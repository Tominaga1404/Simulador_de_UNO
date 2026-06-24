#include <stdio.h>
#include "carta.h"

const char* obter_nome_cor(CorCarta cor) {
    switch(cor) {
        case VERMELHO: return "Vermelho";
        case VERDE:    return "Verde";
        case AZUL:     return "Azul";
        case AMARELO:  return "Amarelo";
        default:       return "Desconhecida";
    }
}

const char* obter_nome_tipo(TipoCarta tipo) {
    switch(tipo) {
        case NORMAL:       return "Normal";
        case INVERTER:     return "Inverter";
        case COMPRAR_DOIS: return "+2";
        case PULAR:        return "Pular";
        default:           return "Desconhecido";
    }
}

void exibir_carta(Carta c) {
    if (c.tipo == NORMAL) {
        printf("[%s %d]", obter_nome_cor(c.cor), c.valor);
    } else {
        printf("[%s %s]", obter_nome_cor(c.cor), obter_nome_tipo(c.tipo));
    }
}

Carta carta_criar(CorCarta cor, int valor, TipoCarta tipo) {
    Carta c;
    c.cor = cor;
    c.valor = valor;
    c.tipo = tipo;
    return c;
}
