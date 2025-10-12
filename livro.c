#include "livro.h"

Livro criarLivro(int isbn, char *titulo, char *autor, int ano, float preco, int estoque, int vendas){
    Livro l;
    l.isbn = isbn;
    strcpy(l.titulo, titulo);
    strcpy(l.autor, autor);
    l.ano = ano;
    l.preco = preco;
    l.estoque = estoque;
    l.vendas = vendas;

    return l;
}

void exibirLivro(Livro l){
    printf("ISBN: %d | Título: %s | Autor: %s | Ano: %d | Preço: R$ %.2f | Estoque: %d | Vendas: %d\n", l.isbn, l.titulo, l.autor, l.ano, l.preco, l.estoque, l.vendas);
}