#ifndef FILA_DIN
#define FILA_DIN

#include <stdio.h>
#include <stdlib.h>
#include "listade.h"

typedef tp_listade tp_filadin;

tp_filadin *inicializarFiladin(){
    return inicializarListade();
}
int  vaziaFiladin(tp_filadin *f){
    return vaziaListade(f);
}
int  enqueueFiladin(tp_filadin **f, tp_item e){
    return insereFimde(f,e);
}
int  dequeueFiladin(tp_filadin **f, tp_item *e){
    return removeiniListade(f,e);
}   
int  frontFiladin(tp_filadin *f, tp_item *e){
    if(vaziaFiladin(f)) return 0;
    *e = f->dado;
    return 1;
}      
int  tamanhoFiladin(tp_filadin *f){
    return tamanhoListade(f);
}
void imprimeFiladin(tp_filadin *f) {
    imprimeListade(f);
}
int  liberaFiladin(tp_filadin **f){
    return liberaListade(f);
}

// imprime a ordem de eliminacao e retorna o sobrevivente
int josephus(int n, int k){
    tp_filadin *f = inicializarFiladin();
    tp_item e;
    int i, vivos;
    if(n <= 0 || k <= 0) return 0;
    for(i = 1; i <= n; i++){
        enqueueFiladin(&f, i);
    }
    for(vivos = n; vivos > 1; vivos--){
        for(i = 1; i < k; i++){
            dequeueFiladin(&f, &e);
            enqueueFiladin(&f, e);
        }
        dequeueFiladin(&f, &e);
        printf("%d ", e);
    }
    printf("\n");
    dequeueFiladin(&f, &e);
    return e;
}

#endif