#include <stdio.h>
float numbers[3] = {};
float soma, media = 0;

void user_numbers(){
    for(int i = 0; i < 3; i++){
        printf("Digite o numero da posicao %d para  calcular a media: ", i);
        scanf("%f", &numbers[i]);
    }
}
void somar(){
    for(int i = 0; i < 3; i++){
        soma += numbers[i];
    }
    printf("A soma e': %.2f\n", soma);
}
void media_numbers(){
    media = soma/3;
    printf("A media e': %.2f", media);
}
void main(){
    user_numbers();
    somar();
    media_numbers();
}
