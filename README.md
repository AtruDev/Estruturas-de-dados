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
| `listade.h` | Lista duplamente encadeada | nos dinamicos com `ant` e `prox` |
| `pilhaDin.h` | Pilha dinamica (LIFO) | sobre `listase.h` |
| `filaDin.h` | Fila dinamica (FIFO) | sobre `listade.h` |
| `exercicios/` | Testes das listas de exercicios (um `.c` por estrutura) | ver abaixo |
| `comprimidas/` | Todas as acima em formato compacto para o beecrowd | ver [README](comprimidas/README.md) |

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
int  removeValorListase(tp_lista **l, tp_item e);  /* remove a 1a ocorrencia; 0 se nao achar */
int  destruirNosImparListase(tp_lista **l);        /* remove os nos de valor impar; retorna quantos */
void inverteListase(tp_lista **l);                 /* inverte trocando os ponteiros */
tp_lista *intercalaListase(tp_lista *l1, tp_lista *l2); /* nova lista ordenada; originais intactas */
tp_lista *buscaListase(tp_lista *l, tp_item e);   /* NULL se nao achar */
int  tamanhoListase(tp_lista *l);
int  maiorQueListase(tp_lista *l, tp_item x);     /* quantos elementos > x */
int  listasIdenticasListase(tp_lista *l1, tp_lista *l2);
void imprimeListase(tp_lista *l);
int  liberaListase(tp_lista **l);                 /* libera todos os nos */
```

As funcoes que alteram o inicio da lista recebem `tp_lista **` porque podem
mudar o ponteiro de cabeca.

### `listade.h`

```c
tp_listade *inicializarListade(void);
int  vaziaListade(tp_listade *l);
int  insereIniciode(tp_listade **l, tp_item e);
int  insereFimde(tp_listade **l, tp_item e);
int  inseriOrdenadoListade(tp_listade **l, tp_item e);
int  removeiniListade(tp_listade **l, tp_item *e);
int  removefimListade(tp_listade **l, tp_item *e);
int  removeValorListade(tp_listade **l, tp_item e);  /* 0 se nao achar */
tp_listade *buscaListade(tp_listade *l, tp_item e);  /* NULL se nao achar */
int  tamanhoListade(tp_listade *l);
int  maiorQueListade(tp_listade *l, tp_item x);
int  listasIdenticasListade(tp_listade *l1, tp_listade *l2);
void imprimeListade(tp_listade *l);
void imprimeInversoListade(tp_listade *l);
int  liberaListade(tp_listade **l);
int  ehPalindromoListade(tp_listade *l);
int  trocaNosListade(tp_listade **l, tp_item a, tp_item b);  /* religa os nos; 0 se algum nao existir */
```

`listase.h` e `listade.h` nao podem ser incluidas juntas nas versoes
completas (as duas definem `struct no` e `tp_item`). As versoes de
`comprimidas/` resolvem isso.

### `pilhaDin.h`

```c
tp_pilhadin *inicializarPilhadin(void);
int  vaziaPilhadin(tp_pilhadin *p);
int  pushPilhadin(tp_pilhadin **p, tp_item e);
int  popPilhadin(tp_pilhadin **p, tp_item *e);    /* 0 se vazia */
int  topPilhadin(tp_pilhadin *p, tp_item *e);     /* 0 se vazia */
int  tamanhoPilhadin(tp_pilhadin *p);
void imprimePilhadin(tp_pilhadin *p);
int  liberaPilhadin(tp_pilhadin **p);
void ordenaPilhadin(tp_pilhadin **p);            /* menor no topo, so 1 pilha auxiliar */
int  balanceado(char *s);                        /* (), [] e {} balanceados */
```

### `filaDin.h`

```c
tp_filadin *inicializarFiladin(void);
int  vaziaFiladin(tp_filadin *f);
int  enqueueFiladin(tp_filadin **f, tp_item e);
int  dequeueFiladin(tp_filadin **f, tp_item *e);  /* 0 se vazia */
int  frontFiladin(tp_filadin *f, tp_item *e);     /* 0 se vazia */
int  tamanhoFiladin(tp_filadin *f);
void imprimeFiladin(tp_filadin *f);
int  liberaFiladin(tp_filadin **f);
int  josephus(int n, int k);                     /* imprime a ordem de eliminacao; retorna o sobrevivente */
```

## Exercicios

A pasta `exercicios/` tem um programa de teste para cada lista de exercicios.
Cada um imprime o resultado ao lado do valor esperado.

| Arquivo | Exercicios |
|---|---|
| `ex_listase.c` | `inverteListase`, `intercalaListase` |
| `ex_listade.c` | `ehPalindromoListade`, `trocaNosListade` |
| `ex_pilhadin.c` | `balanceado`, `ordenaPilhadin` |
| `ex_filadin.c` | `josephus`, `inverteKFiladin` (definida no proprio arquivo, usa pilha + fila) |

Compilar de dentro de `exercicios/`: `gcc ex_listase.c -o ex_listase`
