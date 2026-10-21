
#include "b.h"
#include <stdio.h>
#include <stdlib.h>

static void limparLinha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void menuEstatica(void) {
    Livro livros[qt_max];
    int quantidade = carregarLivros(livros);
    int opcao;

    do {
        printf("\n=== LISTA ESTATICA ===\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar livro\n");
        printf("4 - Emprestar livro\n");
        printf("5 - Devolver livro\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparLinha();
            printf("Entrada invalida!\n");
            continue;
        }
        limparLinha();

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
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

static void menuDinamica(void) {
    ListaDinamica lista;
    int opcao;

    inicializarLista(&lista);

    if (!carregarDinamico(&lista)) {
        printf("Erro ao carregar os livros.\n");
        liberarLista(&lista);
        return;
    }

    do {
        printf("\n=== LISTA DINAMICA ===\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar livro\n");
        printf("4 - Emprestar livro\n");
        printf("5 - Devolver livro\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparLinha();
            printf("Entrada invalida!\n");
            continue;
        }
        limparLinha();

        switch (opcao) {
            case 1:
                cadastrarDinamico(&lista);
                break;
            case 2:
                listarDinamico(&lista);
                break;
            case 3:
                buscarDinamico(&lista);
                break;
            case 4:
                emprestarDinamico(&lista);
                break;
            case 5:
                devolverDinamico(&lista);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    liberarLista(&lista);
}

int main(void) {
    User users[qt_max];
    char user[30];
    char senha[100];
    int tentativas = 0;
    int autenticado = 0;

    while (tentativas < 3 && !autenticado) {
        printf("Informe o usuario: ");
        if (scanf("%29s", user) != 1) {
            limparLinha();
            continue;
        }

        printf("Informe a senha: ");
        if (scanf("%99s", senha) != 1) {
            limparLinha();
            continue;
        }
        limparLinha();

        autenticado = login_v(user, senha, users);

        if (!autenticado) {
            tentativas++;
            printf("Usuario ou senha invalido!\n");

            if (tentativas < 3) {
                printf("Restam %d tentativas.\n",
                       3 - tentativas);
            }
        }
    }

    if (!autenticado) {
        printf("Numero maximo de tentativas atingido.\n");
        return 1;
    }

    int opcao;

    do {
        printf("\n============================\n");
        printf("    SISTEMA DE BIBLIOTECA\n");
        printf("============================\n");
        printf("1 - Utilizar lista estatica\n");
        printf("2 - Utilizar lista dinamica\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            limparLinha();
            printf("Entrada invalida!\n");
            continue;
        }
        limparLinha();

        switch (opcao) {
            case 1:
                menuEstatica();
                break;
            case 2:
                menuDinamica();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
