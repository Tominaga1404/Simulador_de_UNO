# 🃏 Simulador de UNO em C

Este projeto é um simulador em terminal do clássico jogo de cartas UNO, desenvolvido inteiramente na linguagem C. O objetivo principal é recriar as regras tradicionais do jogo aplicando conceitos avançados de Estruturas de Dados Dinâmicas e o padrão de arquitetura MVC (Model-View-Controller) para garantir um código limpo, modular e eficiente.

---

## 🎮 Funcionalidades

* **Partidas dinâmicas:** Suporte para 2 a 4 jogadores, garantindo o equilíbrio das cartas e o ritmo ideal do jogo.
* **Interface via Terminal (View):** Exibição clara do estado do jogo, carta no topo do descarte e a mão atual do jogador.
* **Controle de Turnos Flexível:** Sistema que permite inversão de fluxo e pulo de turnos (comportamentos clássicos das cartas especiais do UNO).

---

## 🏗️ Arquitetura e Estruturas de Dados

O projeto foi construído separando a lógica de negócios da interface, utilizando estruturas de dados dinâmicas escolhidas a dedo para otimizar o tempo de execução:

### 1. Pilha (`pilha.c`)
Utilizada para gerenciar o **Monte de Compra** e o **Monte de Descarte**. 
* **Por quê?** Segue o princípio LIFO (Last In, First Out). A última carta jogada no descarte é a que fica visível no topo, e as cartas de compra são retiradas estritamente do topo, replicando o comportamento físico de um baralho.

### 2. Fila Dinâmica (`fila.c`)
Responsável pelo **Gerenciamento de Turnos** dos jogadores.
* **Por quê?** Permite organizar quem é o próximo a jogar de forma dinâmica, facilitando a alteração da ordem, aplicação de "Pular Vez" ou "Inverter Sentido" em tempo real de execução.

### 3. Lista Duplamente Encadeada Circular (`lista_circular.c`)
Representa a **Mão de Cartas** de cada jogador.
* **Por quê?** Foco na **velocidade e eficiência (tempo de execução)**. Diferente de um array dinâmico — que exigiria o deslocamento de múltiplos elementos na memória ao remover uma carta do meio da mão — a lista duplamente encadeada circular permite inserções e remoções reajustando apenas os ponteiros. Além disso, permite navegação fluida em ambas as direções.

---

## 📂 Estrutura Principal dos Arquivos

* `main.c`: O ponto de partida (botão de ligar) do jogo. Coleta a quantidade e o nome dos jogadores e inicia o loop principal.
* `jogo.h`: Cabeçalhos, assinaturas de funções e declarações de variáveis do escopo do jogo.
* `jogo.c`: Implementação da lógica principal (inicialização do ambiente, configuração de jogadores e limpeza de memória com `liberar_jogo`).
* `pilha.c` / `fila.c` / `lista_circular.c`: Implementação das estruturas de dados base.
* **View**: Módulo exclusivo para desenhar a interface no terminal e capturar os inputs do usuário, sem armazenar regras de negócio.

---

## 🚀 Como Executar

1. Compile o projeto utilizando o GCC (ou o compilador C de sua preferência):
   ```bash
   gcc src/*.c -o uno_simulator
