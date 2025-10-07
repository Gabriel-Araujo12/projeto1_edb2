#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

No* novoNo(int v);
No* inserir(No* r, int v);
No* buscar(No* r, int v);
void emOrdem(No* r);
No* remover(No* r, int v);
void liberarArvore(No* r);

#endif