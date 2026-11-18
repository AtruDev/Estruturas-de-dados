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
| `abb.h` | Arvore binaria de busca (ABB) | nos dinamicos com `esq` e `dir` |
| `avl.h` | Arvore AVL (ABB balanceada) | nos dinamicos com `esq`, `dir` e `alt` |
| `trie.h` | Arvore Trie (palavras `a`-`z`) | nos dinamicos com 26 filhos |
| `exercicios/` | Testes das listas de exercicios (um `.c` por estrutura) | ver abaixo |
| `comprimidas/` | Todas as acima em formato compacto para o beecrowd | ver [README](comprimidas/README.md) |

Todas (menos a `trie.h`, que guarda palavras) usam `typedef int tp_item;` — para trocar o tipo armazenado, basta alterar
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

### `abb.h`

```c
tp_arvore *inicializarAbb(void);                 /* arvore vazia = NULL */
int  vaziaAbb(tp_arvore *r);
int  insereAbb(tp_arvore **r, tp_item e);        /* iterativo; 0 se faltar memoria */
tp_arvore *buscaAbb(tp_arvore *r, tp_item e);    /* NULL se nao achar */
void preOrdemAbb(tp_arvore *r);                  /* raiz, esq, dir */
void emOrdemAbb(tp_arvore *r);                   /* esq, raiz, dir: imprime em ordem crescente */
void posOrdemAbb(tp_arvore *r);                  /* esq, dir, raiz */
int  alturaAbb(tp_arvore *r);                    /* numero de niveis: vazia = 0, folha = 1 */
int  tamanhoAbb(tp_arvore *r);                   /* quantidade de nos */
tp_arvore *minimoAbb(tp_arvore *r);              /* NULL se vazia */
tp_arvore *maximoAbb(tp_arvore *r);              /* NULL se vazia */
int  removeValorAbb(tp_arvore **r, tp_item e);   /* remove 1 ocorrencia; 0 se nao achar */
void liberaNoAbb(tp_arvore *r);                  /* auxiliar da liberaAbb */
void liberaAbb(tp_arvore **r);                   /* libera todos os nos; *r = NULL */
int  buscaInfixa(char *infixa, int esq, int dir, tp_item dado);  /* posicao em infixa[esq..dir]; -1 se nao achar */
tp_arvore *montaArvore(char prefixa[], char infixa[], int esq, int dir);  /* reconstroi pelos percursos */
tp_arvore *montaArvoreAux(char prefixa[], char infixa[], int esq, int dir, int *pos);  /* auxiliar */
```

Valores menores vao para a esquerda; valores iguais ou maiores vao para a
direita, entao elementos repetidos sao aceitos. Na remocao de um no com 2
filhos, o valor dele e trocado pelo do sucessor (menor da subarvore direita) e
o sucessor e removido.

`montaArvore` reconstroi a arvore a partir dos percursos prefixo e infixo
(chamar com `esq = 0` e `dir = tamanho - 1`; elementos sem repeticao). O
primeiro da prefixa e a raiz; na infixa, o que vem antes dela forma a
subarvore esquerda e o que vem depois, a direita. Os dados ficam com o codigo
do `char`, entao imprima com `%c`. Ex.: prefixa `DBACEGF` + infixa `ABCDEFG`
da a pos-ordem `ACBFGED`.

Complexidade: busca, insercao e remocao sao O(h), onde h e a altura — O(log n)
com a arvore balanceada, O(n) no pior caso (inserir em ordem vira uma lista).
Percursos, altura, tamanho e liberacao visitam todos os nos: O(n).

### `avl.h`

