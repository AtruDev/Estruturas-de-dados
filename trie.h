#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>

#define LETRAS 26          // so letras minusculas 'a'..'z'
#ifndef MAX_PALAVRA
#define MAX_PALAVRA 100    // tamanho maximo de palavra na imprimeTrie
#endif

typedef struct no_trie {
    char letra;                       // letra que leva a este no ('\0' na raiz)
    int fim;                          // 1 se alguma palavra termina aqui
    struct no_trie *filhos[LETRAS];
} tp_trie;

tp_trie *inicializarTrie(){return NULL;}

int vaziaTrie(tp_trie *r){return r == NULL;}

// Posicao da letra no vetor de filhos; -1 se nao for 'a'..'z'
int indiceTrie(char c){
    if(c < 'a' || c > 'z') return -1;
    return c - 'a';
}

tp_trie *criaNoTrie(char letra){
    tp_trie *no = malloc(sizeof(tp_trie));
    int i;
    if(no == NULL) return NULL;
    no->letra = letra;
    no->fim = 0;
    for(i = 0; i < LETRAS; i++) no->filhos[i] = NULL;
    return no;
}

int semFilhosTrie(tp_trie *no){
    int i;
    for(i = 0; i < LETRAS; i++) if(no->filhos[i] != NULL) return 0;
    return 1;
}

// Cria a raiz na primeira insercao.
// 0 se a palavra tiver caractere fora de 'a'..'z', se ja existir ou se faltar memoria.
int insereTrie(tp_trie **r, char *palavra){
    int i, ind;
    for(i = 0; palavra[i] != '\0'; i++){
        if(indiceTrie(palavra[i]) == -1) return 0;
    }
    if(*r == NULL){
        *r = criaNoTrie('\0');
        if(*r == NULL) return 0;
    }
    tp_trie *atu = *r;
    for(i = 0; palavra[i] != '\0'; i++){
        ind = indiceTrie(palavra[i]);
        if(atu->filhos[ind] == NULL){
            atu->filhos[ind] = criaNoTrie(palavra[i]);
            if(atu->filhos[ind] == NULL) return 0;
        }
        atu = atu->filhos[ind];
    }
    if(atu->fim) return 0; // ja existia
    atu->fim = 1;
    return 1;
}

// No onde termina o caminho de s; NULL se o caminho nao existir
tp_trie *caminhoTrie(tp_trie *r, char *s){
    tp_trie *atu = r;
    int i, ind;
    for(i = 0; atu != NULL && s[i] != '\0'; i++){
        ind = indiceTrie(s[i]);
        if(ind == -1) return NULL;
        atu = atu->filhos[ind];
    }
    return atu;
}

// 1 se a palavra estiver na trie
int buscaTrie(tp_trie *r, char *palavra){
    tp_trie *no = caminhoTrie(r, palavra);
    return no != NULL && no->fim;
}

// 1 se alguma palavra da trie comecar com o prefixo
int prefixoTrie(tp_trie *r, char *prefixo){
    return caminhoTrie(r, prefixo) != NULL;
}

// Quantidade de palavras
int tamanhoTrie(tp_trie *r){
    int i, total;
    if(r == NULL) return 0;
    total = r->fim;
    for(i = 0; i < LETRAS; i++) total += tamanhoTrie(r->filhos[i]);
    return total;
}

//funcao auxiliar a imprimeTrie
void imprimeNoTrie(tp_trie *no, char *buf, int nivel){
    int i;
    if(no == NULL) return;
    if(no->fim){
        buf[nivel] = '\0';
        printf("%s\n", buf);
    }
    if(nivel >= MAX_PALAVRA - 1) return;
    for(i = 0; i < LETRAS; i++){
        if(no->filhos[i] != NULL){
            buf[nivel] = no->filhos[i]->letra;
            imprimeNoTrie(no->filhos[i], buf, nivel + 1);
        }
    }
}

// Imprime as palavras em ordem alfabetica, uma por linha
void imprimeTrie(tp_trie *r){
    char buf[MAX_PALAVRA];
    if(r == NULL){
        printf("Trie vazia\n");
        return;
    }
    imprimeNoTrie(r, buf, 0);
}

// Remove a palavra; 0 se nao achar.
// Na volta da recursao apaga os nos que ficaram sem filhos e sem fim de palavra
// (se a trie esvaziar, a raiz tambem e liberada e *r = NULL).
int removeTrie(tp_trie **r, char *palavra){
    int res, ind;
    if(*r == NULL) return 0;
    if(*palavra == '\0'){
        if(!(*r)->fim) return 0;
        (*r)->fim = 0;
        res = 1;
    } else {
        ind = indiceTrie(*palavra);
        if(ind == -1) return 0;
        res = removeTrie(&(*r)->filhos[ind], palavra + 1);
    }
    if(res && !(*r)->fim && semFilhosTrie(*r)){
        free(*r);
        *r = NULL;
    }
    return res;
}

//funcao auxiliar a liberaTrie
void liberaNoTrie(tp_trie *r){
    int i;
    if(r == NULL) return;
    for(i = 0; i < LETRAS; i++) liberaNoTrie(r->filhos[i]);
    free(r);
}

void liberaTrie(tp_trie **r){
    liberaNoTrie(*r);
    *r = NULL;
}

#endif
