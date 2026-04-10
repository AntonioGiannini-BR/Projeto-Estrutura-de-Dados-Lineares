#include <stdio.h>
#include <string.h>

#include "stack.c"
#include "stack.h"
#include "queue.c"
#include "queue.h"
#include "dlist.c"
#include "dlist.h"

void clear_screen() {
    system("cls");
}

void wait_enter() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/* 
 * Lê uma linha inteira do teclado e remove o '\n' final,
 * se ele existir.
 */ 
static void read_line(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/* Submenu responsável pelas operações do dicionário. */
static void dictionary_menu(DList *dict) {
    int option;
    char word[TEXT_SIZE];

    do {
        clear_screen();

        printf("\n===== DICIONARIO =====\n");
        printf("1. Inserir palavra\n");
        printf("2. Remover palavra\n");
        printf("3. Buscar palavra\n");
        printf("4. Listar do inicio para o fim\n");
        printf("5. Listar do fim para o inicio\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &option);
        getchar(); /* Consome o enter deixado pelo scanf. */

        clear_screen();

        switch (option) {
            case 1:
                printf("Digite a palavra: ");
                read_line(word, TEXT_SIZE);
                if (dlist_insert_sorted(dict, word)) {
                    printf("Palavra inserida com sucesso.\n");
                } else {
                    printf("Erro ao inserir palavra.\n");
                }
                break;

            case 2:
                printf("Digite a palavra para remover: ");
                read_line(word, TEXT_SIZE);
                if (dlist_remove(dict, word)) {
                    printf("Palavra removida com sucesso.\n");
                } else {
                    printf("Palavra nao encontrada.\n");
                }
                break;

            case 3:
                printf("Digite a palavra para buscar: ");
                read_line(word, TEXT_SIZE);
                if (dlist_search(*dict, word)) {
                    printf("A palavra existe no dicionario.\n");
                } else {
                    printf("A palavra nao existe no dicionario.\n");
                }
                break;

            case 4:
                dlist_print_forward(*dict);
                break;

            case 5:
                dlist_print_backward(*dict);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

        if (option != 0) {
            wait_enter();
        }

    } while (option != 0);
}

int main(void) {
    /* Pilha do editor: guarda frases inseridas e suporta Undo. */
    Stack editor = NULL;

    /* Lista dupla do dicionário, inicialmente vazia. */
    DList dictionary = NULL;

    /* Fila circular usada como buffer de salvamento. */
    Queue save_buffer;
    char text[TEXT_SIZE];
    int option;

    /* Inicializa a fila antes de exibir o menu principal. */
    if (!queue_init(&save_buffer, 4)) {
        printf("Erro ao inicializar fila de salvamento.\n");
        return 1;
    }

    do {
        clear_screen(); //Limpa os MENUS anteriores em tempo de execução.

        printf("\n===== TEXTMANAGER =====\n");
        printf("1. Inserir frase (Push na Pilha)\n");
        printf("2. Desfazer ultima frase (Pop na Pilha)\n");
        printf("3. Enviar para salvamento (Pop da Pilha -> Enqueue na Fila)\n");
        printf("4. Processar salvamento (Dequeue da Fila)\n");
        printf("5. Mostrar editor\n");
        printf("6. Mostrar fila de salvamento\n");
        printf("7. Gerenciar dicionario\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &option);
        getchar(); /* Remove o enter do buffer. */

        printf("\n");

        switch (option) {
            case 1:
                /* Insere uma nova frase no topo da pilha do editor. */
                printf("Digite a frase: ");
                read_line(text, TEXT_SIZE);
                if (stack_push(&editor, text)) {
                    printf("Frase adicionada ao editor.\n");
                } else {
                    printf("Erro de memoria ao inserir frase.\n");
                }
                break;

            case 2:
                /* Desfaz a última frase digitada. */
                if (stack_pop(&editor, text)) {
                    printf("Undo realizado. Frase removida: %s\n", text);
                } else {
                    printf("Nao ha frases para desfazer.\n");
                }
                break;

            case 3:
                /* 
                * Remove do editor e envia para a fila de salvamento.
                * Se o enqueue falhar, devolve a frase para a pilha.
                */
                if (stack_pop(&editor, text)) {
                    if (queue_enqueue(&save_buffer, text)) {
                        printf("Frase enviada para o buffer de salvamento.\n");
                    } else {
                        printf("Erro ao enviar para a fila.\n");
                        stack_push(&editor, text);
                    }
            } else {
                printf("Editor vazio. Nada para salvar.\n");
            }
            break;

            case 4:
                /* Processa o salvamento removendo o primeiro da fila. */
                if (queue_dequeue(&save_buffer, text)) {
                    printf("Processando salvamento no disco: %s\n", text);
                } else {
                    printf("Fila de salvamento vazia.\n");
                }
                break;

            case 5:
                /* Exibe o conteúdo atual da pilha do editor. */
                stack_print(editor);
                break;

            case 6:
                /* Exibe o estado atual da fila circular. */
                queue_print(&save_buffer);
                break;

            case 7:
                /* Abre o submenu do dicionário. */
                dictionary_menu(&dictionary);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

        if (option != 0) {
            wait_enter();
        }

    } while (option != 0);

    /* Libera toda a memória usada pelas três estruturas. */
    stack_clear(&editor);
    dlist_clear(&dictionary);
    queue_destroy(&save_buffer);

    clear_screen(); // Limpa terminal e finaliza código.
    printf("Memoria liberada. Programa encerrado.\n");

    return 0;
}
