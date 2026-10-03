#include <stdio.h>

void ordenarPar(int *a, int *b){
    if (*a>*b) {
        int r = *b;
        *b = *a;
        *a = r;
    }
}
int main(void){
    int a = 9;
    int b = 5;
    ordenarPar(&a, &b);
    printf("(%d, %d)", a, b);

    return 0;
}