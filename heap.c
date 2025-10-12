#include "heap.h"

static void troca(Livro *a, Livro *b) {
    Livro temp = *a;
    *a = *b;
    *b = temp;
}

static int compara(const void *a, const void *b) {
    const Livro *l1 = (Livro*)a;
    const Livro *l2 = (Livro*)b;
    return l2->vendas - l1->vendas;
}

Heap* criarHeap(int capacidade){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->tamanho = 0;
    h->capacidade = capacidade;
    h->l = (Livro*)malloc(capacidade * sizeof(Livro));

    return h;
}

void maxHeapify(Heap *h, int i){
    int maior = i;
    int e = 2 * i + 1;
    int d = 2 * i + 2;

    if(e < h->tamanho && h->l[e].vendas > h->l[maior].vendas){
        maior = e;
    }
    if(d < h->tamanho && h->l[d].vendas > h->l[maior].vendas){
        maior = d;
    }
    if(maior != i){
        troca(&h->l[i], &h->l[maior]);
        maxHeapify(h, maior);
    }
}

void construirHeap(Heap *h){
    int n = h->tamanho;

    for(int i = (n / 2) - 1; i >= 0; i--){
        maxHeapify(h, i);
    }
}

void inserirLivro(Heap* h, Livro l){
    if(h->tamanho == h->capacidade){
        printf("Não é possível adicionar mais livros devido ao espaço!\n");

        return;
    }

    int i = h->tamanho;
    h->l[i] = l;
    h->tamanho++;

    while(i != 0 && h->l[(i - 1) / 2].vendas < h->l[i].vendas){
        troca(&h->l[i], &h->l[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Livro buscarRaiz(Heap *h){
    Livro vazio = {0};

    if(h->tamanho <= 0){
        printf("Não há nenhum livro para exibir!");

        return vazio;
    }
    
    return h->l[0];
}

void buscarN(Heap* h, int n){
    if(n > h->tamanho){
        printf("O valor escolhido é maior do que a quantidade existente, logo, todos serão exibidos!");

        n = h->tamanho;
    }

    if(n <= 0){
        printf("O valor escolhido é inválido!");

        return;
    }

    Livro *copia = malloc(h->tamanho * sizeof(Livro));
    memcpy(copia, h->l, h->tamanho * sizeof(Livro));

    qsort(copia, h->tamanho, sizeof(Livro), compara);

    printf("------------Top %d livros mais vendidos------------", n);
    for(int i = 0; i < n; i++){
        printf("%dº ", i + 1);
        exibirLivro(copia[i]);
    }

    free(copia);
}

void atualizarVendas(Heap *h, int isbn, int qntdVendida){
    int i = -1;

    for(int j = 0; j < h->tamanho; j++){
        if(h->l[j].isbn == isbn){
            i = j;

            break;
        }
    }

    if(i == -1){
        printf("ISBN indicado não foi encontrado entre os livros listados!\n");

        return;
    }

    if(h->l[i].estoque < qntdVendida){
        printf("A quantidade vendida supera o número de livros disponíveis!\n");

        return;
    }

    h->l[i].estoque -= qntdVendida;
    h->l[i].vendas += qntdVendida;

    printf("A venda foi registrada!\n");

    while(i != 0 && h->l[(i - 1) / 2].vendas < h->l[i].vendas){
        troca(&h->l[i], &h->l[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void liberarHeap(Heap *h){
    free(h->l);
    free(h);
}