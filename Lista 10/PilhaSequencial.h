#ifndef PILHA_SEQUENCIAL_H
#define PILHA_SEQUENCIAL_H

#ifndef ED1_STRUCT_ALUNO_DEFINIDA
#define ED1_STRUCT_ALUNO_DEFINIDA
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};
#endif

typedef struct pilha Pilha;

Pilha* cria_Pilha(int capacidade);

void libera_Pilha(Pilha* pi);

int tamanho_Pilha(Pilha* pi);

int Pilha_cheia(Pilha* pi);

int Pilha_vazia(Pilha* pi);

int insere_Pilha(Pilha* pi, struct aluno al);

int remove_Pilha(Pilha* pi);

int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
#endif
