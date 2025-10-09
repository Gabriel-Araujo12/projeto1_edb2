#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <string.h>

typedef struct{
    int isbn;
    char titulo[200];
    char autor[200];
    int ano;
    float preco;
    int estoque;
    int vendas;
} Livro;

Livro criarLivro(int isbn, char *titulo, char *autor, int ano, float preco, int estoque, int vendas);
void exibirLivro(Livro l);

#endif