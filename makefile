# Nome do executável
TARGET = gol

# Compilador e flags de compilação
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

# Arquivos de origem e cabeçalhos
SRCS = main.c grid.c cost.c perturbation.c simulated_annealing.c
HDRS = grid.h cost.h perturbation.h simulated_annealing.h

# Arquivos objeto (os .o serão gerados a partir dos .c)
OBJS = $(SRCS:.c=.o)

# Regra principal para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilar os arquivos objeto
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

# Regra padrão
.PHONY: clean run