```c
tp_avl *inicializarAvl(void);                    /* arvore vazia = NULL */
int  vaziaAvl(tp_avl *r);
int  insereAvl(tp_avl **r, tp_item e);           /* recursivo; 0 se repetido ou faltar memoria */
tp_avl *buscaAvl(tp_avl *r, tp_item e);          /* NULL se nao achar */
void preOrdemAvl(tp_avl *r);
void emOrdemAvl(tp_avl *r);
void posOrdemAvl(tp_avl *r);
int  alturaAvl(tp_avl *r);                       /* O(1), guardada no no: vazia = 0, folha = 1 */
int  tamanhoAvl(tp_avl *r);
tp_avl *minimoAvl(tp_avl *r);                    /* NULL se vazia */
tp_avl *maximoAvl(tp_avl *r);                    /* NULL se vazia */
int  removeValorAvl(tp_avl **r, tp_item e);      /* 0 se nao achar */
void liberaNoAvl(tp_avl *r);                     /* auxiliar da liberaAvl */
void liberaAvl(tp_avl **r);                      /* libera todos os nos; *r = NULL */

/* auxiliares do balanceamento */
void atualizaAlturaAvl(tp_avl *r);
int  fatorBalanceamentoAvl(tp_avl *r);           /* altura(esq) - altura(dir) */
void rotacaoLLAvl(tp_avl **r);                   /* simples a direita */
void rotacaoRRAvl(tp_avl **r);                   /* simples a esquerda */
void rotacaoLRAvl(tp_avl **r);                   /* dupla: RR no filho esq + LL */
void rotacaoRLAvl(tp_avl **r);                   /* dupla: LL no filho dir + RR */
void balanceiaAvl(tp_avl **r);                   /* atualiza altura e rotaciona se |fb| > 1 */
```

Diferente da ABB, a AVL **nao aceita valores repetidos**. Depois de cada
insercao ou remocao, a `balanceiaAvl` e chamada em todos os nos do caminho de
volta ate a raiz, mantendo |fator de balanceamento| <= 1. Com isso a altura
fica sempre O(log n), e busca, insercao e remocao sao O(log n) no pior caso.

`abb.h` e `avl.h` nao podem ser incluidas juntas nas versoes completas (as duas
definem `tp_item`); as de `comprimidas/` podem.

### `trie.h`

```c
tp_trie *inicializarTrie(void);                  /* trie vazia = NULL */
int  vaziaTrie(tp_trie *r);
int  insereTrie(tp_trie **r, char *palavra);     /* 0 se ja existir, tiver char fora de a-z ou faltar memoria */
int  buscaTrie(tp_trie *r, char *palavra);       /* 1 se a palavra existir */
int  prefixoTrie(tp_trie *r, char *prefixo);     /* 1 se alguma palavra comecar com o prefixo */
int  tamanhoTrie(tp_trie *r);                    /* quantidade de palavras */
void imprimeTrie(tp_trie *r);                    /* palavras em ordem alfabetica, uma por linha */
int  removeTrie(tp_trie **r, char *palavra);     /* 0 se nao achar; apaga os nos que sobrarem */
void liberaNoTrie(tp_trie *r);                   /* auxiliar da liberaTrie */
void liberaTrie(tp_trie **r);                    /* libera todos os nos; *r = NULL */

/* auxiliares */
int  indiceTrie(char c);                         /* 'a'..'z' -> 0..25; -1 se invalido */
tp_trie *criaNoTrie(char letra);
int  semFilhosTrie(tp_trie *no);
tp_trie *caminhoTrie(tp_trie *r, char *s);       /* no onde termina o caminho de s; NULL se nao existir */
void imprimeNoTrie(tp_trie *no, char *buf, int nivel);  /* auxiliar da imprimeTrie */
```

Aceita so letras minusculas (`LETRAS` = 26). Cada no marca com `fim = 1` se
uma palavra termina nele. A raiz e criada na primeira insercao; na remocao, os
nos que ficam sem filhos e sem fim de palavra sao liberados (inclusive a raiz,
entao a trie volta a ser `NULL` quando esvazia). `MAX_PALAVRA` (padrao 100)
limita o tamanho das palavras so na `imprimeTrie` e pode ser definido antes do
include.

Complexidade: insercao, busca, prefixo e remocao sao O(m), onde m e o tamanho
da palavra, independente de quantas palavras a trie tem.

## Exercicios

A pasta `exercicios/` tem um programa de teste para cada lista de exercicios.
Cada um imprime o resultado ao lado do valor esperado.

| Arquivo | Exercicios |
|---|---|
| `ex_listase.c` | `inverteListase`, `intercalaListase` |
| `ex_listade.c` | `ehPalindromoListade`, `trocaNosListade` |
| `ex_pilhadin.c` | `balanceado`, `ordenaPilhadin` |
| `ex_filadin.c` | `josephus`, `inverteKFiladin` (definida no proprio arquivo, usa pilha + fila) |
| `ex_abb.c` | `alturaAbb`, `tamanhoAbb`, `minimoAbb`, `maximoAbb`, `removeValorAbb`, `liberaAbb` |

Compilar de dentro de `exercicios/`: `gcc ex_listase.c -o ex_listase`
