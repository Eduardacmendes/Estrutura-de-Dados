/*
Trocas pra n=6 -> são 3 trocas
Trocas pra n=7 -> são 3 trocas
Expressão geral: n/2 (divisão inteira), com uma número impar ele fica 
mesmo lugar pois inicio e fim se igualam e ai não entra no while
*/

#include <stdio.h>

void inverter(int *v, int n){
    int *inicio = v;
    int *fim = v + n-1;
    while(inicio<fim){
        int temp = *inicio;
        *inicio = *fim;
        *fim = temp;

        *inicio++;
        *fim--;
    }    
}
int main(void){
    int v1[] = {12, 7, 30, 4, 18, 9};
    inverter(v1,6);

    for(int i =0; i<6; i++){
        printf("%d ", v1[i]);
    }
    printf("\n");

    int v2[] = {1, 2, 3, 4 , 5, 6, 7};
    inverter(v2,7);

    for(int i =0; i<7; i++){
        printf("%d ", v2[i]);
    }
    return 0;
}