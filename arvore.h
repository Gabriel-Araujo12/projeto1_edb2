#ifndef ARVORE_H
#define ARVORE_H

#include "categoria.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    Categoria c;
    struct No *esq, *dir;
} No;

No* novoNo(Categoria c);
No* inserir(No* r, Categoria c);
No* buscar(No* r, int id);
void emOrdem(No* r);
No* maiorNo(No* r);
No* remover(No* r, int id);
void liberarArvore(No* r);

#endif