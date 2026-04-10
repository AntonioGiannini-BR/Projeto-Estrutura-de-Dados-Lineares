PROJETO FINAL

Alunos: Antonio Giannini e Lucas Henrique  
Disciplina: Estrutura de Dados  
Professora: Monique Soares  

--------------------------------------------------

DESCRIÇÃO DO PROJETO:

Este projeto implementa um sistema de gerenciamento de textos utilizando
estruturas de dados fundamentais:

- Pilha encadeada (Stack)
- Fila circular com vetor dinâmico (Queue)
- Lista duplamente encadeada ordenada (DList)

O objetivo é demonstrar o uso correto dessas estruturas,
incluindo alocação dinâmica de memória e modularização.

--------------------------------------------------

FUNCIONALIDADES DO SISTEMA:

1 - Adicionar texto (Pilha)  
    Insere um texto no topo da pilha  

2 - Undo  
    Remove o último texto inserido (pop)  

3 - Inserir na fila (Enqueue)  
    Adiciona elemento na fila circular dinâmica  

4 - Remover da fila (Dequeue)  
    Remove o elemento mais antigo da fila  

5 - Inserir palavra no dicionário  
    Insere palavra em ordem alfabética  

6 - Listar palavras  
    Mostra todas as palavras da lista  

0 - Sair  
    Libera toda memória alocada  

--------------------------------------------------

ESTRUTURAS UTILIZADAS:

PILHA (STACK):  
- Implementada com lista encadeada  
- Uso de ponteiro para ponteiro ()  
- Operações: push, pop, clear  

FILA (QUEUE):  
- Implementada com vetor dinâmico  
- Estrutura circular  
- Redimensionamento automático com realloc  
- Controle de front, rear, size e capacity  

LISTA DUPLAMENTE ENCADEADA (DLIST):  
- Cada nó possui prev e next  
- Inserção ordenada  
- Percurso sequencial  

--------------------------------------------------

ORGANIZAÇÃO DO PROJETO:

- main.c        -> Menu e controle do sistema  
- stack.c/h     -> Pilha  
- queue.c/h     -> Fila dinâmica  
- dlist.c/h     -> Lista duplamente encadeada  
- Makefile      -> Compilação  

--------------------------------------------------

COMPILAÇÃO:

Linux/Mac:  
gcc main.c stack.c queue.c dlist.c -o textmanager  

Windows:  
gcc main.c stack.c queue.c dlist.c -o textmanager.exe  

--------------------------------------------------

EXECUÇÃO:

Linux/Mac:  
./textmanager  

Windows:  
textmanager.exe  

--------------------------------------------------

OBSERVAÇÕES IMPORTANTES:

- Uso correto de malloc, realloc e free  
- Modularização com arquivos .h e .c  
- Uso de ponteiros para ponteiros ()  
- Estruturas implementadas conforme solicitado  
- Liberação de memória ao final do programa  

--------------------------------------------------

PROJETO FINALIZADO E PRONTO PARA ENTREGA
