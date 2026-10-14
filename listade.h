#ifndef LISTA_DE
#define LISTA_DE

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct no {
    tp_item dado;
    struct no *ant;
    struct no *prox;
} tp_listade;

// ===================== Base =====================
tp_listade *inicializarListade() {
    return NULL;
}

int vaziaListade(tp_listade *l) {
    return l == NULL;
}

void imprimeListade(tp_listade *l) {
    tp_listade *atu = l;
    if (vaziaListade(l)) {
        printf("Lista vazia\n");
        return;
    }
    while (atu != NULL) {
        printf("%d ", atu->dado);
        atu = atu->prox;
    }
    printf("\n");
}

// exclusivo da DE
void imprimeInversoListade(tp_listade *l) {
    tp_listade *atu = l;
    if (vaziaListade(l)) {
        printf("Lista vazia\n");
        return;
    }
    while (atu->prox != NULL) {
        atu = atu->prox;
    }
    while (atu != NULL) {
        printf("%d ", atu->dado);
        atu = atu->ant;
    }
    printf("\n");
}

int tamanhoListade(tp_listade *l) {
    tp_listade *atu = l;
    int cont = 0;
    while (atu != NULL) {
        cont++;
        atu = atu->prox;
    }
    return cont;
}

// ===================== Consulta =====================
tp_listade *buscaListade(tp_listade *l, tp_item e) {
    tp_listade *atu = l;
    while (atu != NULL && atu->dado != e) {
        atu = atu->prox;
    }
    return atu;
}

int maiorQueListade(tp_listade *l, tp_item x) {
    tp_listade *atu = l;
    int cont = 0;
    while (atu != NULL) {
        if (atu->dado > x) cont++;
        atu = atu->prox;
    }
    return cont;
}

int listasIdenticasListade(tp_listade *l1, tp_listade *l2) {
    tp_listade *atu1 = l1;
    tp_listade *atu2 = l2;

    if (tamanhoListade(atu1) != tamanhoListade(atu2)) return 0;
    while (atu1 != NULL && atu2 != NULL) {
        if (atu1->dado != atu2->dado) return 0;
        atu1 = atu1->prox;
        atu2 = atu2->prox;
    }
    return 1;
}

// ===================== Inserção =====================
int insereIniciode(tp_listade **l, tp_item e) {
    tp_listade *novo = malloc(sizeof(tp_listade));
    if (novo == NULL) return 0;

    novo->dado = e;
    novo->ant = NULL;
    if (vaziaListade(*l)) {
        novo->prox = NULL;
    } else {
        tp_listade *atu = *l;
        atu->ant = novo;
        novo->prox = atu;
    }
    *l = novo;
    return 1;
}

int insereFimde(tp_listade **l, tp_item e) {
    tp_listade *novo = malloc(sizeof(tp_listade));
    if (novo == NULL) return 0;

    novo->dado = e;
    novo->prox = NULL;

    if (vaziaListade(*l)) {
        novo->ant = NULL;
        *l = novo;
    } else {
        tp_listade *atu = *l;
        while (atu->prox != NULL) {
            atu = atu->prox;
        }
        atu->prox = novo;
        novo->ant = atu;
    }
    return 1;
}

int inseriOrdenadoListade(tp_listade **l, tp_item e){
    tp_listade *novo = malloc(sizeof(tp_listade));
    if (novo == NULL) return 0;
    novo->dado = e;
    if(vaziaListade(*l) || e <= (*l)->dado){
        novo->ant = NULL;
        novo->prox = *l;
        if(!vaziaListade(*l)){
            (*l)->ant = novo;
        }
        *l = novo;
    } else {
        tp_listade *atu = *l;
        while(atu->prox != NULL && e > atu->prox->dado){
            atu = atu->prox;
        }
        novo->prox = atu->prox;
        novo->ant = atu;
        if(atu->prox != NULL) atu->prox->ant = novo;
        atu->prox = novo;
    }
    return 1;
}   

// ===================== Remoção =====================
int removeiniListade(tp_listade **l, tp_item *e) {
    if (vaziaListade(*l)) return 0;
    tp_listade *atu = *l;
    *e = atu->dado;

    *l = atu->prox;
    if (!vaziaListade(*l)) {
        (*l)->ant = NULL;
    }
    free(atu);
    return 1;
}

int removefimListade(tp_listade **l, tp_item *e) {
    if (vaziaListade(*l)) return 0;
    tp_listade *atu = *l;
    while (atu->prox != NULL) {
        atu = atu->prox;
    }
    *e = atu->dado;
    if (atu->ant == NULL) {
        *l = NULL;
    } else {
        atu->ant->prox = NULL;
    }
    free(atu);
    return 1;
}

int removeValorListade(tp_listade **l, tp_item e) {
    tp_listade *atu = buscaListade(*l, e);
    if (atu == NULL) return 0;
    if (atu->ant == NULL) {
        *l = atu->prox;
    } else {
        atu->ant->prox = atu->prox;
    }
    if (atu->prox != NULL) {
        atu->prox->ant = atu->ant;
    }
    free(atu);
    return 1;
}

// ===================== Liberação =====================
int liberaListade(tp_listade **l) {
    if (vaziaListade(*l)) return 0;
    tp_listade *atu, *prox;

    atu = *l;
    while (atu != NULL) {
        prox = atu->prox;
        free(atu);
        atu = prox;
    }
    *l = NULL;
    return 1;
}

#endif