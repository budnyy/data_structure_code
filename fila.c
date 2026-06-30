#include <stdio.h>
#include <stdlib.h>


typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct {
    No *frente;
    No *tras;
    int tamanho;
} Fila;

Fila* fila_criar() {
    Fila *f = malloc(sizeof(Fila));
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
    return f;
}

void fila_destruir(Fila *f) {
    while (f->frente) {
        No *aux = f->frente;
        f->frente = f->frente->prox;
        free(aux);
    }
    free(f);
}

int fila_vazia(Fila *f) {
    return f->frente == NULL;
}

int fila_tamanho(Fila *f) {
    return f->tamanho;
}

int fila_enfileirar(Fila *f, int valor) {
    No *novo = malloc(sizeof(No));
    if (!novo) return 0;
    novo->dado = valor;
    novo->prox = NULL;
    if (f->tras)
        f->tras->prox = novo;
    else
        f->frente = novo;
    f->tras = novo;
    f->tamanho++;
    return 1;
}

int fila_frente(Fila *f, int *valor) {
    if (fila_vazia(f)) return 0;
    *valor = f->frente->dado;
    return 1;
}

int fila_desenfileirar(Fila *f, int *valor) {
    if (fila_vazia(f)) return 0;
    No *remover = f->frente;
    *valor = remover->dado;
    f->frente = remover->prox;
    if (!f->frente) f->tras = NULL;
    free(remover);
    f->tamanho--;
    return 1;
}

void fila_exibir(Fila *f) {
    printf("[");
    No *atual = f->frente;
    while (atual) {
        printf("%d", atual->dado);
        if (atual->prox) printf(", ");
        atual = atual->prox;
    }
    printf("] (frente=%d, tamanho=%d)\n",
           fila_vazia(f) ? -1 : f->frente->dado,
           f->tamanho);
}

int main() {
    Fila *f = fila_criar();
    int v;

    fila_enfileirar(f, 10);
    fila_enfileirar(f, 20);
    fila_enfileirar(f, 30);
    fila_exibir(f);

    fila_frente(f, &v);
    printf("Frente: %d\n", v);

    fila_desenfileirar(f, &v);
    printf("Desenfileirou: %d\n", v);
    fila_exibir(f);

    fila_enfileirar(f, 40);
    fila_exibir(f);

    printf("Vazia: %s\n", fila_vazia(f) ? "sim" : "nao");
    printf("Tamanho: %d\n", fila_tamanho(f));

    fila_desenfileirar(f, &v);
    fila_desenfileirar(f, &v);
    fila_desenfileirar(f, &v);
    if (!fila_desenfileirar(f, &v))
        printf("Erro ao desenfileirar (vazia)\n");

    fila_destruir(f);
    return 0;
}
