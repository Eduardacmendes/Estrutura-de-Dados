#include <stdio.h>
#include <stdlib.h>
#include "PilhaSequencial.h"

struct pilha {
    int qtd;
    int capacidade;
    struct aluno *dados;
};

Pilha* cria_Pilha(int capacidade) {
    Pilha *pi;
    if (capacidade <= 0)
        return NULL;
    pi = (Pilha*) malloc(sizeof(struct pilha));
    if (pi == NULL)
        return NULL;
    pi->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (pi->dados == NULL) {
        free(pi);
        return NULL;
    }
    pi->capacidade = capacidade;
    pi->qtd = 0;
    return pi;
}
void libera_Pilha(Pilha* pi) {
    if (pi == NULL)
        return;
    free(pi->dados);
    free(pi);
}

int tamanho_Pilha(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return pi->qtd;
}
int Pilha_cheia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == pi->capacidade);
}

int Pilha_vazia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == 0);
}

int insere_Pilha(Pilha* pi, struct aluno al) {
    if (pi == NULL)
        return 0;
    if (Pilha_cheia(pi))
        return 0;
    pi->dados[pi->qtd] = al;
    pi->qtd++;
    return 1;
}
int remove_Pilha(Pilha* pi) {
    if (pi == NULL || Pilha_vazia(pi))
        return 0;
    pi->qtd--;
    return 1;
}

int consulta_topo_Pilha(Pilha* pi, struct aluno *al) {
    if (pi == NULL || al == NULL || Pilha_vazia(pi))
        return 0;
    *al = pi->dados[pi->qtd - 1];
    return 1;
}
