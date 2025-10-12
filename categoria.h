#ifndef CATEGORIA_H
#define CATEGORIA_H

#include "livro.h"
#include "heap.h"

#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char nome[100];
    char arquivo[100];
    Heap *livros;
} Categoria;

Categoria criarCategoria(int id, char *nome, char *arquivo);
void exibirCategoria(Categoria c);
void carregarLivro(Categoria* c);

#endif