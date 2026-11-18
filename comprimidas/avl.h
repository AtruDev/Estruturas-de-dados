#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
#ifndef TP_ITEM
#define TP_ITEM
typedef int tp_item;
#endif
typedef struct no_avl { struct no_avl *esq; tp_item dado; int alt; struct no_avl *dir; } tp_avl;
tp_avl *inicializarAvl() { return NULL; }
int vaziaAvl(tp_avl *r) { return r == NULL; }
int alturaAvl(tp_avl *r) { return r ? r->alt : 0; }
void atualizaAlturaAvl(tp_avl *r) { int e = alturaAvl(r->esq), d = alturaAvl(r->dir); r->alt = (e > d ? e : d) + 1; }
int fatorBalanceamentoAvl(tp_avl *r) { return r ? alturaAvl(r->esq) - alturaAvl(r->dir) : 0; }
void rotacaoLLAvl(tp_avl **r) { tp_avl *n = (*r)->esq; (*r)->esq = n->dir; n->dir = *r; atualizaAlturaAvl(*r); atualizaAlturaAvl(n); *r = n; }
void rotacaoRRAvl(tp_avl **r) { tp_avl *n = (*r)->dir; (*r)->dir = n->esq; n->esq = *r; atualizaAlturaAvl(*r); atualizaAlturaAvl(n); *r = n; }
void rotacaoLRAvl(tp_avl **r) { rotacaoRRAvl(&(*r)->esq); rotacaoLLAvl(r); }
void rotacaoRLAvl(tp_avl **r) { rotacaoLLAvl(&(*r)->dir); rotacaoRRAvl(r); }
void balanceiaAvl(tp_avl **r) { atualizaAlturaAvl(*r); int fb = fatorBalanceamentoAvl(*r); if (fb > 1) { if (fatorBalanceamentoAvl((*r)->esq) >= 0) rotacaoLLAvl(r); else rotacaoLRAvl(r); } else if (fb < -1) { if (fatorBalanceamentoAvl((*r)->dir) <= 0) rotacaoRRAvl(r); else rotacaoRLAvl(r); } }
int insereAvl(tp_avl **r, tp_item e) { int res; if (!*r) { tp_avl *n = malloc(sizeof(tp_avl)); if (!n) return 0; n->dado = e; n->alt = 1; n->esq = n->dir = NULL; *r = n; return 1; } if (e == (*r)->dado) return 0; res = insereAvl(e < (*r)->dado ? &(*r)->esq : &(*r)->dir, e); if (res) balanceiaAvl(r); return res; }
tp_avl *buscaAvl(tp_avl *r, tp_item e) { while (r && r->dado != e) r = e < r->dado ? r->esq : r->dir; return r; }
void preOrdemAvl(tp_avl *r) { if (!r) return; printf("%d ", r->dado); preOrdemAvl(r->esq); preOrdemAvl(r->dir); }
void emOrdemAvl(tp_avl *r) { if (!r) return; emOrdemAvl(r->esq); printf("%d ", r->dado); emOrdemAvl(r->dir); }
void posOrdemAvl(tp_avl *r) { if (!r) return; posOrdemAvl(r->esq); posOrdemAvl(r->dir); printf("%d ", r->dado); }
int tamanhoAvl(tp_avl *r) { if (!r) return 0; return tamanhoAvl(r->esq) + tamanhoAvl(r->dir) + 1; }
tp_avl *minimoAvl(tp_avl *r) { if (!r) return NULL; while (r->esq) r = r->esq; return r; }
tp_avl *maximoAvl(tp_avl *r) { if (!r) return NULL; while (r->dir) r = r->dir; return r; }
int removeValorAvl(tp_avl **r, tp_item e) { int res; tp_avl *v; if (!*r) return 0; if (e < (*r)->dado) res = removeValorAvl(&(*r)->esq, e); else if (e > (*r)->dado) res = removeValorAvl(&(*r)->dir, e); else if ((*r)->esq && (*r)->dir) { (*r)->dado = minimoAvl((*r)->dir)->dado; res = removeValorAvl(&(*r)->dir, (*r)->dado); } else { v = *r; *r = v->esq ? v->esq : v->dir; free(v); return 1; } if (res) balanceiaAvl(r); return res; }
void liberaNoAvl(tp_avl *r) { if (!r) return; liberaNoAvl(r->esq); liberaNoAvl(r->dir); free(r); }
void liberaAvl(tp_avl **r) { liberaNoAvl(*r); *r = NULL; }
#endif
