#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;


Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;   
            free(no);
        }
        free(li);                
    }
}


int tamanho_lista(Lista* li) {
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;               
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;            
    if (*li == NULL)
        return 1;            
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;    
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if (*li != NULL)             
        (*li)->ant = no;         
    *li = no;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL) {         
        no->ant = NULL;
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {         
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else {
        Elem *ante = NULL, *atual = *li;
        while (atual != NULL &&
               atual->dados.matricula < al.matricula) {
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li) {      /* insere inicio */
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else {                 /* insere no meio ou no final */
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)   /* nao e o ultimo */
                atual->ant = no;
        }
        return 1;
    }
}


int remove_lista_inicio(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    *li = no->prox;
    if (no->prox != NULL)          /* existe um seguinte */
        no->prox->ant = NULL;      /* ele passa a ser o primeiro */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no->prox != NULL)
        no = no->prox;
    if (no->ant == NULL)           /* primeiro e unico */
        *li = no->prox;
    else
        no->ant->prox = NULL;      /* penultimo obtido pelo proprio no */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)                /* chave ausente */
        return 0;
    if (no->ant == NULL)           /* remove o primeiro */
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if (no->prox != NULL)          /* nao e o ultimo */
        no->prox->ant = no->ant;
    free(no);
    return 1;
}


int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

/* Q1 - custo O(n): vai ate o fim por prox e volta por ant */
void imprime_lista_inversa(Lista* li){
    if(li == NULL || *li == NULL){
        printf("(lista vazia)\n");
        return;
    }
    Elem* no = *li;
    while(no->prox != NULL)
        no = no->prox;
    while(no != NULL){
        printf("%d ", no->dados.matricula);
        no = no->ant;
    }
    printf("\n");
}

/* Q2 - custo O(n) */
int lista_consistente(Lista* li){
    if(li == NULL) return 0;
    if(*li == NULL) return 1;
    if((*li)->ant != NULL) return 0;
    Elem* no = *li;
    while(no->prox != NULL){
        if(no->prox->ant != no) return 0;
        no = no->prox;
    }
    return 1;
}

/* Q3
   a) remove_lista(li, 33) em 33 <-> 23 <-> 16: o 33 e o primeiro, entao
      no->ant e NULL e a linha no->ant->prox = no->prox acessa NULL->prox.
      O programa quebra (segfault). Tambem nao atualiza *li.
   b) remove_lista(li, 23): 33->prox passa a ser 16, mas 16->ant continua
      apontando pro 23, que foi liberado. Fica:
        33: ant = NULL, prox = 16
        16: ant = (23 liberado), prox = NULL
      tamanho_lista so anda por prox, entao conta 2 (certo).
      lista_consistente confere 33->prox->ant == 33 e isso da falso
      (16->ant nao e o 33), entao devolve 0.
   c) versao corrigida */
int remove_lista_corrigida(Lista* li, int mat){
    if(li == NULL) return 0;
    if(*li == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;
    if(no->ant == NULL)
        *li = no->prox;          /* era o primeiro */
    else
        no->ant->prox = no->prox;
    if(no->prox != NULL)         /* nao era o ultimo */
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/* Q4 - custo O(pos), no pior caso O(n). Remover o primeiro e O(1),
   o ultimo precisa andar a lista toda. */
int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || *li == NULL || pos < 1) return 0;
    Elem* no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL) return 0;
    if(no->ant == NULL)
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if(no->prox != NULL)
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/* Q5
   no meio: escreve 5 campos (no->ant->prox, no->prox->ant, no->ant,
   no->prox e (*li)->ant), fora o *li que tambem muda.
   no ultimo: 4 campos, porque no->prox e NULL e o no->prox->ant nao e escrito.
   se ja e o primeiro, nao escreve nada. */
