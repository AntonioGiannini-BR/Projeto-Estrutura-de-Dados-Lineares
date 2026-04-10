# Compilador
CC = gcc

# Flags de compilação (avisos e padrão C11)
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Nome do executável
TARGET = textmanager

# Arquivos fonte
SRC = main.c stack.c queue.c dlist.c

# Arquivos objeto
OBJ = main.o stack.o queue.o dlist.o

# Regra padrão
all: $(TARGET)

# Gera o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compila cada .c em .o
main.o: main.c stack.h queue.h dlist.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

dlist.o: dlist.c dlist.h
	$(CC) $(CFLAGS) -c dlist.c

# Limpa arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)

# Executa o programa
run: $(TARGET)
	./$(TARGET)
