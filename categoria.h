#ifndef CATEGORIA_H
#define CATEGORIA_H

#include "heap.h"

#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char nome[100];
    char arquivo[100];
    Heap *livros;
} Categoria;

Categoria inserirCategoria(int id, char *nome, char *arquivo);

#endif