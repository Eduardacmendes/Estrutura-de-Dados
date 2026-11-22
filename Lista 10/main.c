
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "PilhaSequencial.h"
#include "PilhaChar.h"
#include "PilhaDupla.h"

struct aluno cria_aluno(int matricula) {
    struct aluno a = {0};
    a.matricula = matricula;
    return a;
}

/* Questao 4
   a) I I R I I R R R produz 2, 4, 3, 1.
      I(1) [1]      I(2) [1,2]    R [1] (sai 2)
      I(3) [1,3]    I(4) [1,3,4]  R [1,3] (sai 4)
      R [1] (sai 3)                R [] (sai 1)
   b) 3,1,4,2 nao e possivel: depois de tirar 3, o 2 continua
      sobre o 1 e tem que sair antes, pela regra LIFO.
   d) A funcao de 4c nao precisa criar pilha: qtd conta quantos
      elementos estariam nela. Nao pode remover se qtd for zero.
*/
int sequencia_valida(const char *s) {
    if (s == NULL) return 0;

    int qtd = 0;

    while (*s) {
        if (*s == 'I') {
            qtd++;
        }
        else if (*s == 'R') {
            if (qtd == 0) return 0;
            qtd--;
        }
        else {
            return 0;
        }
        s++;
    }

    return qtd == 0;
}

void tira_topo(Pilha *pi) {
    struct aluno a;

    if (consulta_topo_Pilha(pi, &a)) {
        printf("%d ", a.matricula);
        remove_Pilha(pi);
    }
}

void questao4(void) {
    Pilha *pi = cria_Pilha(4);
    if (pi == NULL) return;

    insere_Pilha(pi, cria_aluno(1));
    insere_Pilha(pi, cria_aluno(2));

    printf("Saida: ");
    tira_topo(pi);

    insere_Pilha(pi, cria_aluno(3));
    insere_Pilha(pi, cria_aluno(4));

    tira_topo(pi);
    tira_topo(pi);
    tira_topo(pi);

    printf("\n");
    libera_Pilha(pi);

    printf("IRIIRR: %d\n", sequencia_valida("IRIIRR"));
    printf("IRRI: %d\n", sequencia_valida("IRRI"));
}

/* Questao 5
   c) Uma capacidade igual ao tamanho da expressao ja e suficiente.
      O minimo seria a maior quantidade de aberturas simultaneas.
   d) Contar aberturas e fechamentos nao funciona em ([)]:
      as quantidades batem, mas o ')' tenta fechar um '['.
*/
int verifica_delimitadores(const char *expr) {
    if (expr == NULL) return 0;

    size_t len = strlen(expr);
    if (len > INT_MAX) return 0;

    PilhaChar *pi = cria_PilhaChar(len == 0 ? 1 : (int)len);
    if (pi == NULL) return 0;

    int ok = 1;

    for (size_t i = 0; expr[i] && ok; i++) {
        char c = expr[i], topo;

        if (c == '(' || c == '[' || c == '{') {
            if (!insere_PilhaChar(pi, c))
                ok = 0;
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (!consulta_topo_PilhaChar(pi, &topo) ||
                (c == ')' && topo != '(') ||
                (c == ']' && topo != '[') ||
                (c == '}' && topo != '{')) {
                ok = 0;
            }
            else {
                remove_PilhaChar(pi);
            }
        }
    }

    if (!PilhaChar_vazia(pi))
        ok = 0;

    libera_PilhaChar(pi);
    return ok;
}

void questao5(void) {
    const char *exp[] = {
        "(())", "()()", "{a[b(c)d]e}",
        ")(", "(()(", "([)]", ""
    };

    for (int i = 0; i < 7; i++)
        printf("%s -> %d\n", exp[i], verifica_delimitadores(exp[i]));
}

/* Questao 6
   a) Na PilhaDupla, o topo da P1 fica em dados[qtd1-1] e o
      topo da P2 em dados[capacidade-qtd2]. A estrutura esta cheia
      quando qtd1+qtd2=capacidade.
   b) Capacidade 5:
      insere P1 10 -> 1  [10,-,-,-,-]
      insere P2 90 -> 1  [10,-,-,-,90]
      insere P1 20 -> 1  [10,20,-,-,90]
      insere P2 80 -> 1  [10,20,-,80,90]
      insere P1 30 -> 1  [10,20,30,80,90]
      insere P2 70 -> 0  (cheia)
      remove P2    -> 1  [10,20,30,(80),90]
      insere P1 40 -> 1  [10,20,30,40,90]
      Final: qtd1=4, qtd2=1, topo1=40 e topo2=90.
   c) Em duas pilhas separadas de capacidade 4, o quinto elemento
      na P1 falha. Na PilhaDupla de capacidade 8, entra se a P2
      estiver vazia. O contrario nao ocorre, porque o espaco total
      de 8 comporta qualquer ocupacao aceita pelas duas separadas.
   d) As operacoes custam O(1). E util quando a memoria e fixa,
      pois uma pilha aproveita o espaco nao usado pela outra.
*/
void questao6(void) {
    PilhaDupla *pd = cria_PilhaDupla(5);
    struct aluno a;

    if (pd == NULL) return;

    printf("Insere 10 P1: %d\n",
           insere_PilhaDupla(pd, 1, cria_aluno(10)));

    printf("Insere 90 P2: %d\n",
           insere_PilhaDupla(pd, 2, cria_aluno(90)));

    printf("Insere 20 P1: %d\n",
           insere_PilhaDupla(pd, 1, cria_aluno(20)));

    printf("Insere 80 P2: %d\n",
           insere_PilhaDupla(pd, 2, cria_aluno(80)));

    printf("Insere 30 P1: %d\n",
           insere_PilhaDupla(pd, 1, cria_aluno(30)));

    printf("Insere 70 P2: %d\n",
           insere_PilhaDupla(pd, 2, cria_aluno(70)));

    printf("Remove P2: %d\n", remove_PilhaDupla(pd, 2));

    printf("Insere 40 P1: %d\n",
           insere_PilhaDupla(pd, 1, cria_aluno(40)));

    printf("Tamanho P1: %d / P2: %d\n",
           tamanho_PilhaDupla(pd, 1),
           tamanho_PilhaDupla(pd, 2));

    if (consulta_topo_PilhaDupla(pd, 1, &a))
        printf("Topo P1: %d\n", a.matricula);

    if (consulta_topo_PilhaDupla(pd, 2, &a))
        printf("Topo P2: %d\n", a.matricula);

    libera_PilhaDupla(pd);
}

int main(void) {
    printf("\nQuestao 4\n");
    questao4();

    printf("\nQuestao 5\n");
    questao5();

    printf("\nQuestao 6\n");
    questao6();

    return 0;
}
