#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaSequencial.h"

struct lista {
    int qtd;
    struct produto dados[MAX];
};

Lista* cria_lista(void) {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li) {
    free(li);
}

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
}

int insere_lista_inicio(Lista* li, struct produto p) {
    int i;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)
        return 0;

    for (i = li->qtd - 1; i >= 0; i--)
        li->dados[i + 1] = li->dados[i];
    li->dados[0] = p;
    li->qtd++;
    return 1;
}

int insere_lista_final(Lista* li, struct produto p) {
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)
        return 0;
    li->dados[li->qtd] = p;
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct produto p) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)
        return 0;

    while (i < li->qtd && li->dados[i].codigo < p.codigo)
        i++;

    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

int remove_lista_inicio(Lista* li) {
    int k;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;

    for (k = 0; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;
    li->qtd--;
    return 1;
}

int remove_lista(Lista* li, int cod) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)
        return 0;
    for (k = i; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_otimizado(Lista* li, int cod) {
    int i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)
        return 0;
    li->qtd--;
    li->dados[i] = li->dados[li->qtd];
    return 1;
}

int busca_lista_pos(Lista* li, int pos, struct produto *p) {
    if (li == NULL || p == NULL || pos <= 0 || pos > li->qtd)
        return 0;
    *p = li->dados[pos - 1];
    return 1;
}

int busca_lista_cod(Lista* li, int cod, struct produto *p) {
    int i = 0;
    if (li == NULL || p == NULL)
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)
        return 0;
    *p = li->dados[i];
    return 1;
}
/* Q1 */
int lista_tem_espaco(Lista* li, int n) {
    if (li == NULL || n < 0)
        return 0;
    return (n <= MAX - li->qtd);
}

/* Q2 */
float soma_precos(Lista* li) {
    int i;
    float soma = 0;
    if (li == NULL)
        return 0;
    for (i = 0; i < li->qtd; i++)
        soma += li->dados[i].preco;
    return soma;
}

/* Q3 */
int busca_por_nome(Lista* li, char *nome, struct produto *p) {
    int i = 0;
    if (li == NULL || nome == NULL || p == NULL)
        return 0;
    while (i < li->qtd && strcmp(li->dados[i].nome, nome) != 0)
        i++;
    if (i == li->qtd)
        return 0;
    *p = li->dados[i];
    return 1;
}

/* Q4 */
int insere_lista_decrescente(Lista* li, struct produto p) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)
        return 0;
    while (i < li->qtd && li->dados[i].preco >= p.preco)
        i++;
    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

/* Q5 */
int remove_mais_caro(Lista* li, struct produto *removido) {
    int i, imax = 0;
    if (li == NULL || removido == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;
    for (i = 1; i < li->qtd; i++)
        if (li->dados[i].preco > li->dados[imax].preco)
            imax = i;
    *removido = li->dados[imax];
    li->qtd--;
    li->dados[imax] = li->dados[li->qtd];
    return 1;
}

/* Q6 */
int conta_faixa_preco(Lista* li, float min, float max) {
    int i, cont = 0;
    if (li == NULL)
        return 0;
    for (i = 0; i < li->qtd; i++)
        if (li->dados[i].preco >= min && li->dados[i].preco <= max)
            cont++;
    return cont;
}

/* Q7 */
int remove_abaixo_de(Lista* li, float precoMinimo) {
    int i = 0, removidos = 0;
    if (li == NULL)
        return 0;
    while (i < li->qtd) {
        if (li->dados[i].preco < precoMinimo) {
            li->qtd--;
            li->dados[i] = li->dados[li->qtd];
            removidos++;
        } else {
            i++;
        }
    }
    return removidos;
}

/* Q8 */
int mescla_listas(Lista* destino, Lista* origem) {
    int i, j, existe, inseridos = 0;
    if (destino == NULL || origem == NULL)
        return 0;
    for (i = 0; i < origem->qtd; i++) {
        if (destino->qtd == MAX)
            break;
        existe = 0;
        for (j = 0; j < destino->qtd && !existe; j++)
            if (destino->dados[j].codigo == origem->dados[i].codigo)
                existe = 1;
        if (!existe) {
            destino->dados[destino->qtd] = origem->dados[i];
            destino->qtd++;
            inseridos++;
        }
    }
    return inseridos;
}