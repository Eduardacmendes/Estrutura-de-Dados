#ifndef PILHA_CHAR_H
#define PILHA_CHAR_H

typedef struct pilha_char PilhaChar;

PilhaChar* cria_PilhaChar(int capacidade);
void libera_PilhaChar(PilhaChar* pi);
int tamanho_PilhaChar(PilhaChar* pi);
int PilhaChar_cheia(PilhaChar* pi);
int PilhaChar_vazia(PilhaChar* pi);
int insere_PilhaChar(PilhaChar* pi, char c);
int remove_PilhaChar(PilhaChar* pi);
int consulta_topo_PilhaChar(PilhaChar* pi, char *c);
#endif
