#include <stdio.h>
#include "ListaDinEncadCirc.h"

int falhas = 0;

// compara o valor obtido com o esperado e mostra o resultado
void confere(const char *desc, int obtido, int esperado){
    if(obtido == esperado)
        printf("  [ok]   %s: %d\n", desc, obtido);
    else{
        printf("  [ERRO] %s: esperado %d, obtido %d\n", desc, esperado, obtido);
        falhas++;
    }
}

// monta uma lista com as matriculas de v (notas = 0, 2, 4, 6...)
Lista* monta(const int *v, int n){
    Lista* li = cria_lista();
    for(int i = 0; i < n; i++){
        struct aluno a = {0};
        a.matricula = v[i];
        a.n1 = a.n2 = a.n3 = (float)(i * 2);
        insere_lista_final(li, a);
    }
    return li;
}

int main(void){
    int base[] = {12, 16, 23, 40};
    int m;
    struct aluno a;
    Lista* vazia = cria_lista();

    printf("Q1 - imprime_lista (esperado: 12 16 23 40)\n  ");
    Lista* li = monta(base, 4);
    imprime_lista(li);
    printf("  lista vazia e NULL nao imprimem nada: ");
    imprime_lista(vazia);
    imprime_lista(NULL);
    printf("(ok)\n");

    printf("Q2 - maior_matricula\n");
    confere("retorno", maior_matricula(li, &m), 1);
    confere("maior", m, 40);
    m = -7;
    confere("lista vazia, retorno", maior_matricula(vazia, &m), 0);
    confere("lista vazia, *mat inalterado", m, -7);
    confere("lista NULL, retorno", maior_matricula(NULL, &m), 0);

    printf("Q3 - conta_aprovados\n");
    confere("medias 0,2,4,6", conta_aprovados(li), 0);
    confere("lista vazia", conta_aprovados(vazia), 0);
    confere("lista NULL", conta_aprovados(NULL), 0);
    Lista* notas = cria_lista();
    float ns[] = {10.0f, 7.0f, 6.9f, 9.0f};
    for(int i = 0; i < 4; i++){
        struct aluno x = {0};
        x.matricula = i + 1;
        x.n1 = x.n2 = x.n3 = ns[i];
        insere_lista_final(notas, x);
    }
    confere("notas 10, 7, 6.9, 9", conta_aprovados(notas), 3);
    libera_lista(notas);

    printf("Q4 - busca_ciclica\n");
    int ks[] = {1, 4, 5, 7, 1000};
    int esp[] = {12, 40, 12, 23, 40};
    for(int i = 0; i < 5; i++){
        char desc[32];
        sprintf(desc, "k = %d", ks[i]);
        busca_ciclica(li, ks[i], &a);
        confere(desc, a.matricula, esp[i]);
    }
    confere("k = 0", busca_ciclica(li, 0, &a), 0);
    confere("k = -3", busca_ciclica(li, -3, &a), 0);
    confere("lista vazia", busca_ciclica(vazia, 1, &a), 0);

    printf("Q5 - remove_lista_pos\n");
    confere("pos 5 (fora)", remove_lista_pos(li, 5), 0);
    confere("pos 0 (fora)", remove_lista_pos(li, 0), 0);
    confere("pos 2", remove_lista_pos(li, 2), 1);
    printf("  esperado: 12 23 40 -> ");
    imprime_lista(li);
    confere("pos 1", remove_lista_pos(li, 1), 1);
    printf("  esperado: 23 40 -> ");
    imprime_lista(li);
    confere("ultima (pos 2)", remove_lista_pos(li, 2), 1);
    printf("  esperado: 23 -> ");
    imprime_lista(li);
    confere("unico elemento", remove_lista_pos(li, 1), 1);
    confere("tamanho depois", tamanho_lista(li), 0);
    confere("lista ja vazia", remove_lista_pos(li, 1), 0);
    libera_lista(li);

    printf("Q6 - rotaciona_lista\n");
    li = monta(base, 4);
    rotaciona_lista(li, 1);
    printf("  k = 1, esperado 16 23 40 12 -> ");
    imprime_lista(li);
    rotaciona_lista(li, 3);
    printf("  mais k = 3 (volta completa), esperado 12 16 23 40 -> ");
    imprime_lista(li);
    rotaciona_lista(li, 6);
    printf("  mais k = 6 (6 %% 4 = 2), esperado 23 40 12 16 -> ");
    imprime_lista(li);
    confere("k negativo", rotaciona_lista(li, -1), 0);
    confere("lista vazia", rotaciona_lista(vazia, 1), 0);
    libera_lista(li);

    printf("Q7 - concatena_listas\n");
    int v1[] = {1, 2}, v2[] = {3, 4};
    Lista *l1 = monta(v1, 2), *l2 = monta(v2, 2);
    confere("retorno", concatena_listas(l1, l2), 1);
    printf("  esperado 1 2 3 4 -> ");
    imprime_lista(l1);
    confere("tamanho de li2", tamanho_lista(l2), 0);
    struct aluno novo = {0};
    novo.matricula = 99;
    confere("li2 aceita insercao", insere_lista_final(l2, novo), 1);
    confere("concatena de novo", concatena_listas(l1, l2), 1);
    printf("  esperado 1 2 3 4 99 -> ");
    imprime_lista(l1);
    Lista *e1 = cria_lista(), *e2 = cria_lista();
    confere("li1 vazia", concatena_listas(e1, l1), 1);
    confere("tamanho de li2 depois", tamanho_lista(l1), 0);
    confere("as duas vazias", concatena_listas(e1, e2), 1);
    printf("  li1 ficou com: ");
    imprime_lista(e1);
    confere("li1 NULL", concatena_listas(NULL, e1), 0);
    libera_lista(l1); libera_lista(l2); libera_lista(e1); libera_lista(e2);

    printf("Q8 - josephus\n");
    int j[] = {1, 2, 3, 4, 5, 6, 7}, s = 0;
    Lista* lj = monta(j, 7);
    confere("retorno (1..7, k = 3)", josephus(lj, 3, &s), 1);
    confere("sobrevivente", s, 4);
    confere("tamanho depois", tamanho_lista(lj), 0);
    confere("lista ja vazia", josephus(lj, 3, &s), 0);
    int um[] = {42};
    Lista* l_um = monta(um, 1);
    confere("um elemento, retorno", josephus(l_um, 5, &s), 1);
    confere("um elemento, sobrevivente", s, 42);
    Lista* lk = monta(j, 7);
    confere("k = 1, retorno", josephus(lk, 1, &s), 1);
    confere("k = 1, sobrevivente", s, 7);
    confere("k = 0", josephus(lk, 0, &s), 0);
    libera_lista(lj); libera_lista(l_um); libera_lista(lk); libera_lista(vazia);

    if(falhas == 0)
        printf("\nTodos os testes passaram.\n");
    else
        printf("\n%d teste(s) falharam.\n", falhas);
    return falhas != 0;
}