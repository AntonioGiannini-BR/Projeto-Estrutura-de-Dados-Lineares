#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/* Estrutura interna de cada nó da pilha encadeada. */
struct StackNode {
    char text[TEXT_SIZE];      /* Frase armazenada no nó. */
    struct StackNode *next;    /* Ponteiro para o próximo nó da pilha. */
};

/* Verifica se a pilha está vazia. */
int stack_is_empty(Stack top) {
    return top == NULL;
}

/* Insere uma nova frase no topo da pilha. */
int stack_push(Stack *top, const char *text) {
    /* Aloca memória para o novo nó. */
    struct StackNode *new_node = (struct StackNode *) malloc(sizeof(struct StackNode));
    if (new_node == NULL) {
        return 0; /* Falha de alocação. */
    }

    /* Copia a frase com segurança, evitando overflow. */
    strncpy(new_node->text, text, TEXT_SIZE - 1);
    new_node->text[TEXT_SIZE - 1] = '\0';

    /* Novo nó aponta para o antigo topo. */
    new_node->next = *top;

    /* Atualiza o topo da pilha na função chamadora. */
    *top = new_node;
    return 1;
}

/* Remove o elemento do topo da pilha. */
int stack_pop(Stack *top, char *out_text) {
    struct StackNode *temp;

    /* Não há como remover de pilha vazia. */
    if (stack_is_empty(*top)) {
        return 0;
    }

    /* Guarda o nó que será removido. */
    temp = *top;

    /* Se o chamador quiser, devolve o texto removido. */
    if (out_text != NULL) {
        strcpy(out_text, temp->text);
    }

    /* Avança o topo para o próximo nó. */
    *top = temp->next;

    /* Libera a memória do nó removido. */
    free(temp);
    return 1;
}

/* Mostra todo o conteúdo atual do editor. */
void stack_print(Stack top) {
    int i = 1;
    struct StackNode *current = top;

    if (stack_is_empty(top)) {
        printf("Editor vazio.\n");
        return;
    }

    printf("\n--- Conteudo atual do editor (topo para base) ---\n");
    while (current != NULL) {
        printf("%d. %s\n", i, current->text);
        current = current->next;
        i++;
    }
}

/* Remove todos os nós até a pilha ficar vazia. */
void stack_clear(Stack *top) {
    char buffer[TEXT_SIZE];

    /* Reutiliza stack_pop para liberar nó por nó. */
    while (stack_pop(top, buffer)) {
    }
}
