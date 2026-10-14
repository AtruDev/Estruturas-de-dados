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

#endif