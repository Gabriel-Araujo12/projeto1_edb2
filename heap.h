#ifndef HEAP_H
#define HEAP_H

#include "livro.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Livro *l; 
    int tamanho;
    int capacidade;
} Heap;

Heap* criarHeap(int capacidade);
void inserirLivro(Heap* heap, Livro l);
Livro buscarRaiz(Heap *h);
void buscarN(Heap* h, int n);
void atualizarVendas(Heap *h, int isbn, int qntdVendida);
void liberarHeap(Heap *h);

#endif