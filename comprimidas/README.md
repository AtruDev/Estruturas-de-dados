# Estruturas comprimidas (beecrowd)

Mesmas estruturas de `../pilha.h` e `../fila.h`, com a mesma API (nomes de
funcoes e tipos identicos), so que em formato compacto para **colar direto no
topo do arquivo** — o beecrowd aceita apenas um arquivo, entao `#include "pilha.h"`
nao funciona la.

## Como usar

1. Cole o conteudo do `.h` (sem o `#ifndef/#endif`, se quiser) logo abaixo dos
   seus includes.
2. Escreva o `main` normalmente.

```c
#include <stdio.h>
#define MAX_PILHA 100000   /* opcional: antes de colar a pilha */
/* ... cole aqui o conteudo de pilha.h ... */

int main(void) {
    tp_pilha p;
    inicializarPilha(&p);
    ...
}
```

## Diferencas em relacao aos originais

- `MAX_PILHA` / `MAX_FILA` agora usam `#ifndef`, entao da para sobrescrever o
  tamanho antes de colar (padrao 1005 nos dois).
- `tp_item` fica protegido por `TP_ITEM`, permitindo colar pilha e fila juntas.
- Comparacoes retornam direto (`return p->topo == -1;`) em vez de `if/else`.

Comportamento e o mesmo dos originais. A fila continua circular, ou seja,
guarda no maximo `MAX_FILA - 1` elementos.

## Estruturas dinamicas (listase, listade, pilhaDin, filaDin)

Mesma API dos originais em `../`. Cada arquivo e autossuficiente:

| Arquivo | Contem |
|---|---|
| `listase.h` | lista simplesmente encadeada |
| `listade.h` | lista duplamente encadeada |
| `pilhaDin.h` | pilha dinamica **+ listase embutida** |
| `filaDin.h` | fila dinamica **+ listade embutida** |

- Para a pilha ou a fila dinamica, cole **so** o `pilhaDin.h`/`filaDin.h`: a lista
  que ela usa ja vem junto. Se a lista ja tiver sido colada antes, o
  `#ifndef LISTA_SE`/`LISTA_DE` pula a copia repetida.
- As structs internas viraram `no_se` e `no_de` (antes as duas eram `struct no`),
  entao da para colar **todas juntas** no mesmo arquivo sem erro de redefinicao.
  Os nomes de tipo (`tp_lista`, `tp_listade`, ...) nao mudaram.
- `destruirNosImparListase` ficou de fora porque ainda esta incompleta no original.
