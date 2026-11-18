#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct no_avl {
    struct no_avl *esq;
    tp_item dado;
    int alt;              // altura do no: folha = 1 (mesma convencao da alturaAbb)
    struct no_avl *dir;
} tp_avl;

tp_avl *inicializarAvl(){return NULL;}

int vaziaAvl(tp_avl *r){return r == NULL;}

// Altura guardada no no (vazia = 0, folha = 1). O(1).
int alturaAvl(tp_avl *r){
    if(r == NULL) return 0;
    return r->alt;
}

// Recalcula a altura de um no a partir dos filhos
void atualizaAlturaAvl(tp_avl *r){
    int altEsq = alturaAvl(r->esq);
    int altDir = alturaAvl(r->dir);
    if(altEsq > altDir){
        r->alt = altEsq + 1;
    } else {
        r->alt = altDir + 1;
    }
}

// Fator de balanceamento = altura(esq) - altura(dir)
// > 1: pesado a esquerda; < -1: pesado a direita
int fatorBalanceamentoAvl(tp_avl *r){
    if(r == NULL) return 0;
    return alturaAvl(r->esq) - alturaAvl(r->dir);
}

// Rotacao simples a direita (desbalanceio esquerda-esquerda)
void rotacaoLLAvl(tp_avl **r){
    tp_avl *no = (*r)->esq;
    (*r)->esq = no->dir;
    no->dir = *r;
    atualizaAlturaAvl(*r);
    atualizaAlturaAvl(no);
    *r = no;
}

// Rotacao simples a esquerda (desbalanceio direita-direita)
void rotacaoRRAvl(tp_avl **r){
    tp_avl *no = (*r)->dir;
    (*r)->dir = no->esq;
    no->esq = *r;
    atualizaAlturaAvl(*r);
    atualizaAlturaAvl(no);
    *r = no;
}

// Rotacao dupla: esquerda no filho esquerdo, depois direita
void rotacaoLRAvl(tp_avl **r){
    rotacaoRRAvl(&(*r)->esq);
    rotacaoLLAvl(r);
}

// Rotacao dupla: direita no filho direito, depois esquerda
void rotacaoRLAvl(tp_avl **r){
    rotacaoLLAvl(&(*r)->dir);
    rotacaoRRAvl(r);
}

// Atualiza a altura de *r e aplica a rotacao necessaria (serve para insercao e remocao)
void balanceiaAvl(tp_avl **r){
    atualizaAlturaAvl(*r);
    int fb = fatorBalanceamentoAvl(*r);
    if(fb > 1){
        if(fatorBalanceamentoAvl((*r)->esq) >= 0){
            rotacaoLLAvl(r);
        } else {
            rotacaoLRAvl(r);
        }
    } else if(fb < -1){
        if(fatorBalanceamentoAvl((*r)->dir) <= 0){
            rotacaoRRAvl(r);
        } else {
            rotacaoRLAvl(r);
        }
    }
}

// Recursiva (precisa rebalancear no caminho de volta).
// 0 se o valor ja existir (AVL nao aceita repetidos) ou se faltar memoria.
int insereAvl(tp_avl **r, tp_item e){
    int res;
    if(*r == NULL){
        tp_avl *novo_no = malloc(sizeof(tp_avl));
        if(novo_no == NULL) return 0;
        novo_no->dado = e;
        novo_no->alt = 1;
        novo_no->esq = NULL; novo_no->dir = NULL;
        *r = novo_no;
        return 1;
    }
    if(e < (*r)->dado){
        res = insereAvl(&(*r)->esq, e);
    } else if(e > (*r)->dado){
        res = insereAvl(&(*r)->dir, e);
    } else {
        return 0; // valor duplicado
    }
    if(res) balanceiaAvl(r);
    return res;
}

tp_avl *buscaAvl(tp_avl *r, tp_item e){
    tp_avl *atu = r;
    while(atu != NULL && atu->dado != e){
        if(e < atu->dado){
            atu = atu->esq;
        } else {
            atu = atu->dir;
        }
    }
    return atu;
}

void preOrdemAvl(tp_avl *r){
    if(r == NULL) return;
    printf("%d ", r->dado);
    preOrdemAvl(r->esq);
    preOrdemAvl(r->dir);
}

void emOrdemAvl(tp_avl *r){
    if(r == NULL) return;
    emOrdemAvl(r->esq);
    printf("%d ", r->dado);
    emOrdemAvl(r->dir);
}

void posOrdemAvl(tp_avl *r){
    if(r == NULL) return;
    posOrdemAvl(r->esq);
    posOrdemAvl(r->dir);
    printf("%d ", r->dado);
}

// Tamanho = quantidade de nos
int tamanhoAvl(tp_avl *r){
    if(r == NULL) return 0;
    return tamanhoAvl(r->esq) + tamanhoAvl(r->dir) + 1;
}

tp_avl *minimoAvl(tp_avl *r){
    if(r == NULL) return NULL;
    tp_avl *atu = r;
    while(atu->esq != NULL){
        atu = atu->esq;
    }
    return atu;
}

tp_avl *maximoAvl(tp_avl *r){
    if(r == NULL) return NULL;
    tp_avl *atu = r;
    while(atu->dir != NULL){
        atu = atu->dir;
    }
    return atu;
}

// Remove o valor; 0 se nao achar.
// No com 2 filhos: copia o sucessor (menor da subarvore direita) e remove o sucessor.
// Rebalanceia todos os nos no caminho de volta ate a raiz.
int removeValorAvl(tp_avl **r, tp_item e){
    int res;
    if(*r == NULL) return 0;
    if(e < (*r)->dado){
        res = removeValorAvl(&(*r)->esq, e);
    } else if(e > (*r)->dado){
        res = removeValorAvl(&(*r)->dir, e);
    } else {
        if((*r)->esq != NULL && (*r)->dir != NULL){
            tp_avl *suc = minimoAvl((*r)->dir);
            (*r)->dado = suc->dado;
            res = removeValorAvl(&(*r)->dir, suc->dado);
        } else {
            tp_avl *velho = *r;
            if(velho->esq != NULL) *r = velho->esq;
            else *r = velho->dir;
            free(velho);
            return 1;
        }
    }
    if(res) balanceiaAvl(r);
    return res;
}

//funcao auxiliar a liberaAvl
void liberaNoAvl(tp_avl *r){
    if(r == NULL) return;
    liberaNoAvl(r->esq);
    liberaNoAvl(r->dir);
    free(r);
}

void liberaAvl(tp_avl **r){
    liberaNoAvl(*r);
    *r = NULL;
}

#endif
