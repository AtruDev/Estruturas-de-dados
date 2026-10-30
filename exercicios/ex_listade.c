#include <stdio.h>
#include "../listade.h"

// ehPalindromoListade e trocaNosListade estao em listade.h

tp_listade *cria(int *v, int n){
    tp_listade *l = inicializarListade();
    int i;
    for(i = 0; i < n; i++) insereFimde(&l, v[i]);
    return l;
}

int main(){
    int p1[] = {1, 2, 3, 2, 1}, p2[] = {1, 2, 2, 1}, p3[] = {1, 2, 3};
    int v[] = {1, 2, 3, 4, 5};
    tp_listade *l;

    printf("== 1. ehPalindromoListade\n");
    l = cria(p1, 5); printf("1 2 3 2 1 -> %d\n", ehPalindromoListade(l)); liberaListade(&l);  // 1
    l = cria(p2, 4); printf("1 2 2 1   -> %d\n", ehPalindromoListade(l)); liberaListade(&l);  // 1
    l = cria(p3, 3); printf("1 2 3     -> %d\n", ehPalindromoListade(l)); liberaListade(&l);  // 0
    printf("vazia     -> %d\n", ehPalindromoListade(NULL));                                 // 1

    // imprimeInversoListade confere se os ponteiros ant ficaram certos
    printf("\n== 2. trocaNosListade\n");
    l = cria(v, 5);
    printf("troca 2 e 4: %d -> ", trocaNosListade(&l, 2, 4)); imprimeListade(l);   // 1 4 3 2 5
    printf("  inverso: "); imprimeInversoListade(l);
    printf("vizinhos 3 e 2: %d -> ", trocaNosListade(&l, 3, 2)); imprimeListade(l); // 1 4 2 3 5
    printf("  inverso: "); imprimeInversoListade(l);
    printf("cabeca e fim 1 e 5: %d -> ", trocaNosListade(&l, 1, 5)); imprimeListade(l); // 5 4 2 3 1
    printf("  inverso: "); imprimeInversoListade(l);
    printf("vizinhos na cabeca 5 e 4: %d -> ", trocaNosListade(&l, 5, 4)); imprimeListade(l); // 4 5 2 3 1
    printf("  inverso: "); imprimeInversoListade(l);
    printf("valor inexistente 9: %d -> ", trocaNosListade(&l, 1, 9)); imprimeListade(l);
    liberaListade(&l);
    return 0;
}
