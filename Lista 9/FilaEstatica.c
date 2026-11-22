#include <stdio.h>
#include <stdlib.h>
#include "FilaEstatica.h"

struct fila {
    int inicio, final, qtd;
    int capacidade;
    struct aluno *dados;
};

Fila* cria_Fila(int capacidade) {
    Fila *fi;
    if (capacidade <= 0)
        return NULL;
    fi = (Fila*) malloc(sizeof(struct fila));
    if (fi == NULL)
        return NULL;
    fi->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (fi->dados == NULL) {
        free(fi);
        return NULL;
    }
    fi->capacidade = capacidade;
    fi->inicio = 0;
    fi->final = 0;
    fi->qtd = 0;
    return fi;
}
void libera_Fila(Fila* fi) {
    if (fi == NULL)
        return;
    free(fi->dados);
    free(fi);
}

int tamanho_Fila(Fila* fi) {
    if (fi == NULL)
        return -1;
    return fi->qtd;
}
int Fila_cheia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == fi->capacidade);
}

int Fila_vazia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == 0);
}

int insere_Fila(Fila* fi, struct aluno al) {
    if (fi == NULL)
        return 0;
    if (Fila_cheia(fi))
        return 0;
    fi->dados[fi->final] = al;
    fi->final = (fi->final + 1) % fi->capacidade;
    fi->qtd++;
    return 1;
}
int remove_Fila(Fila* fi) {
    if (fi == NULL || Fila_vazia(fi))
        return 0;

    fi->inicio = (fi->inicio + 1) % fi->capacidade;
    fi->qtd--;
    return 1;
}

int consulta_Fila(Fila* fi, struct aluno *al) {
    if (fi == NULL || al == NULL || Fila_vazia(fi))
        return 0;
    *al = fi->dados[fi->inicio];
    return 1;
}

int fura_Fila(Fila* fi, struct aluno al) {
    if (fi == NULL || Fila_cheia(fi))
        return 0;

    fi->inicio = (fi->inicio + fi->capacidade - 1) % fi->capacidade;
    fi->dados[fi->inicio] = al;
    fi->qtd++;
    return 1;
}
