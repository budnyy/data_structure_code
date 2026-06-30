#include <stdio.h>
struct Aluno {
    char nome[20];
    int idade;
};

int main() {
    struct Aluno a = {"Anna", 20};
    printf("%s %d\n", a.nome, a.idade);
    return 0;
}