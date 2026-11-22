#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

#ifndef ED1_STRUCT_ALUNO_DEFINIDA
#define ED1_STRUCT_ALUNO_DEFINIDA
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};
#endif

typedef struct fila Fila;

Fila* cria_Fila(int capacidade);

void libera_Fila(Fila* fi);

int tamanho_Fila(Fila* fi);

int Fila_cheia(Fila* fi);

int Fila_vazia(Fila* fi);

int insere_Fila(Fila* fi, struct aluno al);

int remove_Fila(Fila* fi);

int consulta_Fila(Fila* fi, struct aluno *al);

int fura_Fila(Fila* fi, struct aluno al);

#endif
