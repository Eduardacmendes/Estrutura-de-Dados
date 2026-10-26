#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"

struct elemento {
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
    if (li == NULL)
        return;
    if ((*li) != NULL) {
        Elem *aux, *no = *li;
        /* para quando o seguinte ao atual e o inicio: uma volta completa */
        while ((*li) != no->prox) {
            aux = no;
            no = no->prox;   /* avanca antes de liberar */
            free(aux);
        }
        free(no);
    }
    free(li);               /* libera o bloco do inicio */
}


int tamanho_lista(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    do {                    /* do-while: o primeiro elemento tem de ser contado */
        cont++;
        no = no->prox;
    } while (no != (*li));
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;              /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;           /* lista invalida */
    if (*li == NULL)
        return 1;           /* nenhum elemento alocado */
    return 0;
}


int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;           /* sem memoria: a lista esta cheia */
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;           /* unica linha que difere da insercao no final */
    }
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;     /* o inicio nao muda */
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia */
        *li = no;
        no->prox = no;
        return 1;
    }
    if ((*li)->dados.matricula > al.matricula) {   /* insercao no inicio */
        Elem *atual = *li;
        while (atual->prox != (*li))               /* procura o ultimo */
            atual = atual->prox;
        no->prox = *li;
        atual->prox = no;
        *li = no;
        return 1;
    }
    Elem *ant = *li, *atual = (*li)->prox;
    while (atual != (*li) && atual->dados.matricula < al.matricula) {
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = no;
    no->prox = atual;
    return 1;
}


int remove_lista_inicio(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while (atual->prox != (*li))  /* procura o ultimo */
        atual = atual->prox;
    Elem *no = *li;
    atual->prox = no->prox;       /* o ultimo passa a apontar para o segundo */
    *li = no->prox;               /* o segundo passa a ser o inicio */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant = NULL, *no = *li;
    while (no->prox != (*li)) {   /* procura o ultimo, guardando o anterior */
        ant = no;
        no = no->prox;
    }
    ant->prox = no->prox;         /* o penultimo passa a apontar para o inicio */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    Elem *no = *li;
    if (no->dados.matricula == mat) {      /* remocao do inicio */
        if (no == no->prox) {              /* a lista fica vazia */
            free(no);
            *li = NULL;
            return 1;
        } else {
            Elem *ult = *li;
            while (ult->prox != (*li))     /* procura o ultimo */
                ult = ult->prox;
            ult->prox = (*li)->prox;
            *li = (*li)->prox;
            free(no);
            return 1;
        }
    }
    Elem *ant = no;
    no = no->prox;
    /* para ao encontrar a matricula ou ao completar uma volta */
    while (no != (*li) && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == (*li))
        return 0;           /* chave ausente */
    ant->prox = no->prox;
    free(no);
    return 1;
}


int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    /* para no ultimo elemento ou ao alcancar a posicao desejada */
    while (no->prox != (*li) && i < pos) {
        no = no->prox;
        i++;
    }
    if (i != pos)
        return 0;           /* posicao inexistente */
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    /* para no ultimo elemento ou ao encontrar a matricula */
    while (no->prox != (*li) && no->dados.matricula != mat)
        no = no->prox;
    if (no->dados.matricula != mat)
        return 0;           /* chave ausente */
    else {
        *al = no->dados;
        return 1;
    }
}

// Q1
void imprime_lista(Lista* li){
    if(li == NULL || *li == NULL) return;
    Elem *no = *li;
    do{
        printf(no == *li ? "%d" : " %d", no->dados.matricula);
        no = no->prox;
    }while(no != *li);
    printf("\n");
}

// Q2
int maior_matricula(Lista* li, int *mat){
    if(li == NULL || *li == NULL || mat == NULL) return 0;
    Elem *no = *li;
    int maior = no->dados.matricula;
    do{
        if(no->dados.matricula > maior)
            maior = no->dados.matricula;
        no = no->prox;
    }while(no != *li);
    *mat = maior;
    return 1;
}

