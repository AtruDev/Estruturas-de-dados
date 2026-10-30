#include <stdio.h>
#include "../listase.h"

// inverteListase e intercalaListase estao em listase.h

void imprimeLinha(tp_lista *l){
    for(; l != NULL; l = l->prox) printf("%d ", l->dado);
    printf("\n");
}

int main(){
    tp_lista *l = inicializarListase();
    tp_lista *l1 = inicializarListase(), *l2 = inicializarListase(), *nova;
    int i;

    printf("== 1. inverteListase\n");
    inverteListase(&l);
    printf("vazia: "); imprimeLinha(l);
    insereFimse(&l, 1);
    inverteListase(&l);
    printf("1 no: "); imprimeLinha(l);                 // 1
    for(i = 2; i <= 4; i++) insereFimse(&l, i);
    inverteListase(&l);
    printf("1 2 3 4 -> "); imprimeLinha(l);            // 4 3 2 1

    printf("\n== 2. intercalaListase\n");
    insereFimse(&l1, 1); insereFimse(&l1, 4); insereFimse(&l1, 7);
    insereFimse(&l2, 2); insereFimse(&l2, 3); insereFimse(&l2, 8); insereFimse(&l2, 9);
    nova = intercalaListase(l1, l2);
    printf("1 4 7 + 2 3 8 9 -> "); imprimeLinha(nova);  // 1 2 3 4 7 8 9
    printf("l1 intacta: "); imprimeLinha(l1);
    printf("l2 intacta: "); imprimeLinha(l2);
    liberaListase(&nova);
    nova = intercalaListase(NULL, l2);
    printf("vazia + 2 3 8 9 -> "); imprimeLinha(nova);
    liberaListase(&nova);

    liberaListase(&l); liberaListase(&l1); liberaListase(&l2);
    return 0;
}
