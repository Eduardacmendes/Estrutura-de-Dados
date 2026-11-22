#include <stdio.h>
#include <stdlib.h>
#include "PilhaChar.h"

struct pilha_char {
    int qtd;
    int capacidade;
    char *dados;
};

PilhaChar* cria_PilhaChar(int capacidade) {
    PilhaChar *pi;
    if (capacidade <= 0)
        return NULL;
    pi = (PilhaChar*) malloc(sizeof(struct pilha_char));
    if (pi == NULL)
        return NULL;
    pi->dados = (char*) malloc(capacidade * sizeof(char));
    if (pi->dados == NULL) {
        free(pi);
        return NULL;
    }
    pi->capacidade = capacidade;
    pi->qtd = 0;
    return pi;
}
void libera_PilhaChar(PilhaChar* pi) {
    if (pi == NULL)
        return;
    free(pi->dados);
    free(pi);
}

int tamanho_PilhaChar(PilhaChar* pi) {
    if (pi == NULL)
        return -1;
    return pi->qtd;
}
int PilhaChar_cheia(PilhaChar* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == pi->capacidade);
}
int PilhaChar_vazia(PilhaChar* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == 0);
}

int insere_PilhaChar(PilhaChar* pi, char c) {
    if (pi == NULL)
        return 0;
    if (PilhaChar_cheia(pi))
        return 0;
    pi->dados[pi->qtd] = c;
    pi->qtd++;
    return 1;
}
int remove_PilhaChar(PilhaChar* pi) {
    if (pi == NULL || PilhaChar_vazia(pi))
        return 0;
    pi->qtd--;
    return 1;
}

int consulta_topo_PilhaChar(PilhaChar* pi, char *c) {
    if (pi == NULL || c == NULL || PilhaChar_vazia(pi))
        return 0;
    *c = pi->dados[pi->qtd - 1];
    return 1;
}
