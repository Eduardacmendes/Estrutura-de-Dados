/*
 * Defeitos de memória encontrados:
 * 1. sizeof(v) dentro da função devolve o tamanho do ponteiro, não do vetor. 
 *    Solução: passar 'n' como parâmetro.
 * 2. Condição 'i <= n' acessa memória fora do vetor (v[n]). 
 *    Solução: alterar a condição para 'i < n'.
 * 3. 'return &maior;' retorna o endereço de uma variável local da pilha. 
 *    Solução: retornar o endereço do elemento dentro do próprio vetor (&v[p_maior]).
 * 4. '*p' desreferencia um ponteiro não inicializado. 
 *    Solução: atribuir o retorno de maiorValor a 'p' e imprimir '*p'.
 */

#include <stdio.h>

int *maiorValor(int v[], int n) {
    int maior = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] > v[maior]) {
            maior = i;
        }
    }
    return &v[maior];
}
int main(void) {
    int v[5] = {12, 7, 30, 4, 18};
    int n = 5;
    int *p = maiorValor(v,n);
    printf("%d \n", *p);
    return 0;
}