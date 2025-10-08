#include "heap.h"

static void troca(Livro *a, Livro *b) {
    Livro temp = *a;
    *a = *b;
    *b = temp;
}

Heap* criarHeap(int capacidade){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->tamanho = 0;
    h->capacidade = capacidade;
    h->l = (int*)malloc(capacidade * sizeof(int));

    return h;
}

void maxHeapify(Heap *h, int i){
    int maior = i;
    int e = 2 * i;
    int d = 2 * i + 1;

    if(e <= h->tamanho && h->l[e] > h->l[maior]){
        maior = e;
    }
    if(d <= h->tamanho && h->l[d] > h->l[maior]){
        maior = d;
    }
    if(m != i){
        troca(&h->l[i], &h->l[maior]);
        maxHeapify(h, maior);
    }
}

void construirHeap(Heap *h){
    int n = h->tamanho;

    for(int i = n / 2; i <= 1; i--){
        maxHeapify(h, i);
    }
}

Livro buscarRaiz(Heap *h){
    if(h->size <= 0){
        printf("Não há nenhum livro para exibir!");

        return;
    }
    
    return h->l[0];
}

void buscarN(Heap* h, int n){
    if(n > h->tamanho){
        printf("O valor escolhido é maior do que a quantidade existente, logo, todos serão exibidos!");
        n = h->tamanho;
    }

    printf("------------Top %d livros mais vendidos------------", n);
    for(int i = 0; i < n; i++){
        printf("%dº ", i + 1);
        exibirLivro(h->l[i]);
        printf("\n");
    }
}

void liberarHeap(Heap *h){
    free(h->l);
    free(h);
}