#ifndef DLIST_H
#define DLIST_H

#include "stack.h"

/* DList representa o ponteiro para o primeiro nó da lista dupla. */
typedef struct DNode* DList;

/* Verifica se a lista está vazia. */
int dlist_is_empty(DList head);

/* Insere uma palavra em ordem alfabética. */
int dlist_insert_sorted(DList *head, const char *word);

/* Remove uma palavra da lista. */
int dlist_remove(DList *head, const char *word);

/* Busca uma palavra na lista. */
int dlist_search(DList head, const char *word);

/* Lista as palavras do início para o fim. */
void dlist_print_forward(DList head);

/* Lista as palavras do fim para o início. */
void dlist_print_backward(DList head);

/* Libera toda a memória da lista. */
void dlist_clear(DList *head);

#endif