int move_para_inicio(Lista* li, int mat){
    if(li == NULL || *li == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;
    if(no == *li) return 1;
    /* tira da posicao atual */
    no->ant->prox = no->prox;
    if(no->prox != NULL)
        no->prox->ant = no->ant;
    /* poe no comeco */
    no->ant = NULL;
    no->prox = *li;
    (*li)->ant = no;
    *li = no;
    return 1;
}

/* Q6 - uma passada so. Guarda o prox antes do free, senao
   perde o resto da lista. */
int remove_todos(Lista* li, int mat){
    if(li == NULL || *li == NULL) return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        Elem* prox = no->prox;
        if(no->dados.matricula == mat){
            if(no->ant == NULL)
                *li = no->prox;
            else
                no->ant->prox = no->prox;
            if(no->prox != NULL)
                no->prox->ant = no->ant;
            free(no);
            cont++;
        }
        no = prox;
    }
    return cont;
}

/* Q7 - custo O(n), sem alocar nada.
   Cada no troca ant e prox. Como a troca vale pra todos, se A->prox era B
   e B->ant era A, depois da troca A->ant e B e B->prox e A, entao a lista
   continua consistente. O primeiro (ant NULL) vira ultimo (prox NULL) e o
   ultimo vira o primeiro, por isso so falta atualizar o *li. */
void inverte_lista(Lista* li){
    if(li == NULL || *li == NULL) return;
    Elem* no = *li;
    Elem* ultimo = NULL;
    while(no != NULL){
        Elem* prox = no->prox;
        no->prox = no->ant;
        no->ant = prox;
        ultimo = no;
        no = prox;
    }
    *li = ultimo;
}

/* Q8 - custo O(n) (so n/2 comparacoes, mais n pra achar o fim).
   Parada: i != j e j->prox != i.
   - tamanho impar: i e j se encontram no meio (i == j)
   - tamanho par: eles se cruzam (j->prox == i)
   Na lista simples nao tem ant, entao nao da pra voltar com o ponteiro
   do fim; teria que percorrer desde o inicio a cada passo (O(n^2))
   ou usar vetor auxiliar. */
int eh_palindromo(Lista* li){
    if(li == NULL) return 0;
    if(*li == NULL) return 1;
    Elem* i = *li;
    Elem* j = *li;
    while(j->prox != NULL)
        j = j->prox;
    while(i != j && j->prox != i){
        if(i->dados.matricula != j->dados.matricula)
            return 0;
        i = i->prox;
        j = j->ant;
    }
    return 1;
}

/* Extra - lista circular. O ultimo e (*li)->ant, entao inserir no final
   e O(1) (na biblioteca normal insere_lista_final e O(n)). */
int insere_circ_inicio(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = al;
    if(*li == NULL){
        no->prox = no;
        no->ant = no;
    } else {
        Elem* ultimo = (*li)->ant;
        no->prox = *li;
        no->ant = ultimo;
        ultimo->prox = no;
        (*li)->ant = no;
    }
    *li = no;
    return 1;
}

int insere_circ_final(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = al;
    if(*li == NULL){
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        Elem* ultimo = (*li)->ant;
        no->prox = *li;
        no->ant = ultimo;
        ultimo->prox = no;
        (*li)->ant = no;
    }
    return 1;
}

int remove_circ_inicio(Lista* li){
    if(li == NULL || *li == NULL) return 0;
    Elem* no = *li;
    if(no->prox == no){
        *li = NULL;
    } else {
        Elem* ultimo = no->ant;
        *li = no->prox;
        (*li)->ant = ultimo;
        ultimo->prox = *li;
    }
    free(no);
    return 1;
}

int remove_circ_final(Lista* li){
    if(li == NULL || *li == NULL) return 0;
    Elem* ultimo = (*li)->ant;
    if(ultimo == *li){
        *li = NULL;
    } else {
        Elem* penultimo = ultimo->ant;
        penultimo->prox = *li;
        (*li)->ant = penultimo;
    }
    free(ultimo);
    return 1;
}
