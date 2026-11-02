#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

struct aluno novo(int mat){
    struct aluno a = {0};
    a.matricula = mat;
    return a;
}

Lista* monta(int v[], int n){
    Lista* li = cria_lista();
    for(int i = 0; i < n; i++)
        insere_lista_final(li, novo(v[i]));
    return li;
}

void imprime(char* msg, Lista* li){
    struct aluno a;
    int n = tamanho_lista(li);
    printf("%s: ", msg);
    if(n == 0)
        printf("(vazia) ");
    for(int i = 1; i <= n; i++){
        busca_lista_pos(li, i, &a);
        printf("%d ", a.matricula);
    }
    printf("| consistente = %d\n", lista_consistente(li));
}

int main(){
    Lista* li;
    Lista* vazia = cria_lista();

    printf("Q1: imprime_lista_inversa\n");
    int a[] = {33, 23, 16};
    li = monta(a, 3);
    imprime_lista_inversa(li);          // 16 23 33 
    imprime_lista_inversa(vazia);       //lista vazia
    imprime_lista_inversa(NULL);        //lista vazia
    libera_lista(li);

    printf("\nQ2: lista_consistente\n");
    li = monta(a, 3);
    printf("3 elementos: %d (esperado 1)\n", lista_consistente(li));
    printf("vazia: %d (esperado 1)\n", lista_consistente(vazia));
    printf("NULL: %d (esperado 0)\n", lista_consistente(NULL));
    libera_lista(li);

    printf("\nQ3: remove_lista_corrigida\n");
    li = monta(a, 3);
    remove_lista_corrigida(li, 23);
    imprime("tirei o 23", li);          // 33 16 
    remove_lista_corrigida(li, 33);
    imprime("tirei o 33", li);          // 16 
    printf("tirar o 99: %d (esperado 0)\n", remove_lista_corrigida(li, 99));
    remove_lista_corrigida(li, 16);
    imprime("tirei o 16", li);          // vazia 
    libera_lista(li);

    printf("\nQ4: remove_lista_pos\n");
    int b[] = {10, 20, 30, 40, 50};
    li = monta(b, 5);
    remove_lista_pos(li, 1);
    imprime("pos 1", li);               // 20 30 40 50 
    remove_lista_pos(li, 2);
    imprime("pos 2", li);               // 20 40 50 
    remove_lista_pos(li, 3);
    imprime("pos 3 (ultima)", li);      // 20 40 
    printf("pos 0: %d (esperado 0)\n", remove_lista_pos(li, 0));
    printf("pos 7: %d (esperado 0)\n", remove_lista_pos(li, 7));
    printf("lista vazia: %d (esperado 0)\n", remove_lista_pos(vazia, 1));
    printf("NULL: %d (esperado 0)\n", remove_lista_pos(NULL, 1));
    libera_lista(li);

    printf("\nQ5: move_para_inicio\n");
    int c[] = {10, 20, 30, 40};
    li = monta(c, 4);
    move_para_inicio(li, 30);
    imprime("mat 30", li);              // 30 10 20 40 
    move_para_inicio(li, 40);
    imprime("mat 40 (ultimo)", li);     // 40 30 10 20 
    move_para_inicio(li, 40);
    imprime("mat 40 (ja e o primeiro)", li);
    printf("mat 99: %d (esperado 0)\n", move_para_inicio(li, 99));
    libera_lista(li);

    printf("\nQ6: remove_todos\n");
    int d[] = {7, 3, 7, 7, 5, 7};
    li = monta(d, 6);
    printf("removidos: %d (esperado 4)\n", remove_todos(li, 7));
    imprime("depois", li);             // 3 5 
    libera_lista(li);
    int e[] = {4, 4, 4};
    li = monta(e, 3);
    printf("removidos: %d (esperado 3)\n", remove_todos(li, 4));
    imprime("todos iguais", li);        // vazia 
    libera_lista(li);

    printf("\nQ7: inverte_lista\n");
    int f[] = {1, 2, 3, 4, 5};
    li = monta(f, 5);
    inverte_lista(li);
    imprime("invertida", li);           // 5 4 3 2 1 
    libera_lista(li);
    int g[] = {9};
    li = monta(g, 1);
    inverte_lista(li);
    imprime("um elemento", li);
    libera_lista(li);
    inverte_lista(vazia);
    inverte_lista(NULL);

    printf("\nQ8: eh_palindromo\n");
    int p1[] = {1, 2, 3, 2, 1}, p2[] = {4, 8, 8, 4}, p3[] = {1, 2, 2, 3};
    li = monta(p1, 5);
    printf("1 2 3 2 1: %d (esperado 1)\n", eh_palindromo(li));
    libera_lista(li);
    li = monta(p2, 4);
    printf("4 8 8 4: %d (esperado 1)\n", eh_palindromo(li));
    libera_lista(li);
    li = monta(p3, 4);
    printf("1 2 2 3: %d (esperado 0)\n", eh_palindromo(li));
    libera_lista(li);
    li = monta(g, 1);
    printf("um elemento: %d (esperado 1)\n", eh_palindromo(li));
    libera_lista(li);
    printf("vazia: %d (esperado 1)\n", eh_palindromo(vazia));
    printf("NULL: %d (esperado 0)\n", eh_palindromo(NULL));

    printf("\nExtra: lista circular\n");
    Lista* c2 = cria_lista();
    struct aluno x;
    insere_circ_final(c2, novo(1));
    insere_circ_final(c2, novo(2));
    insere_circ_final(c2, novo(3));
    insere_circ_inicio(c2, novo(0));
    printf("0 1 2 3 -> ");
    for(int i = 1; i <= 5; i++){
        busca_lista_pos(c2, i, &x);
        printf("%d ", x.matricula);     // a 5a posicao volta pro 0 
    }
    printf("\n");
    remove_circ_final(c2);
    remove_circ_inicio(c2);
    printf("depois de remover o 3 e o 0 -> ");
    for(int i = 1; i <= 3; i++){
        busca_lista_pos(c2, i, &x);
        printf("%d ", x.matricula);     // 1 2 1 
    }
    printf("\n");
    printf("esvaziando: ");
    printf("%d ", remove_circ_inicio(c2));
    printf("%d ", remove_circ_final(c2));
    printf("%d (esperado 1 1 0)\n", remove_circ_inicio(c2));
    free(c2);

    libera_lista(vazia);
    return 0;
}