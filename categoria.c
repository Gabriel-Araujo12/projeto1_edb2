#include "categoria.h"

Categoria criarCategoria(int id, char *nome, char *arquivo){
    Categoria c;
    c.id = id;
    strcpy(c.nome, nome);
    strcpy(c.arquivo, arquivo);
    c.livros = NULL;

    return c;
}

void exibirCategoria(Categoria c){
    printf("ID: %d | Nome: %s\n", c.id, c.nome);
}