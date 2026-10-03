/* Acontece o buffer overflow, a função continuará escrevendo os 
caracteres além do espaço reservado no vetor de destino, 
o que sobrescreve dados vizinhos na memória e pode corromper variáveis.
O programa não avisa por que linguagem C não faz checagem automática
dos limites de memória em tempo de execução.
*/ 

#include <stdio.h>

int meuStrlen(const char *s){
    int tam = 0;
    while(*s != '\0'){
        tam += 1;
        s++;
    }
    return tam;
}
void meuStrcpy(char *destino, const char *origem){
    while(*origem != '\0'){
        *destino = *origem;
        destino++;
        origem++;
    }
    *destino = '\0';
}
int main(void){
    char origem[] = "Estrutura de Dados";
    int tam = meuStrlen(origem);
    char destino[tam+1];
    meuStrcpy(destino, origem);

    printf("%s|%d\n", destino, tam);
    return 0;
}