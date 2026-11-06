#ifndef ABB_H
#define ABB_H
#include <stdio.h>
#include <stdlib.h>
#ifndef TP_ITEM
#define TP_ITEM
typedef int tp_item;
#endif
typedef struct no_abb { struct no_abb *esq; tp_item dado; struct no_abb *dir; } tp_arvore;
tp_arvore *inicializarAbb() { return NULL; }
int vaziaAbb(tp_arvore *r) { return r == NULL; }
int insereAbb(tp_arvore **r, tp_item e) { tp_arvore *n = malloc(sizeof(tp_arvore)); if (!n) return 0; n->dado = e; n->esq = n->dir = NULL; while (*r) r = e < (*r)->dado ? &(*r)->esq : &(*r)->dir; *r = n; return 1; }
tp_arvore *buscaAbb(tp_arvore *r, tp_item e) { while (r && r->dado != e) r = e < r->dado ? r->esq : r->dir; return r; }
void preOrdemAbb(tp_arvore *r) { if (!r) return; printf("%d ", r->dado); preOrdemAbb(r->esq); preOrdemAbb(r->dir); }
void emOrdemAbb(tp_arvore *r) { if (!r) return; emOrdemAbb(r->esq); printf("%d ", r->dado); emOrdemAbb(r->dir); }
void posOrdemAbb(tp_arvore *r) { if (!r) return; posOrdemAbb(r->esq); posOrdemAbb(r->dir); printf("%d ", r->dado); }
#endif
