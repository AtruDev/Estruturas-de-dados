#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct no_abb {
    struct no_abb *esq;
    tp_item dado;
    struct no_abb *dir;
} tp_arvore;

tp_arvore *inicializarAbb(){return NULL;}

int vaziaAbb(tp_arvore *r){return r == NULL;}

int insereAbb(tp_arvore **r, tp_item e){
    tp_arvore *novo_no = malloc(sizeof(tp_arvore));
    if(novo_no == NULL) return 0;

    novo_no->dado = e;
    novo_no->dir = NULL; novo_no->esq = NULL;

    tp_arvore *p, *pai;

    p = *r;
    pai = NULL;

    while(p != NULL){
        pai = p;
        if(e < p->dado){
            p = p->esq;
        } else {
            p = p->dir;
        }
    }
    if(pai == NULL) {
        *r = novo_no;
    } else {
        if(e < pai->dado){
            pai->esq = novo_no;
        } else{
            pai->dir = novo_no;
        }
    }
return 1;
}

tp_arvore *buscaAbb(tp_arvore *r, tp_item e){
    tp_arvore *atu = r;
    while(atu != NULL && atu->dado != e){
        if(e < atu->dado ){
            atu = atu->esq;
        } else {
            atu = atu->dir;
        }
    }
    return atu;
}

void preOrdemAbb(tp_arvore *r){
    if(r == NULL) return;
    printf("%d ", r->dado);
    preOrdemAbb(r->esq);
    preOrdemAbb(r->dir);
}

void emOrdemAbb(tp_arvore *r){
    if(r == NULL) return;
    emOrdemAbb(r->esq);
    printf("%d ", r->dado);
    emOrdemAbb(r->dir);
}

void posOrdemAbb(tp_arvore *r){
    if(r == NULL) return;
    posOrdemAbb(r->esq);
    posOrdemAbb(r->dir);
    printf("%d ", r->dado);
}

#endif