#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/* 
 * Função interna para aumentar a capacidade da fila.
 * Dobra o tamanho do vetor e reorganiza os elementos a partir do índice 0.
 */
static int queue_resize(Queue *q) {
    int old_capacity = q->capacity;
    int new_capacity = old_capacity * 2;
    char **new_data = (char **) malloc((size_t)new_capacity * sizeof(char *));
    int i;

    if (new_data == NULL) {
        return 0;
    }

    /* Copia os elementos na ordem lógica da fila circular. */
    for (i = 0; i < q->size; i++) {
        new_data[i] = q->data[(q->front + i) % q->capacity];
    }

    /* Libera o vetor antigo e atualiza os metadados. */
    free(q->data);
    q->data = new_data;
    q->front = 0;
    q->rear = q->size;
    q->capacity = new_capacity;
    return 1;
}

/* Inicializa os campos da fila. */
int queue_init(Queue *q, int initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = 4; /* Valor padrão mínimo. */
    }

    q->data = (char **) malloc((size_t)initial_capacity * sizeof(char *));
    if (q->data == NULL) {
        return 0;
    }

    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = initial_capacity;
    return 1;
}

/* Verifica se não há elementos na fila. */
int queue_is_empty(const Queue *q) {
    return q->size == 0;
}

/* Verifica se todos os espaços do vetor estão ocupados. */
int queue_is_full(const Queue *q) {
    return q->size == q->capacity;
}

/* Insere uma cópia do texto no final da fila. */
int queue_enqueue(Queue *q, const char *text) {
    size_t len;
    char *copy;

    /* Se a fila estiver cheia, tenta dobrar a capacidade. */
    if (queue_is_full(q) && !queue_resize(q)) {
        return 0;
    }

    /* Aloca exatamente o espaço necessário para a string. */
    len = strlen(text);
    copy = (char *) malloc((len + 1) * sizeof(char));
    if (copy == NULL) {
        return 0;
    }

    /* Copia o texto e insere na posição rear. */
    strcpy(copy, text);
    q->data[q->rear] = copy;

    /* Rear avança circularmente. */
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
    return 1;
}

/* Remove o primeiro elemento da fila. */
int queue_dequeue(Queue *q, char *out_text) {
    char *temp;

    if (queue_is_empty(q)) {
        return 0;
    }

    /* Guarda o texto da frente da fila. */
    temp = q->data[q->front];

    /* Se necessário, devolve o texto para quem chamou. */
    if (out_text != NULL) {
        strncpy(out_text, temp, TEXT_SIZE - 1);
        out_text[TEXT_SIZE - 1] = '\0';
    }

    /* Libera a string removida e ajusta o início da fila. */
    free(temp);
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return 1;
}

/* Exibe os elementos na ordem de saída da fila. */
void queue_print(const Queue *q) {
    int i;

    if (queue_is_empty(q)) {
        printf("Fila de salvamento vazia.\n");
        return;
    }

    printf("\n--- Fila de salvamento ---\n");
    for (i = 0; i < q->size; i++) {
        printf("%d. %s\n", i + 1, q->data[(q->front + i) % q->capacity]);
    }
    printf("Capacidade atual: %d\n", q->capacity);
}

/* Libera todos os elementos e reseta os campos da fila. */
void queue_destroy(Queue *q) {
    char buffer[TEXT_SIZE];

    /* Remove e libera cada string armazenada. */
    while (queue_dequeue(q, buffer)) {
    }

    /* Libera o vetor principal e zera a estrutura. */
    free(q->data);
    q->data = NULL;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = 0;
}
