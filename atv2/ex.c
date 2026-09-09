#include <stdio.h>
int main() {
    int quant_estoque = 0;
    printf("Digite a quantidade de produtos: ");
    scanf("%d", &quant_estoque);
    int estoque[quant_estoque];
    int *pont = estoque;
    int p, q;
    char opc;
    printf("Digite a quantidade de cada produto:\n");
    for (int i = 0; i < quant_estoque; i++) {
        printf("Produto %d: ", i + 1);
        scanf("%d", pont + i);
    }
    do {
        printf("\n===== CONTROLE DE ESTOQUE =====\n");
        printf("1 - Consultar estoque\n");
        printf("2 - Atualizar estoque\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opc);
        switch (opc) {
            case '1':
                printf("\n--- Estoque atual ---\n");
                for (int i = 0; i < quant_estoque; i++) {
                    printf("Produto %d: %d unidades\n",
                           i + 1, *(pont + i));
                }
                break;
            case '2':
                printf("\nDigite o numero do produto (1 a %d): ",
                       quant_estoque);
                scanf("%d", &p);
                if (p < 1 || p > quant_estoque) {

                    printf("Produto invalido!\n");
                    break;
                }
                printf("Digite a nova quantidade: ");
                scanf("%d", &q);
                *(pont + (p - 1)) = q;
                printf("Estoque atualizado!\n");
                break;
            case '3':
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opc != '3');
    return 0;
}