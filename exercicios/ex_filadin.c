#include <stdio.h>
// as versoes completas de pilhaDin.h e filaDin.h nao compilam juntas
// (as duas listas usam struct no), entao aqui vao as comprimidas
#include "../comprimidas/pilhaDin.h"
#include "../comprimidas/filaDin.h"

// josephus esta em filaDin.h

void inverteKFiladin(tp_filadin **f, int k){
    tp_pilhadin *p = inicializarPilhadin();
    tp_item e;
    int n = tamanhoFiladin(*f), i;
    if(k <= 0) return;
    if(k > n) k = n;
    for(i = 0; i < k; i++){
        dequeueFiladin(f, &e);
        pushPilhadin(&p, e);
    }
    while(popPilhadin(&p, &e)){
        enqueueFiladin(f, e);
    }
    // os k invertidos foram pro fim: gira o resto pra tras deles
    for(i = 0; i < n - k; i++){
        dequeueFiladin(f, &e);
        enqueueFiladin(f, e);
    }
}

tp_filadin *cria(int n){
    tp_filadin *f = inicializarFiladin();
    int i;
    for(i = 1; i <= n; i++) enqueueFiladin(&f, i);
    return f;
}

int main(){
    tp_filadin *f;

    printf("== 1. josephus\n");
    printf("n=5 k=2: eliminados "); printf("-> sobrevivente %d\n", josephus(5, 2));  // 2 4 1 5 -> 3
    printf("n=7 k=3: eliminados "); printf("-> sobrevivente %d\n", josephus(7, 3));  // 3 6 2 7 5 1 -> 4
    printf("n=1 k=4: eliminados "); printf("-> sobrevivente %d\n", josephus(1, 4));  // -> 1

    printf("\n== 2. inverteKFiladin\n");
    f = cria(5); inverteKFiladin(&f, 3); printf("1 2 3 4 5, k=3  -> "); imprimeFiladin(f); liberaFiladin(&f); // 3 2 1 4 5
    f = cria(5); inverteKFiladin(&f, 5); printf("1 2 3 4 5, k=5  -> "); imprimeFiladin(f); liberaFiladin(&f); // 5 4 3 2 1
    f = cria(5); inverteKFiladin(&f, 9); printf("1 2 3 4 5, k=9  -> "); imprimeFiladin(f); liberaFiladin(&f); // 5 4 3 2 1
    f = cria(5); inverteKFiladin(&f, 1); printf("1 2 3 4 5, k=1  -> "); imprimeFiladin(f); liberaFiladin(&f); // 1 2 3 4 5
    f = cria(5); inverteKFiladin(&f, 0); printf("1 2 3 4 5, k=0  -> "); imprimeFiladin(f); liberaFiladin(&f);
    return 0;
}
