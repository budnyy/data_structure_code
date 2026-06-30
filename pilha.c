#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

Pilha* pilha_criar(int capacidade) {
    Pilha *p = malloc(sizeof(Pilha));
    p->dados = malloc(capacidade * sizeof(int));
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}

void pilha_destruir(Pilha *p) {
    free(p->dados);
    free(p);
}

bool pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

bool pilha_cheia(Pilha *p) {
    return p->topo == p->capacidade - 1;
}

int pilha_tamanho(Pilha *p) {
    return p->topo + 1;
}

bool pilha_empilhar(Pilha *p, int valor) {
    if (pilha_cheia(p)) {
        int nova_cap = p->capacidade * 2;
        int *novo = realloc(p->dados, nova_cap * sizeof(int));
        if (!novo) return false;
        p->dados = novo;
        p->capacidade = nova_cap;
    }
    p->dados[++p->topo] = valor;
    return true;
}

bool pilha_topo(Pilha *p, int *valor) {
    if (pilha_vazia(p)) return false;
    *valor = p->dados[p->topo];
    return true;
}

bool pilha_desempilhar(Pilha *p, int *valor) {
    if (pilha_vazia(p)) return false;
    *valor = p->dados[p->topo--];
    return true;
}

void pilha_exibir(Pilha *p) {
    printf("[");
    for (int i = 0; i <= p->topo; i++) {
        printf("%d", p->dados[i]);
        if (i < p->topo) printf(", ");
    }
    printf("] (topo=%d, tamanho=%d, cap=%d)\n",
           pilha_vazia(p) ? -1 : p->dados[p->topo],
           pilha_tamanho(p), p->capacidade);
}

int main() {
    Pilha *p = pilha_criar(2);
    int v;

    pilha_empilhar(p, 10);
    pilha_empilhar(p, 20);
    pilha_empilhar(p, 30);        // redimensiona
    pilha_exibir(p);

    pilha_topo(p, &v);
    printf("Topo: %d\n", v);

    pilha_desempilhar(p, &v);
    printf("Desempilhou: %d\n", v);
    pilha_exibir(p);

    printf("Vazia: %s\n", pilha_vazia(p) ? "sim" : "nao");
    printf("Tamanho: %d\n", pilha_tamanho(p));

    pilha_desempilhar(p, &v);
    pilha_desempilhar(p, &v);
    if (!pilha_desempilhar(p, &v))
        printf("Erro ao desempilhar (vazia)\n");

    pilha_destruir(p);
    return 0;
}
