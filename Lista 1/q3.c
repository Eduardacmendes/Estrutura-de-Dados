/* Ele avança 4 bytes na memória para int *v 
e se fosse double avançaria 8 bytes na memória.
*/
#include <stdio.h>

int somaVetor(const int *v, int n){
    int soma = 0;
    for(int i = 0; i<n; i++){
        soma += *v;
        v++;
    }
    return soma;
}
int main(){
    int v[] = {12, 7, 30, 4, 18};
    int n = 5;
    printf("%d", somaVetor(v, n));

    return 0;
}