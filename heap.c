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
    h->l = (Livro*)malloc(capacidade * sizeof(Livro));

    return h;
}

void maxHeapify(Livro* a, int n, int i){
    int maior = i;
    int e = 2 * i + 1;
    int d = 2 * i + 2;

    if(e < n && a[e].vendas > a[maior].vendas){
        maior = e;
    }
    if(d < n && a[d].vendas > a[maior].vendas){
        maior = d;
    }
    if(maior != i){
        troca(&a[i], &a[maior]);
        maxHeapify(a, n, maior);
    }
}

void construirHeap(Livro* a, int n){
    for(int i = (n / 2) - 1; i >= 0; i--){
        maxHeapify(a, n, i);
    }
}

void heapSort(Livro* a, int n){
    construirHeap(a, n);

    for(int i = n - 1; i > 0; i--){
        troca(&a[0], &a[i]);
        maxHeapify(a, i, 0);
    }
}

void inserirLivro(Heap* h, Livro l){
    if(h->tamanho == h->capacidade){
        printf("\n---> Não é possível adicionar mais livros devido ao espaço!\n\n");

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
        printf("\n---> Não há nenhum livro para exibir!\n\n");

        return vazio;
    }
    
    return h->l[0];
}

void buscarN(Heap* h, int n){
    if(n > h->tamanho){
        printf("\n---> O valor escolhido é maior do que a quantidade existente, logo, todos serão exibidos!\n");

        n = h->tamanho;
    }

    if(n <= 0){
        printf("\n---> O valor escolhido é inválido!\n\n");

        return;
    }

    Livro *copia = malloc(h->tamanho * sizeof(Livro));
    memcpy(copia, h->l, h->tamanho * sizeof(Livro));

    heapSort(copia, h->tamanho);

    printf("\n----------------- Top %d Livro Mais Vendido -----------------\n\n", n);
    for(int i = 0; i < n; i++){
        int indice = h->tamanho - 1 - i;
        printf("%dº ", i + 1);
        exibirLivro(copia[indice]);
    }
    printf("\n------------------------------------------------------------\n\n");

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
        printf("\n---> ISBN indicado não foi encontrado entre os livros listados!\n\n");

        return;
    }

    if(h->l[i].estoque < qntdVendida){
        printf("\n---> A quantidade vendida supera o número de livros disponíveis!\n\n");

        return;
    }

    h->l[i].estoque -= qntdVendida;
    h->l[i].vendas += qntdVendida;

    printf("\n---> A venda foi registrada!\n\n");

    while(i != 0 && h->l[(i - 1) / 2].vendas < h->l[i].vendas){
        troca(&h->l[i], &h->l[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void liberarHeap(Heap *h){
    free(h->l);
    free(h);
}