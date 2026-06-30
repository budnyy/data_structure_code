#include <stdio.h>
#include <stdlib.h>


typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

typedef struct {
    No *raiz;
} Arvore;

Arvore* arvore_criar() {
    Arvore *a = malloc(sizeof(Arvore));
    a->raiz = NULL;
    return a;
}

static No* criar_no(int valor) {
    No *novo = malloc(sizeof(No));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int arvore_inserir(Arvore *a, int valor) {
    No *novo = criar_no(valor);
    if (!novo) return 0;
    if (!a->raiz) {
        a->raiz = novo;
        return 1;
    }
    No *atual = a->raiz;
    while (1) {
        if (valor < atual->dado) {
            if (!atual->esq) { atual->esq = novo; return 1; }
            atual = atual->esq;
        } else if (valor > atual->dado) {
            if (!atual->dir) { atual->dir = novo; return 1; }
            atual = atual->dir;
        } else {
            free(novo);
            return 0;
        }
    }
}

int arvore_buscar(Arvore *a, int valor) {
    No *atual = a->raiz;
    while (atual) {
        if (valor == atual->dado) return 1;
        atual = (valor < atual->dado) ? atual->esq : atual->dir;
    }
    return 0;
}

static void destruir_no(No *no) {
    if (!no) return;
    destruir_no(no->esq);
    destruir_no(no->dir);
    free(no);
}

void arvore_destruir(Arvore *a) {
    destruir_no(a->raiz);
    free(a);
}

static void em_ordem_no(No *no) {
    if (!no) return;
    em_ordem_no(no->esq);
    printf("%d ", no->dado);
    em_ordem_no(no->dir);
}

void arvore_em_ordem(Arvore *a) {
    printf("Em-ordem: ");
    em_ordem_no(a->raiz);
    printf("\n");
}

static void pre_ordem_no(No *no) {
    if (!no) return;
    printf("%d ", no->dado);
    pre_ordem_no(no->esq);
    pre_ordem_no(no->dir);
}

void arvore_pre_ordem(Arvore *a) {
    printf("Pre-ordem: ");
    pre_ordem_no(a->raiz);
    printf("\n");
}

static void pos_ordem_no(No *no) {
    if (!no) return;
    pos_ordem_no(no->esq);
    pos_ordem_no(no->dir);
    printf("%d ", no->dado);
}

void arvore_pos_ordem(Arvore *a) {
    printf("Pos-ordem: ");
    pos_ordem_no(a->raiz);
    printf("\n");
}

static int altura_no(No *no) {
    if (!no) return -1;
    int ae = altura_no(no->esq);
    int ad = altura_no(no->dir);
    return 1 + (ae > ad ? ae : ad);
}

int arvore_altura(Arvore *a) {
    return altura_no(a->raiz);
}

int arvore_minimo(Arvore *a, int *valor) {
    if (!a->raiz) return 0;
    No *atual = a->raiz;
    while (atual->esq) atual = atual->esq;
    *valor = atual->dado;
    return 1;
}

int arvore_maximo(Arvore *a, int *valor) {
    if (!a->raiz) return 0;
    No *atual = a->raiz;
    while (atual->dir) atual = atual->dir;
    *valor = atual->dado;
    return 1;
}

int arvore_vazia(Arvore *a) {
    return a->raiz == NULL;
}

int main() {
    Arvore *a = arvore_criar();
    int v;

    arvore_inserir(a, 50);
    arvore_inserir(a, 30);
    arvore_inserir(a, 70);
    arvore_inserir(a, 20);
    arvore_inserir(a, 40);

    arvore_em_ordem(a);
    arvore_pre_ordem(a);
    arvore_pos_ordem(a);

    printf("Altura: %d\n", arvore_altura(a));

    arvore_minimo(a, &v);
    printf("Menor: %d\n", v);
    arvore_maximo(a, &v);
    printf("Maior: %d\n", v);

    printf("40 %s\n", arvore_buscar(a, 40) ? "encontrado" : "ausente");
    printf("55 %s\n", arvore_buscar(a, 55) ? "encontrado" : "ausente");

    printf("Vazia: %s\n", arvore_vazia(a) ? "sim" : "nao");

    arvore_destruir(a);
    return 0;
}
