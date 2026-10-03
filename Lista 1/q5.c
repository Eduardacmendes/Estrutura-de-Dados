/*Devolver &v[i] é seguro porque o vetor foi criado na main e sua
memória continua válida durante todo o programa; já devolver o endereço
de uma variável local não é seguro porque a memória dessa variável é
destruída assim que a função termina, deixando o ponteiro inválido.
*/
#include <stdio.h>

int *primeiraOcorrencia(int *v, int n, int alvo){
    for (int i =0; i<n; i++){
        if (v[i] == alvo){
            return &v[i];
        }
    }
    return NULL;
}
int main(){
    int v[] = {12, 7, 30, 4, 18, 30};
    int n = 6;
    int *valor = primeiraOcorrencia(v, n, 30);

    if (valor != NULL){
        *valor = 0;

        for(int i = 0; i<n;i++){
            printf ("%d ", v[i]);
        }
        printf("\n");
    } else{
        printf("nao encontrado\n");
    }
    valor = primeiraOcorrencia(v, n, 99);

    if (valor != NULL){
        *valor = 0;
    } else{
        printf("nao encontrado\n");
    }

    return 0;
}