#ifndef LISTA_DIN_ENCAD_CIRC_H
#define LISTA_DIN_ENCAD_CIRC_H

struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct elemento* Lista;

Lista* cria_lista(void);

void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int remove_lista(Lista* li, int mat);
int busca_lista_pos(Lista* li, int pos, struct aluno *al);
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

void imprime_lista(Lista* li); // Q1
int maior_matricula(Lista* li, int *mat); // Q2
int conta_aprovados(Lista* li); // Q3
int busca_ciclica(Lista* li, int k, struct aluno *al); // Q4
int remove_lista_pos(Lista* li, int pos); // Q5
int rotaciona_lista(Lista* li, int k); // Q6
int concatena_listas(Lista* li1, Lista* li2); // Q7
int josephus(Lista* li, int k, int *sobrevivente); // Q8

#endif 