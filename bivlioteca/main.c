#include <stdio.h>
#include "biblioteca.h"


int main() {

    Livro livros[MAX_LIVROS];

    int quantidade = carregarLivros(livros);

    int opcao;

    do {

        printf("\n");
        printf("=================================\n");
        printf("       SISTEMA DE BIBLIOTECA     \n");
        printf("=================================\n");

        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar livro\n");
        printf("4 - Emprestar livro\n");
        printf("5 - Devolver livro\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrarLivro(livros, &quantidade);
                break;

            case 2:
                listarLivros(livros, quantidade);
                break;

            case 3:
                buscarLivro(livros, quantidade);
                break;

            case 4:
                emprestarLivro(livros, quantidade);
                break;

            case 5:
                devolverLivro(livros, quantidade);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}