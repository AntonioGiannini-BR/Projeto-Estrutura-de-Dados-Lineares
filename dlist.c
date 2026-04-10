#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

/* Estrutura de cada nó da lista duplamente encadeada. */
struct DNode {
    char word[TEXT_SIZE];   /* Palavra armazenada. */
    struct DNode *prev;     /* Ponteiro para o nó anterior. */
    struct DNode *next;     /* Ponteiro para o próximo nó. */
};

/* Verifica se a lista está vazia. */
int dlist_is_empty(DList head) {
    return head == NULL;
}

/* Insere uma nova palavra na posição correta, mantendo ordem alfabética. */
int dlist_insert_sorted(DList *head, const char *word) {
    struct DNode *new_node = (struct DNode *) malloc(sizeof(struct DNode));
    struct DNode *current;

    if (new_node == NULL) {
        return 0;
    }

    /* Copia a palavra para o novo nó. */
    strncpy(new_node->word, word, TEXT_SIZE - 1);
    new_node->word[TEXT_SIZE - 1] = '\0';
    new_node->prev = NULL;
    new_node->next = NULL;

    /* Caso 1: inserir no início da lista. */
    if (*head == NULL || strcmp(word, (*head)->word) <= 0) {
        new_node->next = *head;
        if (*head != NULL) {
            (*head)->prev = new_node;
        }
        *head = new_node;
        return 1;
    }

    /* Procura a posição correta de inserção. */
    current = *head;
    while (current->next != NULL && strcmp(word, current->next->word) > 0) {
        current = current->next;
    }

    /* Liga o novo nó entre current e current->next. */
    new_node->next = current->next;
    new_node->prev = current;

    if (current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
    return 1;
}

/* Remove uma palavra da lista, se existir. */
int dlist_remove(DList *head, const char *word) {
    struct DNode *current;

    if (*head == NULL) {
        return 0;
    }

    /* Busca o nó que contém a palavra. */
    current = *head;
    while (current != NULL && strcmp(current->word, word) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        return 0;
    }

    /* Ajusta o nó anterior ou atualiza a cabeça da lista. */
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    /* Ajusta o nó seguinte, se existir. */
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    /* Libera o nó removido. */
    free(current);
    return 1;
}

/* Procura uma palavra na lista. */
int dlist_search(DList head, const char *word) {
    struct DNode *current = head;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/* Exibe as palavras do início para o fim. */
void dlist_print_forward(DList head) {
    struct DNode *current = head;

    if (head == NULL) {
        printf("Dicionario vazio.\n");
        return;
    }

    printf("\n--- Dicionario (inicio -> fim) ---\n");
    while (current != NULL) {
        printf("- %s\n", current->word);
        current = current->next;
    }
}

/* Exibe as palavras do fim para o início. */
void dlist_print_backward(DList head) {
    struct DNode *current = head;

    if (head == NULL) {
        printf("Dicionario vazio.\n");
        return;
    }

    /* Vai até o último nó da lista. */
    while (current->next != NULL) {
        current = current->next;
    }

    printf("\n--- Dicionario (fim -> inicio) ---\n");
    while (current != NULL) {
        printf("- %s\n", current->word);
        current = current->prev;
    }
}

/* Libera todos os nós da lista. */
void dlist_clear(DList *head) {
    /* Remove sempre o primeiro nó até esvaziar a lista. */
    while (*head != NULL) {
        dlist_remove(head, (*head)->word);
    }
}
