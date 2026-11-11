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
int alturaAbb(tp_arvore *r) { if (!r) return 0; int e = alturaAbb(r->esq), d = alturaAbb(r->dir); return (e > d ? e : d) + 1; }
int tamanhoAbb(tp_arvore *r) { if (!r) return 0; return tamanhoAbb(r->esq) + tamanhoAbb(r->dir) + 1; }
tp_arvore *minimoAbb(tp_arvore *r) { if (!r) return NULL; while (r->esq) r = r->esq; return r; }
tp_arvore *maximoAbb(tp_arvore *r) { if (!r) return NULL; while (r->dir) r = r->dir; return r; }
int removeValorAbb(tp_arvore **r, tp_item e) { tp_arvore *atu = *r, *pai = NULL, *t, *f; while (atu && atu->dado != e) { pai = atu; atu = e < atu->dado ? atu->esq : atu->dir; } if (!atu) return 0; if (atu->esq && atu->dir) { pai = atu; t = atu->dir; while (t->esq) { pai = t; t = t->esq; } atu->dado = t->dado; atu = t; } f = atu->esq ? atu->esq : atu->dir; if (!pai) *r = f; else if (pai->esq == atu) pai->esq = f; else pai->dir = f; free(atu); return 1; }
void liberaNoAbb(tp_arvore *r) { if (!r) return; liberaNoAbb(r->esq); liberaNoAbb(r->dir); free(r); }
void liberaAbb(tp_arvore **r) { liberaNoAbb(*r); *r = NULL; }
#endif
