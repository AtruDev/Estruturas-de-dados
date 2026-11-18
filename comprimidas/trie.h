#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>
#include <stdlib.h>
#define LETRAS 26
#ifndef MAX_PALAVRA
#define MAX_PALAVRA 100
#endif
typedef struct no_trie { char letra; int fim; struct no_trie *filhos[LETRAS]; } tp_trie;
tp_trie *inicializarTrie() { return NULL; }
int vaziaTrie(tp_trie *r) { return r == NULL; }
int indiceTrie(char c) { return (c < 'a' || c > 'z') ? -1 : c - 'a'; }
tp_trie *criaNoTrie(char letra) { tp_trie *n = malloc(sizeof(tp_trie)); int i; if (!n) return NULL; n->letra = letra; n->fim = 0; for (i = 0; i < LETRAS; i++) n->filhos[i] = NULL; return n; }
int semFilhosTrie(tp_trie *n) { int i; for (i = 0; i < LETRAS; i++) if (n->filhos[i]) return 0; return 1; }
int insereTrie(tp_trie **r, char *p) { int i, k; tp_trie *a; for (i = 0; p[i]; i++) if (indiceTrie(p[i]) == -1) return 0; if (!*r && !(*r = criaNoTrie('\0'))) return 0; for (a = *r, i = 0; p[i]; i++) { k = indiceTrie(p[i]); if (!a->filhos[k] && !(a->filhos[k] = criaNoTrie(p[i]))) return 0; a = a->filhos[k]; } if (a->fim) return 0; return a->fim = 1; }
tp_trie *caminhoTrie(tp_trie *r, char *s) { int k; for (; r && *s; s++) { if ((k = indiceTrie(*s)) == -1) return NULL; r = r->filhos[k]; } return r; }
int buscaTrie(tp_trie *r, char *p) { tp_trie *n = caminhoTrie(r, p); return n != NULL && n->fim; }
int prefixoTrie(tp_trie *r, char *p) { return caminhoTrie(r, p) != NULL; }
int tamanhoTrie(tp_trie *r) { int i, t; if (!r) return 0; t = r->fim; for (i = 0; i < LETRAS; i++) t += tamanhoTrie(r->filhos[i]); return t; }
void imprimeNoTrie(tp_trie *n, char *b, int k) { int i; if (!n) return; if (n->fim) { b[k] = '\0'; printf("%s\n", b); } if (k >= MAX_PALAVRA - 1) return; for (i = 0; i < LETRAS; i++) if (n->filhos[i]) { b[k] = n->filhos[i]->letra; imprimeNoTrie(n->filhos[i], b, k + 1); } }
void imprimeTrie(tp_trie *r) { char b[MAX_PALAVRA]; if (!r) { printf("Trie vazia\n"); return; } imprimeNoTrie(r, b, 0); }
int removeTrie(tp_trie **r, char *p) { int res, k; if (!*r) return 0; if (!*p) { if (!(*r)->fim) return 0; (*r)->fim = 0; res = 1; } else { if ((k = indiceTrie(*p)) == -1) return 0; res = removeTrie(&(*r)->filhos[k], p + 1); } if (res && !(*r)->fim && semFilhosTrie(*r)) { free(*r); *r = NULL; } return res; }
void liberaNoTrie(tp_trie *r) { int i; if (!r) return; for (i = 0; i < LETRAS; i++) liberaNoTrie(r->filhos[i]); free(r); }
void liberaTrie(tp_trie **r) { liberaNoTrie(*r); *r = NULL; }
#endif