/* Q3
   O codigo original tinha dois problemas:
   1) o while(no != NULL) nunca para. Na lista circular o prox do ultimo
      aponta pro primeiro, entao nunca chega em NULL. A funcao fica girando
      na lista pra sempre e o cont vai aumentando ate estourar o int.
   2) nao testava li == NULL, entao o *li quebrava (segfault) com lista
      invalida. Lista vazia (*li == NULL) so dava certo por acaso, porque o
      laco nem rodava. Trocando pra do-while esse teste vira obrigatorio,
      senao o no->dados acessa NULL. */
int conta_aprovados(Lista* li){
    if(li == NULL || *li == NULL) return 0;
    int cont = 0;
    Elem *no = *li;
    do{
        float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3.0f;
        if(media >= 7.0f)
            cont++;
        no = no->prox;
    }while(no != *li);
    return cont;
}

// Q4
int busca_ciclica(Lista* li, int k, struct aluno *al){
    if(li == NULL || *li == NULL || al == NULL || k <= 0) return 0;
    int n = tamanho_lista(li);
    int avancos = (k - 1) % n;
    Elem *no = *li;
    for(int i = 0; i < avancos; i++)
        no = no->prox;
    *al = no->dados;
    return 1;
}

// Q5
int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || *li == NULL) return 0;
    int n = tamanho_lista(li);
    if(pos < 1 || pos > n) return 0;
    if(pos == 1)
        return remove_lista_inicio(li);
    Elem *ant = *li;
    for(int i = 1; i < pos - 1; i++) // para no antecessor da posicao pos
        ant = ant->prox;
    Elem *rem = ant->prox;
    ant->prox = rem->prox; // se rem era o ultimo, aponta para o inicio
    free(rem);
    return 1;
}

/* Q6
   Pergunta 1: o custo e O(min(k, N)). Pra k pequeno sao so k passos e nao
   depende do tamanho da lista, porque nao mexo em nenhum prox, so troco o
   ponteiro de entrada (*li). So quando k >= N eu dou a volta inteira pra
   descobrir N e ai uso k % N.
   Pergunta 2: numa lista nao circular teria que achar o ultimo no, achar o
   k-esimo, ligar o ultimo no antigo inicio e colocar NULL no prox do
   k-esimo. Precisa percorrer a lista, entao e O(N) sempre, mesmo com k
   pequeno. */
int rotaciona_lista(Lista* li, int k){
    if(li == NULL || *li == NULL || k < 0) return 0;
    Elem *no = *li;
    int i = 0;
    while(i < k){
        no = no->prox;
        i++;
        if(no == *li){ // volta completa: i e o tamanho da lista
            k %= i;
            i = 0;
        }
    }
    *li = no;
    return 1;
}

/* Q7
   Aqui preciso achar o ultimo de cada lista, entao o custo e O(N1 + N2).
   Se (*li) guardasse o final da lista (o do fim da aula) ficava O(1): era
   so trocar o prox dos dois ultimos e atualizar *li1, sem percorrer nada. */
int concatena_listas(Lista* li1, Lista* li2){
    if(li1 == NULL || li2 == NULL || li1 == li2) return 0;
    if(*li2 == NULL) return 1;
    if(*li1 == NULL){
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }
    Elem *ult1 = *li1;
    while(ult1->prox != *li1) ult1 = ult1->prox;
    Elem *ult2 = *li2;
    while(ult2->prox != *li2) ult2 = ult2->prox;
    ult1->prox = *li2; // corte cruzado
    ult2->prox = *li1;
    *li2 = NULL;
    return 1;
}

/* Q8
   ant e atual andam juntos. ant comeca no ultimo (antecessor do inicio).
   O laco para quando sobra um no so (atual->prox == atual). */
int josephus(Lista* li, int k, int *sobrevivente){
    if(li == NULL || *li == NULL || k <= 0 || sobrevivente == NULL) return 0;
    Elem *atual = *li;
    Elem *ant = *li;
    while(ant->prox != *li) // antecessor inicial = ultimo
        ant = ant->prox;
    while(atual->prox != atual){ // ate restar um unico no
        for(int i = 1; i < k; i++){
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = atual->prox;
        Elem *rem = atual;
        atual = atual->prox;
        free(rem);
    }
    *sobrevivente = atual->dados.matricula;
    free(atual);
    *li = NULL;
    return 1;
}