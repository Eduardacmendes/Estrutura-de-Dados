/*Se fosse void dobrar(int n) a funçao recebiria apenas uma cópia do 
valor e ai as alterações seriam na memória local e seriam perdidas após
o término da execução sem alterar realmente 'n' da main.
*/
#include <stdio.h>

void dobrar(int *n){
    *n = (*n) * 2;
}
int main(void){
    int n = 21;
    dobrar(&n);
    printf("%d\n", n);
    return 0;
}