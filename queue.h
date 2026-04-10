#ifndef QUEUE_H
#define QUEUE_H

#include "stack.h"

/* 
 * Estrutura da fila circular com vetor dinâmico.
 * data guarda ponteiros para strings alocadas dinamicamente.
 */
typedef struct {
    char **data;    /* Vetor de strings da fila. */
    int front;      /* Índice do primeiro elemento. */
    int rear;       /* Índice da próxima posição livre. */
    int size;       /* Quantidade atual de elementos. */
    int capacity;   /* Capacidade total do vetor. */
} Queue;

/* Inicializa a fila com a capacidade inicial informada. */
int queue_init(Queue *q, int initial_capacity);

/* Verifica se a fila está vazia. */
int queue_is_empty(const Queue *q);

/* Verifica se a fila atingiu sua capacidade máxima atual. */
int queue_is_full(const Queue *q);

/* Insere um novo texto no final da fila. */
int queue_enqueue(Queue *q, const char *text);

/* Remove o texto do início da fila. */
int queue_dequeue(Queue *q, char *out_text);

/* Exibe os elementos atualmente armazenados na fila. */
void queue_print(const Queue *q);

/* Libera toda a memória usada pela fila. */
void queue_destroy(Queue *q);

#endif
