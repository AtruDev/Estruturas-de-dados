# Estruturas de Dados

Implementacoes em C de estruturas de dados feitas na disciplina de Algoritmos e
Estruturas de Dados (AED). Cada estrutura e um header unico, auto-contido
(declaracao + implementacao), pronto para `#include`.

## Conteudo

| Arquivo | Estrutura | Implementacao |
|---|---|---|
| `pilha.h` | Pilha (LIFO) | vetor estatico, `MAX_PILHA` = 100 |
| `fila.h` | Fila (FIFO) | vetor circular, `MAX_FILA` = 6 |
| `listase.h` | Lista simplesmente encadeada | nos dinamicos (`malloc`) |
| `comprimidas/` | Pilha e fila em formato compacto para o beecrowd | ver [README](comprimidas/README.md) |

Todas usam `typedef int tp_item;` — para trocar o tipo armazenado, basta alterar
esse typedef.

## Como usar

```c
#include "pilha.h"

int main(void) {
    tp_pilha p;
    tp_item e;

    inicializarPilha(&p);
    inserePilha(&p, 10);
    inserePilha(&p, 20);

    while (removePilha(&p, &e))
        printf("%d\n", e);   /* 20, 10 */

    return 0;
}
```

Compilar: `gcc main.c -o main`

## API

### `pilha.h`

```c
void inicializarPilha(tp_pilha *p);
int  vaziaPilha(tp_pilha *p);
int  cheiaPilha(tp_pilha *p);
int  inserePilha(tp_pilha *p, tp_item e);      /* 0 se cheia */
int  removePilha(tp_pilha *p, tp_item *e);     /* 0 se vazia */
int  peekPilha(tp_pilha *p, tp_item *e);       /* 0 se vazia */
int  tamanhoPilha(tp_pilha *p);
void imprimePilha(tp_pilha p);                 /* por valor: nao consome a original */
```

### `fila.h`

```c
void inicializarFila(tp_fila *f);
int  vaziaFila(tp_fila *f);
int  cheiaFila(tp_fila *f);
int  proximoFila(int pos);
int  insereFila(tp_fila *f, tp_item e);        /* 0 se cheia */
int  removeFila(tp_fila *f, tp_item *e);       /* 0 se vazia */
int  peekFila(tp_fila *f, tp_item *e);         /* 0 se vazia */
int  tamanhoFila(tp_fila f);
void imprimeFila(tp_fila f);
```

A fila e circular e reserva uma posicao como sentinela, ou seja, guarda no
maximo `MAX_FILA - 1` elementos.

### `listase.h`

```c
tp_lista *inicializarListase(void);
int  vaziaListase(tp_lista *l);
int  insereIniciose(tp_lista **l, tp_item e);
int  insereFimse(tp_lista **l, tp_item e);
int  inseriOrdenadoListase(tp_lista **l, tp_item e);
int  removeiniListase(tp_lista **l, tp_item *e);
int  removefimListase(tp_lista **l, tp_item *e);
tp_lista *buscaListase(tp_lista *l, tp_item e);   /* NULL se nao achar */
int  tamanhoListase(tp_lista *l);
int  maiorQueListase(tp_lista *l, tp_item x);     /* quantos elementos > x */
int  listasIdenticasListase(tp_lista *l1, tp_lista *l2);
void imprimeListase(tp_lista *l);
int  liberaListase(tp_lista **l);                 /* libera todos os nos */
```

As funcoes que alteram o inicio da lista recebem `tp_lista **` porque podem
mudar o ponteiro de cabeca.
