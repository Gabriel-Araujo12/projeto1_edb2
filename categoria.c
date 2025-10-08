#include "categoria.h"

Categoria inserirCategoria(int id, char *nome, char *arquivo){
    Categoria c;
    c.id = id;
    strcpy(c.nome, nome);
    strcpy(c.arquivo, arquivo);
    c.livros = NULL;

    return c;
}