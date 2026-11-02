#ifndef LISTA_DIN_ENCAD_DUPLA_H
#define LISTA_DIN_ENCAD_DUPLA_H

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

void imprime_lista_inversa(Lista* li);
int lista_consistente(Lista* li);
int remove_lista_pos(Lista* li, int pos);
int move_para_inicio(Lista* li, int mat);
int remove_todos(Lista* li, int mat);
void inverte_lista(Lista* li);
int eh_palindromo(Lista* li);
int insere_circ_inicio(Lista* li, struct aluno al);
int insere_circ_final(Lista* li, struct aluno al);
int remove_circ_inicio(Lista* li);
int remove_circ_final(Lista* li);

#endif 