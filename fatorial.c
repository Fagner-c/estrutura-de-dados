#include <stdio.h>
int numero = 0;
int user_number(){
    printf("Digite um numero interio positivo para realizar o fatorial: ");
    scanf("%d", &numero);
}
void fatorial(){
    int aux = 1;
    for(int i = 1; i <= numero; i++){
        aux *= i;
    }
    printf("O fatorial de %d e': %d", numero, aux);
}
void main(){
    user_number();
    fatorial(numero);
}
