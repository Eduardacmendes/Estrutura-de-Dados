#include <stdio.h>
#include <stdlib.h>
#include "FilaEncadeada.h"

struct fila {
    int qtd;
    Lista *lista;
};

struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Fila* cria_Fila() {
    Fila *fi;
    fi = (Fila*) malloc(sizeof(struct fila));
    if (fi == NULL)
        return NULL;

    fi->lista = cria_lista();
    fi->qtd = 0;
    return fi;
}

void libera_Fila(Fila* fi) {
    if (fi == NULL)
        return;
    libera_lista(fi->lista);
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
    return 0;
}

int Fila_vazia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == 0);
}

int insere_Fila(Fila* fi, struct aluno al) {
    if (fi == NULL)
        return 0;
    if(!insere_lista_final(fi->lista, al))
        return 0;

    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi) {
    if (fi == NULL || fi->qtd == 0)
        return 0;

    if(!remove_lista_inicio(fi->lista))
        return 0;
    fi->qtd--;
    return 1;
}

int consulta_Fila(Fila* fi, struct aluno *al) {
    if (fi == NULL || al == NULL || fi->qtd == 0)
        return 0;
    return busca_lista_pos(fi->lista, 1, al);
}
