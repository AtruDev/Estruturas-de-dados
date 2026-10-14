#ifndef LISTA_SE
#define LISTA_SE
#include <stdio.h>
#include <stdlib.h>
#ifndef TP_ITEM
#define TP_ITEM
typedef int tp_item;
#endif
typedef struct no_se { tp_item dado; struct no_se *prox; } tp_lista;
tp_lista *inicializarListase() { return NULL; }
int vaziaListase(tp_lista *l) { return l == NULL; }
int insereIniciose(tp_lista **l, tp_item e) { tp_lista *n = malloc(sizeof(tp_lista)); if (!n) return 0; n->dado = e; n->prox = *l; *l = n; return 1; }
int insereFimse(tp_lista **l, tp_item e) { tp_lista *n = malloc(sizeof(tp_lista)), *a; if (!n) return 0; n->dado = e; n->prox = NULL; if (!*l) { *l = n; return 1; } for (a = *l; a->prox; a = a->prox); a->prox = n; return 1; }
int inseriOrdenadoListase(tp_lista **l, tp_item e) { tp_lista *n = malloc(sizeof(tp_lista)), *a = *l; if (!n) return 0; n->dado = e; if (!a || e <= a->dado) { n->prox = *l; *l = n; return 1; } while (a->prox && e > a->prox->dado) a = a->prox; n->prox = a->prox; a->prox = n; return 1; }
int removeiniListase(tp_lista **l, tp_item *e) { tp_lista *a = *l; if (!a) return 0; *e = a->dado; *l = a->prox; free(a); return 1; }
int removefimListase(tp_lista **l, tp_item *e) { tp_lista *a = *l; if (!a) return 0; if (!a->prox) { *e = a->dado; free(a); *l = NULL; return 1; } while (a->prox->prox) a = a->prox; *e = a->prox->dado; free(a->prox); a->prox = NULL; return 1; }
tp_lista *buscaListase(tp_lista *l, tp_item e) { while (l && l->dado != e) l = l->prox; return l; }
int tamanhoListase(tp_lista *l) { int c = 0; for (; l; l = l->prox) c++; return c; }
int maiorQueListase(tp_lista *l, tp_item x) { int c = 0; for (; l; l = l->prox) if (l->dado > x) c++; return c; }
int listasIdenticasListase(tp_lista *l1, tp_lista *l2) { if (tamanhoListase(l1) != tamanhoListase(l2)) return 0; for (; l1 && l2; l1 = l1->prox, l2 = l2->prox) if (l1->dado != l2->dado) return 0; return 1; }
void imprimeListase(tp_lista *l) { if (!l) { printf("Lista vazia\n"); return; } for (; l; l = l->prox) printf("%d\n", l->dado); }
int liberaListase(tp_lista **l) { tp_lista *a = *l, *p; if (!a) return 0; while (a) { p = a->prox; free(a); a = p; } *l = NULL; return 1; }
#endif
