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

No* inserir(No* r, Categoria c){
    if(r == NULL){
        return novoNo(c);
    }
    if(c.id < r->c.id){
        r->esq = inserir(r->esq, c);
    }
    else if(c.id > r->c.id){
        r->dir = inserir(r->dir, c);
    }

    return r;
}

No* buscar(No* r, int id){
    if(r == NULL || r->c.id == id){
        return r;
    }

    return (id < r->c.id) ? buscar(r->esq, id) : buscar(r->dir, id);
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

No* remover(No* r, int id){
    if(r == NULL){
        return NULL;
    }

    if(id < r->c.id){
        r->esq = remover(r->esq, id);
    } 
    else if(id > r->c.id){
        r->dir = remover(r->dir, id);
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
            r->esq = remover(r->esq, pred->c.id);
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
    free(r);
}