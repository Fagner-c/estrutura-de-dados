#include <stdio.h>
#include <string.h>
#include "biblioteca.h"


void cadastrarLivro(Livro *livros, int *quantidade) {

    if (*quantidade >= MAX_LIVROS) {
        printf("\nLimite de livros atingido!\n");
        return;
    }

    Livro *novo = &livros[*quantidade];

    novo->id = *quantidade + 1;

    printf("\n===== CADASTRO DE LIVRO =====\n");

    printf("Titulo: ");
    getchar();
    fgets(novo->titulo, sizeof(novo->titulo), stdin);
    novo->titulo[strcspn(novo->titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(novo->autor, sizeof(novo->autor), stdin);
    novo->autor[strcspn(novo->autor, "\n")] = '\0';

    printf("Ano de publicacao: ");
    scanf("%d", &novo->ano);

    novo->disponivel = 1;

    (*quantidade)++;

    printf("\nLivro cadastrado com sucesso!\n");

    salvarLivros(livros, *quantidade);
}


void listarLivros(Livro *livros, int quantidade) {

    printf("\n===== LIVROS CADASTRADOS =====\n");

    if (quantidade == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {

        printf("\nID: %d\n", livros[i].id);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Ano: %d\n", livros[i].ano);

        if (livros[i].disponivel) {
            printf("Status: Disponivel\n");
        } else {
            printf("Status: Emprestado\n");
        }
    }
}


void buscarLivro(Livro *livros, int quantidade) {

    int id;

    printf("\nDigite o ID do livro: ");
    scanf("%d", &id);

    for (int i = 0; i < quantidade; i++) {

        if (livros[i].id == id) {

            printf("\n===== LIVRO ENCONTRADO =====\n");
            printf("ID: %d\n", livros[i].id);
            printf("Titulo: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Ano: %d\n", livros[i].ano);

            if (livros[i].disponivel) {
                printf("Status: Disponivel\n");
            } else {
                printf("Status: Emprestado\n");
            }

            return;
        }
    }

    printf("\nLivro nao encontrado!\n");
}


void emprestarLivro(Livro *livros, int quantidade) {

    int id;

    printf("\nDigite o ID do livro que deseja emprestar: ");
    scanf("%d", &id);

    for (int i = 0; i < quantidade; i++) {

        if (livros[i].id == id) {

            if (livros[i].disponivel == 1) {

                livros[i].disponivel = 0;

                printf("\nLivro emprestado com sucesso!\n");

                salvarLivros(livros, quantidade);

            } else {

                printf("\nEste livro ja esta emprestado!\n");
            }

            return;
        }
    }

    printf("\nLivro nao encontrado!\n");
}


void devolverLivro(Livro *livros, int quantidade) {

    int id;

    printf("\nDigite o ID do livro que deseja devolver: ");
    scanf("%d", &id);

    for (int i = 0; i < quantidade; i++) {

        if (livros[i].id == id) {

            if (livros[i].disponivel == 0) {

                livros[i].disponivel = 1;

                printf("\nLivro devolvido com sucesso!\n");

                salvarLivros(livros, quantidade);

            } else {

                printf("\nEste livro ja esta disponivel!\n");
            }

            return;
        }
    }

    printf("\nLivro nao encontrado!\n");
}


void salvarLivros(Livro *livros, int quantidade) {

    FILE *arquivo;

    arquivo = fopen("livros.txt", "w");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {

        fprintf(
            arquivo,
            "%d|%s|%s|%d|%d\n",
            livros[i].id,
            livros[i].titulo,
            livros[i].autor,
            livros[i].ano,
            livros[i].disponivel
        );
    }

    fclose(arquivo);
}


int carregarLivros(Livro *livros) {

    FILE *arquivo;

    arquivo = fopen("livros.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    int quantidade = 0;

    while (
        fscanf(
            arquivo,
            "%d|%99[^|]|%99[^|]|%d|%d\n",
            &livros[quantidade].id,
            livros[quantidade].titulo,
            livros[quantidade].autor,
            &livros[quantidade].ano,
            &livros[quantidade].disponivel
        ) == 5
    ) {

        quantidade++;

        if (quantidade >= MAX_LIVROS) {
            break;
        }
    }

    fclose(arquivo);

    return quantidade;
}