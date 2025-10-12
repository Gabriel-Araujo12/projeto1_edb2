#include "arvore.h"

No* novoNo(Categoria c){
    No* n = (No*) malloc(sizeof(No));

    if(!n){ 
        perror("malloc"); exit(EXIT_FAILURE); 
    }

    n->c = c;
    n->esq = n->dir = NULL;
    return n;
}

No* inserirCategoria(No* r, Categoria c){
    if(r == NULL){
        return novoNo(c);
    }

    if(strcmp(c.nome, r->c.nome) < 0){
        r->esq = inserirCategoria(r->esq, c);
    }
    else if(strcmp(c.nome, r->c.nome) > 0){
        r->dir = inserirCategoria(r->dir, c);
    }

    return r;
}

No* carregarCategoria(const char* arquivo){
    FILE* arquivoCategoria = fopen(arquivo, "r");

    if(arquivoCategoria == NULL){
        printf("\n---> Não foi possível abrir o arquivo!\n\n");

        return NULL;
    }

    No* raiz = NULL;
    char linha[256];
    fgets(linha, sizeof(linha), arquivoCategoria);

    while(fgets(linha, sizeof(linha), arquivoCategoria)){
        int id;
        char nome[100], arquivoLivro[100];

        if(sscanf(linha, "%d;%99[^;];%99[^\n]", &id, nome, arquivoLivro) == 3){
            Categoria c = criarCategoria(id, nome, arquivoLivro);
            raiz = inserirCategoria(raiz, c);
        }
    }

    fclose(arquivoCategoria);
    
    return raiz;
}

No* buscar(No* r, const char* nome){
    if(r == NULL){
        return NULL;
    }

    if(strcmp(nome, r->c.nome) == 0){
        return r;
    } 
    else if(strcmp(nome, r->c.nome) < 0){
        return buscar(r->esq, nome);
    } 
    else{
        return buscar(r->dir, nome);
    }
}

void emOrdem(No* r){
    if(r == NULL){
        return;
    }

    emOrdem(r->esq);
    exibirCategoria(r->c); 
    emOrdem(r->dir);
}

No* maiorNo(No* r){
    No* atual = r;
    while (atual && atual->dir) atual = atual->dir;
    return atual;
}

No* remover(No* r, const char* nome){
    if(r == NULL){
        return NULL;
    }

    if(strcmp(nome, r->c.nome) < 0){
        r->esq = remover(r->esq, nome);
    } 
    else if(strcmp(nome, r->c.nome) > 0){
        r->dir = remover(r->dir, nome);
    } 
    else{
        if(r->esq == NULL && r->dir == NULL){
            free(r);
            return NULL;
        } 
        else if(r->esq == NULL){
            No* tmp = r->dir;
            free(r);
            return tmp;
        } 
        else if(r->dir == NULL){
            No* tmp = r->esq;
            free(r);
            return tmp;
        } 
        else{
            No* pred = maiorNo(r->esq);
            r->c = pred->c;
            r->esq = remover(r->esq, pred->c.nome);
        }
    }

    return r;
}

void liberarArvore(No* r){
    if(!r){
        return;
    }

    liberarArvore(r->esq);
    liberarArvore(r->dir);

    if(r->c.livros != NULL){
        liberarHeap(r->c.livros);
    }

    free(r);
}