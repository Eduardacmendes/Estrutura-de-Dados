
#include <stdio.h>
#include <limits.h>
#include "FilaEstatica.h"

struct aluno cria_aluno(int matricula) {
    struct aluno a = {0};
    a.matricula = matricula;
    return a;
}

void imprime_fila(Fila *fi) {
    struct aluno a;
    while (consulta_Fila(fi, &a)) {
        printf("%d ", a.matricula);
        remove_Fila(fi);
    }
    printf("\n");
}

/* Questao 1
   a) * significa que o aluno ainda esta na fila.

   Operacao       ret  inicio final qtd     vetor [0,1,2,3]
   cria(4)        ptr     0     0    0      [-,-,-,-]
   insere 5        1      0     1    1      [5*,-,-,-]
   insere 8        1      0     2    2      [5*,8*,-,-]
   insere 3        1      0     3    3      [5*,8*,3*,-]
   remove          1      1     3    2      [5,8*,3*,-]
   insere 9        1      1     0    3      [5,8*,3*,9*]
   insere 7        1      1     1    4      [7*,8*,3*,9*]
   insere 1        0      1     1    4      [7*,8*,3*,9*]
   remove          1      2     1    3      [7*,8,3*,9*]
   insere 6        1      2     2    4      [7*,6*,3*,9*]
   consulta        1      2     2    4      [7*,6*,3*,9*]

   b) Ordem final: 3, 9, 7, 6. A consulta retorna o aluno 3.
   c) Foram sobrescritas as posicoes 0 (5 por 7) e 1 (8 por 6).
      Os valores antigos ja tinham sido removidos. A fila circular
      reutiliza essas posicoes sem perder elementos validos.
*/
void questao1(void) {
    Fila *fi = cria_Fila(4);
    struct aluno a;
    if (fi == NULL) return;

    printf("Insere 5: %d\n", insere_Fila(fi, cria_aluno(5)));
    printf("Insere 8: %d\n", insere_Fila(fi, cria_aluno(8)));
    printf("Insere 3: %d\n", insere_Fila(fi, cria_aluno(3)));
    printf("Remove: %d\n", remove_Fila(fi));
    printf("Insere 9: %d\n", insere_Fila(fi, cria_aluno(9)));
    printf("Insere 7: %d\n", insere_Fila(fi, cria_aluno(7)));
    printf("Insere 1: %d\n", insere_Fila(fi, cria_aluno(1)));
    printf("Remove: %d\n", remove_Fila(fi));
    printf("Insere 6: %d\n", insere_Fila(fi, cria_aluno(6)));

    if (consulta_Fila(fi, &a))
        printf("Consulta: %d\n", a.matricula);

    printf("Fila final: ");
    imprime_fila(fi);
    libera_Fila(fi);
}

/* Questao 2
   b) Com inicio=0, (inicio-1)%4 resulta em -1 no C.
      dados[-1] acessaria memoria fora do vetor. O certo e usar
      (inicio+capacidade-1)%capacidade.
   c) Nao e mais uma fila FIFO estrita, pois um aluno pode passar
      na frente de quem chegou antes.
*/
void questao2(void) {
    Fila *fi = cria_Fila(4);
    if (fi == NULL) return;

    printf("Fila vazia: %d\n", fura_Fila(fi, cria_aluno(10)));
    printf("Atendimento: ");
    imprime_fila(fi);
    libera_Fila(fi);

    fi = cria_Fila(4);
    if (fi == NULL) return;

    insere_Fila(fi, cria_aluno(1));
    insere_Fila(fi, cria_aluno(2));

    printf("Inicio igual a 0: %d\n", fura_Fila(fi, cria_aluno(99)));
    printf("Atendimento: ");
    imprime_fila(fi);
    libera_Fila(fi);

    fi = cria_Fila(2);
    if (fi == NULL) return;

    insere_Fila(fi, cria_aluno(1));
    insere_Fila(fi, cria_aluno(2));
    printf("Fila cheia: %d\n", fura_Fila(fi, cria_aluno(99)));
    libera_Fila(fi);

    fi = cria_Fila(5);
    if (fi == NULL) return;

    for (int i = 1; i <= 4; i++)
        insere_Fila(fi, cria_aluno(i));

    remove_Fila(fi);
    remove_Fila(fi);
    insere_Fila(fi, cria_aluno(5));
    insere_Fila(fi, cria_aluno(6));

    printf("Fila circular: %d\n", fura_Fila(fi, cria_aluno(99)));
    printf("Atendimento: ");
    imprime_fila(fi);
    libera_Fila(fi);

    printf("Fila NULL: %d\n", fura_Fila(NULL, cria_aluno(1)));
}

/* Questao 3
   b) A fila precisa guardar pelo menos n alunos. Usando n+1,
      ela nunca chega a ficar cheia. As rotacoes nao aumentam a qtd.
   c) Na fila circular, insere e remove custam O(1), entao O(n*k).
      Em lista sequencial com remove_lista_inicio, seria O(k*n*n),
      por causa dos deslocamentos. A fila circular e melhor aqui.
*/
int josefo(int n, int k) {
    if (n <= 0 || k <= 0 || n == INT_MAX)
        return -1;

    Fila *fi = cria_Fila(n + 1);
    if (fi == NULL) return -1;

    for (int i = 1; i <= n; i++) {
        if (!insere_Fila(fi, cria_aluno(i))) {
            libera_Fila(fi);
            return -1;
        }
    }

    struct aluno a;
    printf("Saidas: ");

    while (tamanho_Fila(fi) > 1) {
        for (int i = 1; i < k; i++) {
            consulta_Fila(fi, &a);
            remove_Fila(fi);
            insere_Fila(fi, a);
        }

        consulta_Fila(fi, &a);
        printf("%d ", a.matricula);
        remove_Fila(fi);
    }

    consulta_Fila(fi, &a);
    int vencedor = a.matricula;

    printf("| Sobrevivente: %d\n", vencedor);
    libera_Fila(fi);

    return vencedor;
}

void questao3(void) {
    printf("n=7, k=3: "); josefo(7, 3);
    printf("n=5, k=2: "); josefo(5, 2);
    printf("n=1, k=4: "); josefo(1, 4);
    printf("n=6, k=1: "); josefo(6, 1);
}

int main(void) {
    printf("\nQuestao 1\n");
    questao1();

    printf("\nQuestao 2\n");
    questao2();

    printf("\nQuestao 3\n");
    questao3();

    return 0;
}
