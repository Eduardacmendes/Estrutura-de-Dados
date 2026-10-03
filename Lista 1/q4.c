#include <stdio.h>

void minMax(const int *v, int n, int *min, int *max){
    if(n<=0){
        return;
    }else{
        *max = *min = v[0]; 
        for(int i = 0; i<n; i++){
           if(v[i]>= *max){
            *max = v[i];
           }
           if(v[i]<= *min){
            *min = v[i];
           }
        }
    }
}

int main(void){
    int v[] = {12, 7, 30, 4, 18, 9};
    int n = 6;
    int min;
    int max;
    minMax(v, n, &min, &max);

    printf ("%d %d\n", min, max);
    return 0;
}