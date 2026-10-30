#ifndef PILHA_DIN
#define PILHA_DIN

#include <stdio.h>
#include <stdlib.h>
#include "listase.h"

typedef tp_lista tp_pilhadin;

tp_pilhadin *inicializarPilhadin(){
    return inicializarListase();
}

int vaziaPilhadin(tp_pilhadin *p){
    return vaziaListase(p);
}

int pushPilhadin(tp_pilhadin **p, tp_item e){
    return insereIniciose(p, e);
}

int popPilhadin(tp_pilhadin **p, tp_item *e){
    return removeiniListase(p, e);
}

int topPilhadin(tp_pilhadin *p, tp_item *e){
    if(vaziaPilhadin(p)) return 0;
    *e = p->dado;
    return 1;
}

int tamanhoPilhadin(tp_pilhadin *p){
    return tamanhoListase(p);
}

void imprimePilhadin(tp_pilhadin *p){
    imprimeListase(p);
}

int liberaPilhadin(tp_pilhadin **p){
    return liberaListase(p);
}

// menor elemento no topo, usando so uma pilha auxiliar
void ordenaPilhadin(tp_pilhadin **p){
    tp_pilhadin *aux = inicializarPilhadin();
    tp_item e, t;
    while(popPilhadin(p, &e)){
        // aux fica sempre com o menor no topo
        while(topPilhadin(aux, &t) && t < e){
            popPilhadin(&aux, &t);
            pushPilhadin(p, t);
        }
        pushPilhadin(&aux, e);
    }
    *p = aux;
}

char abreDe(char c){
    if(c == ')') return '(';
    if(c == ']') return '[';
    return '{';
}

int balanceado(char *s){
    tp_pilhadin *p;
    tp_item topo;
    int ok;
    p = inicializarPilhadin();
    for(; *s != '\0'; s++){
        if(*s == '(' || *s == '[' || *s == '{'){
            pushPilhadin(&p, *s);
        } else if(*s == ')' || *s == ']' || *s == '}'){
            if(!popPilhadin(&p, &topo) || topo != abreDe(*s)){
                liberaPilhadin(&p);
                return 0;
            }
        }
    }
    ok = vaziaPilhadin(p);
    liberaPilhadin(&p);
    return ok;
}

#endif