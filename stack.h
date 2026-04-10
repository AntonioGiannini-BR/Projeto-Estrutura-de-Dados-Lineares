#ifndef STACK_H
#define STACK_H

/* Tamanho máximo de texto armazenado nas estruturas do projeto. */
#define TEXT_SIZE 256

/* 
 * Stack é um ponteiro para o nó do topo da pilha.
 * A definição completa do nó fica escondida em stack.c
 * para manter encapsulamento.
 */
typedef struct StackNode* Stack;

/* Retorna 1 se a pilha estiver vazia e 0 caso contrário. */
int stack_is_empty(Stack top);

/* 
 * Insere uma nova frase no topo da pilha.
 * Usa Stack * porque a função altera o topo na main.
 * Retorna 1 em caso de sucesso e 0 em falha de memória.
 */
int stack_push(Stack *top, const char *text);

/* 
 * Remove a frase do topo da pilha.
 * Se out_text não for NULL, copia a frase removida para esse buffer.
 * Retorna 1 se removeu com sucesso e 0 se a pilha estiver vazia.
 */
int stack_pop(Stack *top, char *out_text);

/* Exibe todo o conteúdo da pilha do topo para a base. */
void stack_print(Stack top);

/* Libera toda a memória alocada pela pilha. */
void stack_clear(Stack *top);

#endif
