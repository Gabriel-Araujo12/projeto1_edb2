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
void maxHeapify(Heap *h, int i);
void construirHeap(Heap *h);
Livro buscarRaiz(Heap *h);
void buscarN(Heap* h, int n);
void liberarHeap(Heap *h);

#endif