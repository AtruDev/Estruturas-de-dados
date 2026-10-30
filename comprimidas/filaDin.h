#ifndef FILA_DIN
#define FILA_DIN
/* depende da listade: vem embutida abaixo (pulada se ja tiver sido colada) */
#ifndef LISTA_DE
#define LISTA_DE
#include <stdio.h>
#include <stdlib.h>
#ifndef TP_ITEM
#define TP_ITEM
typedef int tp_item;
#endif
typedef struct no_de { tp_item dado; struct no_de *ant, *prox; } tp_listade;
tp_listade *inicializarListade() { return NULL; }
int vaziaListade(tp_listade *l) { return l == NULL; }
int tamanhoListade(tp_listade *l) { int c = 0; for (; l; l = l->prox) c++; return c; }
void imprimeListade(tp_listade *l) { if (!l) { printf("Lista vazia\n"); return; } for (; l; l = l->prox) printf("%d ", l->dado); printf("\n"); }
void imprimeInversoListade(tp_listade *l) { if (!l) { printf("Lista vazia\n"); return; } while (l->prox) l = l->prox; for (; l; l = l->ant) printf("%d ", l->dado); printf("\n"); }
tp_listade *buscaListade(tp_listade *l, tp_item e) { while (l && l->dado != e) l = l->prox; return l; }
int maiorQueListade(tp_listade *l, tp_item x) { int c = 0; for (; l; l = l->prox) if (l->dado > x) c++; return c; }
int listasIdenticasListade(tp_listade *l1, tp_listade *l2) { if (tamanhoListade(l1) != tamanhoListade(l2)) return 0; for (; l1 && l2; l1 = l1->prox, l2 = l2->prox) if (l1->dado != l2->dado) return 0; return 1; }
int insereIniciode(tp_listade **l, tp_item e) { tp_listade *n = malloc(sizeof(tp_listade)); if (!n) return 0; n->dado = e; n->ant = NULL; n->prox = *l; if (*l) (*l)->ant = n; *l = n; return 1; }
int insereFimde(tp_listade **l, tp_item e) { tp_listade *n = malloc(sizeof(tp_listade)), *a; if (!n) return 0; n->dado = e; n->prox = NULL; if (!*l) { n->ant = NULL; *l = n; return 1; } for (a = *l; a->prox; a = a->prox); a->prox = n; n->ant = a; return 1; }
int inseriOrdenadoListade(tp_listade **l, tp_item e) { tp_listade *n, *a = *l; if (!a || e <= a->dado) return insereIniciode(l, e); if (!(n = malloc(sizeof(tp_listade)))) return 0; n->dado = e; while (a->prox && e > a->prox->dado) a = a->prox; n->prox = a->prox; n->ant = a; if (a->prox) a->prox->ant = n; a->prox = n; return 1; }
int removeiniListade(tp_listade **l, tp_item *e) { tp_listade *a = *l; if (!a) return 0; *e = a->dado; *l = a->prox; if (*l) (*l)->ant = NULL; free(a); return 1; }
int removefimListade(tp_listade **l, tp_item *e) { tp_listade *a = *l; if (!a) return 0; while (a->prox) a = a->prox; *e = a->dado; if (a->ant) a->ant->prox = NULL; else *l = NULL; free(a); return 1; }
int removeValorListade(tp_listade **l, tp_item e) { tp_listade *a = buscaListade(*l, e); if (!a) return 0; if (a->ant) a->ant->prox = a->prox; else *l = a->prox; if (a->prox) a->prox->ant = a->ant; free(a); return 1; }
int liberaListade(tp_listade **l) { tp_listade *a = *l, *p; if (!a) return 0; while (a) { p = a->prox; free(a); a = p; } *l = NULL; return 1; }
int ehPalindromoListade(tp_listade *l) { tp_listade *i = l, *f = l; if (!l) return 1; while (f->prox) f = f->prox; for (; i != f && i->ant != f; i = i->prox, f = f->ant) if (i->dado != f->dado) return 0; return 1; }
int trocaNosListade(tp_listade **l, tp_item a, tp_item b) { tp_listade *x = buscaListade(*l, a), *y = buscaListade(*l, b), *t, *ax, *py; if (!x || !y) return 0; if (x == y) return 1; for (t = x; t && t != y; t = t->prox); if (!t) { t = x; x = y; y = t; } ax = x->ant; py = y->prox; if (x->prox == y) { y->prox = x; x->ant = y; } else { tp_listade *px = x->prox, *ay = y->ant; y->prox = px; px->ant = y; x->ant = ay; ay->prox = x; } y->ant = ax; x->prox = py; if (ax) ax->prox = y; else *l = y; if (py) py->ant = x; return 1; }
#endif
typedef tp_listade tp_filadin;
tp_filadin *inicializarFiladin() { return inicializarListade(); }
int vaziaFiladin(tp_filadin *f) { return vaziaListade(f); }
int enqueueFiladin(tp_filadin **f, tp_item e) { return insereFimde(f, e); }
int dequeueFiladin(tp_filadin **f, tp_item *e) { return removeiniListade(f, e); }
int frontFiladin(tp_filadin *f, tp_item *e) { if (!f) return 0; *e = f->dado; return 1; }
int tamanhoFiladin(tp_filadin *f) { return tamanhoListade(f); }
void imprimeFiladin(tp_filadin *f) { imprimeListade(f); }
int liberaFiladin(tp_filadin **f) { return liberaListade(f); }
int josephus(int n, int k) { tp_filadin *f = NULL; tp_item e; int i, v; if (n <= 0 || k <= 0) return 0; for (i = 1; i <= n; i++) enqueueFiladin(&f, i); for (v = n; v > 1; v--) { for (i = 1; i < k; i++) { dequeueFiladin(&f, &e); enqueueFiladin(&f, e); } dequeueFiladin(&f, &e); printf("%d ", e); } printf("\n"); dequeueFiladin(&f, &e); return e; }
#endif
