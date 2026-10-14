#include <stdio.h>
#include "listase.h"

int main(){
    tp_lista *lista;
    lista = inicializarListase();
    imprimeListase(lista);

    insereIniciose(&lista, 10);
    insereIniciose(&lista, 20);
    insereFimse(&lista, 30);
    imprimeListase(lista);

    return 0;
}