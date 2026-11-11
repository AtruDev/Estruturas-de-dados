#include <stdio.h>
#include "../abb.h"

// alturaAbb, tamanhoAbb, minimoAbb, maximoAbb, removeValorAbb e liberaAbb estao em abb.h

void imprimeNo(const char *rotulo, tp_arvore *n, const char *esperado){
    if(n == NULL) printf("%s NULL (esperado %s)\n", rotulo, esperado);
    else printf("%s %d (esperado %s)\n", rotulo, n->dado, esperado);
}

void imprimePreEm(tp_arvore *r, const char *preEsp, const char *emEsp){
    printf("  pre: "); preOrdemAbb(r); printf("  (esperado %s)\n", preEsp);
    printf("  em:  "); emOrdemAbb(r);  printf("  (esperado %s)\n", emEsp);
}

int main(){
    tp_arvore *r = inicializarAbb();
    int v[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65}, i;

    printf("== 0. arvore vazia\n");
    printf("vazia: %d (esperado 1)\n", vaziaAbb(r));
    printf("altura: %d (esperado 0)\n", alturaAbb(r));
    printf("tamanho: %d (esperado 0)\n", tamanhoAbb(r));
    imprimeNo("minimo:", minimoAbb(r), "NULL");
    imprimeNo("maximo:", maximoAbb(r), "NULL");
    printf("remove 10: %d (esperado 0)\n", removeValorAbb(&r, 10));

    printf("\n== 1. insercao e percursos\n");
    for(i = 0; i < 10; i++) insereAbb(&r, v[i]);
    /*          50
             /      \
           30        70
          /  \      /  \
        20    40  60    80
             /  \   \
           35   45   65      */
    printf("  pos: "); posOrdemAbb(r); printf("  (esperado 20 35 45 40 30 65 60 80 70 50 )\n");
    imprimePreEm(r, "50 30 20 40 35 45 70 60 65 80 ", "20 30 35 40 45 50 60 65 70 80 ");

    printf("\n== 2. altura, tamanho, min/max, busca\n");
    printf("altura: %d (esperado 4)\n", alturaAbb(r));
    printf("tamanho: %d (esperado 10)\n", tamanhoAbb(r));
    imprimeNo("minimo:", minimoAbb(r), "20");
    imprimeNo("maximo:", maximoAbb(r), "80");
    imprimeNo("busca 45:", buscaAbb(r, 45), "45");
    imprimeNo("busca 99:", buscaAbb(r, 99), "NULL");

    printf("\n== 3. removeValorAbb\n");
    printf("remove 99 (nao existe): %d (esperado 0)\n", removeValorAbb(&r, 99));
    printf("remove 20 (folha): %d (esperado 1)\n", removeValorAbb(&r, 20));
    imprimePreEm(r, "50 30 40 35 45 70 60 65 80 ", "30 35 40 45 50 60 65 70 80 ");
    printf("remove 60 (so filho dir): %d (esperado 1)\n", removeValorAbb(&r, 60));
    imprimePreEm(r, "50 30 40 35 45 70 65 80 ", "30 35 40 45 50 65 70 80 ");
    printf("remove 30 (so filho dir): %d (esperado 1)\n", removeValorAbb(&r, 30));
    imprimePreEm(r, "50 40 35 45 70 65 80 ", "35 40 45 50 65 70 80 ");
    // raiz com 2 filhos: sucessor = 65 (menor da subarvore direita)
    printf("remove 50 (raiz, 2 filhos): %d (esperado 1)\n", removeValorAbb(&r, 50));
    imprimePreEm(r, "65 40 35 45 70 80 ", "35 40 45 65 70 80 ");
    // sucessor (45) e o filho direito direto: pai->dir que deve ser religado
    printf("remove 40 (2 filhos, sucessor e filho dir): %d (esperado 1)\n", removeValorAbb(&r, 40));
    imprimePreEm(r, "65 45 35 70 80 ", "35 45 65 70 80 ");

    printf("\n== 4. repetidos (iguais vao para a direita)\n");
    insereAbb(&r, 70);   // vira filho esquerdo do 80
    imprimePreEm(r, "65 45 35 70 80 70 ", "35 45 65 70 70 80 ");
    printf("remove 70: %d (esperado 1)\n", removeValorAbb(&r, 70));
    imprimePreEm(r, "65 45 35 80 70 ", "35 45 65 70 80 ");
    printf("altura: %d (esperado 3)\n", alturaAbb(r));
    printf("tamanho: %d (esperado 5)\n", tamanhoAbb(r));

    printf("\n== 5. liberaAbb\n");
    liberaAbb(&r);
    printf("r == NULL: %d (esperado 1)\n", r == NULL);
    printf("vazia: %d (esperado 1)\n", vaziaAbb(r));
    printf("tamanho: %d (esperado 0)\n", tamanhoAbb(r));
    liberaAbb(&r);   // liberar arvore vazia nao pode quebrar
    printf("libera de novo: ok\n");
    return 0;
}
