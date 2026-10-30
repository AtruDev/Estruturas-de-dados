#ifndef LISTA_SE
#define LISTA_SE

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct no{
    tp_item dado;
    struct no *prox;
} tp_lista;

tp_lista *inicializarListase() {
    return NULL;
}

int insereIniciose(tp_lista **l, tp_item e){
    tp_lista *novo_no = malloc(sizeof(tp_lista));
    if (novo_no == NULL) return 0;

    novo_no->dado = e;
    novo_no->prox = *l;

    *l = novo_no;
    return 1;
}

int vaziaListase(tp_lista *l) {
    if(l == NULL) return 1;
    return 0;
}

void imprimeListase(tp_lista *l){
    tp_lista *atu;
    if (vaziaListase(l)) {
        printf("Lista vazia\n"); return;
    }
    atu = l;
    while(atu != NULL) {
        printf("%d\n", atu->dado);
        atu = atu->prox;
    }
}

int insereFimse(tp_lista **l, tp_item e) {
    tp_lista* novo_no = malloc(sizeof(tp_lista)); if (novo_no == NULL) return 0;
    tp_lista *atu;

    novo_no->dado = e;
    novo_no->prox = NULL;
    if(vaziaListase(*l)){
        *l = novo_no;
    } else {
        atu = *l;
        while(atu->prox != NULL){
            atu = atu->prox;
        }
        atu->prox = novo_no;
    }
    return 1;
}

int removeiniListase(tp_lista **l, tp_item *e) {
    if (vaziaListase(*l)) return 0;
    tp_lista *atu;
    atu = *l;
    *e = atu->dado;
    *l = atu->prox;
    free(atu);
    return 1;
}

int removefimListase(tp_lista **l, tp_item *e) {
    if(vaziaListase(*l)) return 0;
    tp_lista *atu;
    atu = *l;
    if(atu->prox == NULL) {
        *l = NULL;
        *e = atu->dado;
        free(atu);
        return 1;
    }
    while(atu->prox->prox != NULL) {
        atu = atu->prox;
    }
    *e = atu->prox->dado;
    free(atu->prox);
    atu->prox = NULL;
    return 1;    
}

tp_lista* buscaListase(tp_lista *l, tp_item e){
    tp_lista *atu = l;
    while(atu != NULL && atu->dado != e){
        atu = atu->prox;
    }
    return atu;
}

int tamanhoListase(tp_lista *l){
    tp_lista *atu = l;
    int cont=0;
    while (atu != NULL){
        atu = atu->prox;
        cont++;
    }
    return cont;
}

int liberaListase(tp_lista **l){
    if(vaziaListase(*l)) return 0;
    tp_lista *atu, *prox;

    atu = *l;
    while(atu != NULL){
        prox = atu->prox;
        free(atu);
        atu = prox;
    }
    *l = NULL;
    return 1;
}

int maiorQueListase(tp_lista *l, tp_item x){
    tp_lista *atu = l;
    int cont=0;
    while (atu != NULL){
        if(atu->dado > x) cont++;
        atu = atu->prox;
    }
    return cont;
}

int listasIdenticasListase(tp_lista *l1, tp_lista *l2){
    tp_lista *atu1 = l1;
    tp_lista *atu2 = l2;

    if(tamanhoListase(atu1) != tamanhoListase(atu2)) return 0;
    while(atu1 != NULL && atu2 != NULL){
        if(atu1->dado != atu2->dado) return 0;
        atu1 = atu1->prox; atu2 = atu2->prox;
    }
    
    return 1;
}

int inseriOrdenadoListase(tp_lista **l, tp_item e){
    tp_lista *novo_no = malloc(sizeof(tp_lista));
    if(novo_no == NULL) return 0;
    tp_lista *atu = *l; 

    novo_no->dado = e;

    if(vaziaListase(atu) || e <= atu->dado){
        novo_no->prox = *l;
        *l = novo_no;
    } else {
        while(atu->prox != NULL && e > atu->prox->dado) {
            atu = atu->prox;
        }
        novo_no->prox = atu->prox;
        atu->prox = novo_no;
    }
    return 1;
}

int removeValorListase(tp_lista **l, tp_item e){
    tp_lista *atu = *l, *ant = NULL;
    while(atu != NULL && atu->dado != e){
        ant = atu;
        atu = atu->prox;
    }
    if(atu == NULL) return 0;
    if(ant == NULL){
        *l = atu->prox;
    } else {
        ant->prox = atu->prox;
    }
    free(atu);
    return 1;
}

int destruirNosImparListase(tp_lista **l){
    tp_lista *atu = *l, *ant = NULL, *prox;
    int cont = 0;
    while(atu != NULL){
        prox = atu->prox;
        if(atu->dado % 2 != 0){
            if(ant == NULL){
                *l = prox;
            } else {
                ant->prox = prox;
            }
            free(atu);
            cont++;
        } else {
            ant = atu;
        }
        atu = prox;
    }
    return cont;
}
void inverteListase(tp_lista **l){
    tp_lista *atu = *l, *ant = NULL, *prox;
    while(atu != NULL){
        prox = atu->prox;
        atu->prox = ant;
        ant = atu;
        atu = prox;
    }
    *l = ant;
}

tp_lista *intercalaListase(tp_lista *l1, tp_lista *l2){
    tp_lista *nova = NULL, *fim = NULL, *novo_no;
    tp_item e;
    while(l1 != NULL || l2 != NULL){
        if(l2 == NULL || (l1 != NULL && l1->dado <= l2->dado)){
            e = l1->dado;
            l1 = l1->prox;
        } else {
            e = l2->dado;
            l2 = l2->prox;
        }
        novo_no = malloc(sizeof(tp_lista));
        if(novo_no == NULL){
            liberaListase(&nova);
            return NULL;
        }
        novo_no->dado = e;
        novo_no->prox = NULL;
        if(fim == NULL){
            nova = novo_no;
        } else {
            fim->prox = novo_no;
        }
        fim = novo_no;
    }
    return nova;
}

#endif