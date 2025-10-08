#include "arvore.h"

No* novoNo(Categoria c){
    No* n = (No*) malloc(sizeof(No));

    if(!n){ 
        perror("malloc"); exit(EXIT_FAILURE); 
    }

    n->valor = c;
    n->esq = n->dir = NULL;
    return n;
}

No* inserir(No* r, Categoria c){
    if(r == NULL){
        return novoNo(c);
    }
    if(c < r->valor){
        r->esq = inserir(r->esq, c);
    }
    else if(c > r->valor){
        r->dir = inserir(r->dir, c);
    }

    return r;
}

No* buscar(No* r, int id){
    if(r == NULL || r->valor == id){
        return r;
    }

    return (id < r->valor) ? buscar(r->esq, id) : buscar(r->dir, id);
}

void emOrdem(No* r){
    if(r == NULL){
        return;
    }

    emOrdem(r->esq);
    printf("%d ", r->valor);
    emOrdem(r->dir);
}

No* remover(No* r, int id){
    if(r == NULL){
        return NULL;
    }

    if(id < r->valor){
        r->esq = remover(r->esq, id);
    } 
    else if(id > r->valor){
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
            r->valor = pred->valor;
            r->esq = remover(r->esq, pred->valor);
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