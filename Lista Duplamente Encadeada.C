#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do Nó da lista
typedef struct No {
    int valor;
    struct No* proximo;
    struct No* anterior;
} No;

// Definição da estrutura do Descritor da lista
typedef struct Descritor {
    int qtde;
    No* primeiro;
    No* ultimo;
} Descritor;

// Função para criar o Descritor da lista
Descritor* criarLista() {
    Descritor* descritor = (Descritor*)malloc(sizeof(Descritor));
    descritor->qtde = 0;
    descritor->primeiro = NULL;
    descritor->ultimo = NULL;
    return descritor;
}

// Função para inserir um elemento no início da lista
void inserir_no_inicio(Descritor* descritor, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->proximo = descritor->primeiro;
    novoNo->anterior = NULL;

    if (descritor->primeiro != NULL) {
        descritor->primeiro->anterior = novoNo;
    } else {
        // Se a lista estiver vazia, o novo nó será o último também
        descritor->ultimo = novoNo;
    }

    descritor->primeiro = novoNo;
    descritor->qtde++;
}

// Função para inserir um elemento no fim da lista
void inserir_no_fim(Descritor* descritor, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->proximo = NULL;
    novoNo->anterior = descritor->ultimo;

    if (descritor->ultimo != NULL) {
        descritor->ultimo->proximo = novoNo;
    } else {
        // Se a lista estiver vazia, o novo nó será o primeiro também
        descritor->primeiro = novoNo;
    }

    descritor->ultimo = novoNo;
    descritor->qtde++;
}

// Função para excluir o primeiro elemento da lista
void excluir_do_inicio(Descritor* descritor) {
    if (descritor->primeiro == NULL) {
        printf("Lista vazia, impossível excluir.\n");
        return;
    }

    No* primeiroNo = descritor->primeiro;
    descritor->primeiro = primeiroNo->proximo;

    if (descritor->primeiro != NULL) {
        descritor->primeiro->anterior = NULL;
    } else {
        // Se não há mais elementos, o último também é NULL
        descritor->ultimo = NULL;
    }

    free(primeiroNo);
    descritor->qtde--;
}

// Função para excluir o último elemento da lista
void excluir_do_fim(Descritor* descritor) {
    if (descritor->ultimo == NULL) {
        printf("Lista vazia, impossível excluir.\n");
        return;
    }

    No* ultimoNo = descritor->ultimo;
    descritor->ultimo = ultimoNo->anterior;

    if (descritor->ultimo != NULL) {
        descritor->ultimo->proximo = NULL;
    } else {
        // Se não há mais elementos, o primeiro também é NULL
        descritor->primeiro = NULL;
    }

    free(ultimoNo);
    descritor->qtde--;
}

// Função para imprimir os elementos da lista
void imprimir(Descritor* descritor) {
    No* atual = descritor->primeiro;

    printf("Lista: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para buscar um elemento na lista e retornar seu endereço (ou NULL se não encontrado)
No* buscar(Descritor* descritor, int valor) {
    No* atual = descritor->primeiro;

    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Função para liberar a memória alocada pela lista
void liberarLista(Descritor* descritor) {
    No* atual = descritor->primeiro;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(descritor);
}

int main() {
    Descritor* lista = criarLista();

    inserir_no_fim(lista, 10);
    inserir_no_inicio(lista, 5);
    inserir_no_fim(lista, 20);
    inserir_no_inicio(lista, 2);

    printf("Após inserção:\n");
    imprimir(lista);

    No* elemento = buscar(lista, 5);
    if (elemento != NULL) {
        printf("Elemento encontrado: %d\n", elemento->valor);
    } else {
        printf("Elemento não encontrado.\n");
    }

    excluir_do_fim(lista);
    excluir_do_inicio(lista);

    printf("Após exclusão:\n");
    imprimir(lista);

    liberarLista(lista);
    return 0;
}
