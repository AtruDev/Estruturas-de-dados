#include <stdio.h>
#include "../pilhaDin.h"

// balanceado e ordenaPilhadin estao em pilhaDin.h

void imprimeTopoBase(tp_pilhadin *p){
    for(; p != NULL; p = p->prox) printf("%d ", p->dado);
    printf("\n");
}

int main(){
    tp_pilhadin *p = inicializarPilhadin();
    int base[] = {2, 4, 1, 3}, i;   // empilhando nessa ordem, o topo fica 3 1 4 2

    printf("== 1. balanceado\n");
    printf("\"{[()]}\" -> %d\n", balanceado("{[()]}"));  // 1
    printf("\"([)]\"   -> %d\n", balanceado("([)]"));    // 0
    printf("\"((\"     -> %d\n", balanceado("(("));      // 0
    printf("\"))\"     -> %d\n", balanceado("))"));      // 0
    printf("\"\"       -> %d\n", balanceado(""));        // 1
    printf("\"a*(b+c[1])\" -> %d\n", balanceado("a*(b+c[1])")); // 1

    printf("\n== 2. ordenaPilhadin (topo -> base)\n");
    for(i = 0; i < 4; i++) pushPilhadin(&p, base[i]);
    printf("antes:  "); imprimeTopoBase(p);   // 3 1 4 2
    ordenaPilhadin(&p);
    printf("depois: "); imprimeTopoBase(p);   // 1 2 3 4
    liberaPilhadin(&p);
    ordenaPilhadin(&p);
    printf("vazia:  "); imprimeTopoBase(p);
    return 0;
}
