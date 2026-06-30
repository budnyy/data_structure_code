#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

int main() {
    No *n = malloc(sizeof(No));
    n->valor = 10;
    n->prox = n;
    
    printf("%d\n", n->prox->valor);
    free(n);
    return 0;
}