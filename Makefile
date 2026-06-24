# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Diretórios
SRC_DIR = src
MODEL_DIR = src/model
CTRL_DIR = src/controller
VIEW_DIR = src/view
TEST_DIR = tests

# Arquivos fonte principais (Exclui testes)
SRCS = $(SRC_DIR)/main.c \
       $(MODEL_DIR)/carta.c \
       $(MODEL_DIR)/pilha.c \
       $(MODEL_DIR)/lista_circular.c \
       $(MODEL_DIR)/fila.c \
       $(MODEL_DIR)/jogo.c \
       $(CTRL_DIR)/controller.c \
       $(VIEW_DIR)/view.c

# Objetos correspondentes
OBJS = $(SRCS:.c=.o)

# Nome do binário final do jogo
EXEC = uno_simulador

# Arquivo e executável de testes
TEST_SRC = $(TEST_DIR)/test_structs.c
TEST_EXEC = runner_testes

# Regra principal (compila o jogo)
all: $(EXEC)

# Linkagem do simulador
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos objetos genéricos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra exigida para os testes (make tests)
# Faz a linkagem do test_structs.c apenas com os objetos do Modelo
tests: $(MODEL_DIR)/carta.o $(MODEL_DIR)/pilha.o $(MODEL_DIR)/lista_circular.o $(MODEL_DIR)/fila.o $(MODEL_DIR)/jogo.o
	$(CC) $(CFLAGS) $(TEST_SRC) $^ -o $(TEST_EXEC)
	@echo "Testes compilados com sucesso. Rode ./$(TEST_EXEC) para executar."

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJS) $(EXEC) $(TEST_EXEC)
