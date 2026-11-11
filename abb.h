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
        if(e < atu->dado){
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

// Altura = numero de niveis (vazia = 0, folha = 1)
int alturaAbb(tp_arvore *r){
    if(r == NULL) return 0;
    int altEsq = alturaAbb(r->esq);
    int altDir = alturaAbb(r->dir);
    if(altEsq > altDir){
        return altEsq + 1;
    } else {
        return altDir + 1;
    }
}

// Tamanho = quantidade de nos
int tamanhoAbb(tp_arvore *r){
    if(r == NULL) return 0;
    int tamEsq = tamanhoAbb(r->esq);
    int tamDir = tamanhoAbb(r->dir);
    return tamDir + tamEsq + 1;
}

tp_arvore *minimoAbb(tp_arvore *r){
    if(r == NULL) return NULL;
    tp_arvore *atu = r;
    while(atu->esq != NULL){
        atu = atu->esq;
    }
    return atu;
}

tp_arvore *maximoAbb(tp_arvore *r){
    if(r == NULL) return NULL;
    tp_arvore *atu = r;
    while(atu->dir != NULL){
        atu = atu->dir;
    }
    return atu;
}

// Remove 1 ocorrencia; 0 se nao achar.
// No com 2 filhos: copia o sucessor (menor da subarvore direita) e remove o sucessor.
int removeValorAbb(tp_arvore **r, tp_item e){
    tp_arvore *atu = *r, *pai = NULL, *temp = NULL, *filho = NULL;
    while(atu != NULL && atu->dado != e){
        pai = atu;
        if(e < atu->dado){
            atu = atu->esq;
        } else {
            atu = atu->dir;
        }
    }
    if(atu == NULL) return 0;
    if(atu->esq != NULL && atu->dir != NULL){
        pai = atu;
        temp = atu->dir;
        while(temp->esq != NULL){
            pai = temp;
            temp = temp->esq;
        }
        atu->dado = temp->dado;
        atu = temp;
    }
    if(atu->esq != NULL) filho = atu->esq;
    else filho = atu->dir;
    if(pai == NULL) *r = filho;
    else if(pai->esq == atu) pai->esq = filho;
    else pai->dir = filho;
    free(atu);
    return 1;
}

//funcao auxiliar a liberaAbb
void liberaNoAbb(tp_arvore *r){
    if(r == NULL) return;
    liberaNoAbb(r->esq);
    liberaNoAbb(r->dir);
    free(r);
}

void liberaAbb(tp_arvore **r){
    liberaNoAbb(*r);
    *r = NULL;
}

#endif
