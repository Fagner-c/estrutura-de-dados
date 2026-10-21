#include "b.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Descarta o restante da linha de entrada */
static void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Le os dados de um livro */
static void lerDadosLivro(Livro *livro) {
    printf("Titulo: ");
    fgets(livro->titulo, sizeof(livro->titulo), stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(livro->autor, sizeof(livro->autor), stdin);
    livro->autor[strcspn(livro->autor, "\n")] = '\0';

    printf("Ano de publicacao: ");
    scanf("%d", &livro->ano);
    limparEntrada();

    livro->disponivel = 1;
}

/* Exibe os dados de um livro */
static void exibirLivro(Livro livro) {
    printf("\nID: %d\n", livro.id);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano: %d\n", livro.ano);
    printf("Status: %s\n",
           livro.disponivel ? "Disponivel" : "Emprestado");
}

/* =========================
   LISTA ESTATICA
   ========================= */

void cadastrarLivro(Livro livros[], int *quantidade) {
    if (*quantidade >= qt_max) {
        printf("Limite de livros atingido!\n");
        return;
    }

    Livro *novo = &livros[*quantidade];

    novo->id = 1;

    for (int i = 0; i < *quantidade; i++) {
        if (livros[i].id >= novo->id) {
            novo->id = livros[i].id + 1;
        }
    }

    printf("\n=== CADASTRO DE LIVRO ===\n");
    lerDadosLivro(novo);

    (*quantidade)++;

    salvarLivros(livros, *quantidade);
    printf("Livro cadastrado com sucesso!\n");
}

void listarLivros(Livro livros[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        exibirLivro(livros[i]);
    }
}

void buscarLivro(Livro livros[], int quantidade) {
    int id;
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    limparEntrada();

    for (int i = 0; i < quantidade; i++) {
        if (livros[i].id == id) {
            exibirLivro(livros[i]);
            return;
        }
    }

    printf("Livro nao encontrado!\n");
}

void emprestarLivro(Livro livros[], int quantidade) {
    int id;
    printf("ID do livro para emprestar: ");
    scanf("%d", &id);
    limparEntrada();

    for (int i = 0; i < quantidade; i++) {
        if (livros[i].id == id) {
            if (livros[i].disponivel) {
                livros[i].disponivel = 0;
                salvarLivros(livros, quantidade);
                printf("Emprestimo realizado!\n");
            } else {
                printf("Livro ja emprestado!\n");
            }
            return;
        }
    }

    printf("Livro nao encontrado!\n");
}

void devolverLivro(Livro livros[], int quantidade) {
    int id;
    printf("ID do livro para devolver: ");
    scanf("%d", &id);
    limparEntrada();

    for (int i = 0; i < quantidade; i++) {
        if (livros[i].id == id) {
            if (!livros[i].disponivel) {
                livros[i].disponivel = 1;
                salvarLivros(livros, quantidade);
                printf("Devolucao realizada!\n");
            } else {
                printf("Livro ja esta disponivel!\n");
            }
            return;
        }
    }

    printf("Livro nao encontrado!\n");
}

void salvarLivros(Livro livros[], int quantidade) {
    FILE *arquivo = fopen("livros.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar livros!\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d|%s|%s|%d|%d\n",
                livros[i].id,
                livros[i].titulo,
                livros[i].autor,
                livros[i].ano,
                livros[i].disponivel);
    }

    fclose(arquivo);
}

int carregarLivros(Livro livros[]) {
    FILE *arquivo = fopen("livros.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    int quantidade = 0;

    while (quantidade < qt_max &&
           fscanf(arquivo, "%d|%99[^|]|%99[^|]|%d|%d",
                  &livros[quantidade].id,
                  livros[quantidade].titulo,
                  livros[quantidade].autor,
                  &livros[quantidade].ano,
                  &livros[quantidade].disponivel) == 5) {
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

/* =========================
   LOGIN
   ========================= */

int login_v(const char *user, const char *senha,
            User users[]) {
    FILE *arquivo = fopen("users.txt", "r");

    if (arquivo == NULL) {
        printf("Erro: arquivo users.txt nao encontrado.\n");
        return 0;
    }

    int quantidade = 0;

    while (quantidade < qt_max &&
           fscanf(arquivo, "%d|%29[^|]|%99[^|]|%9[^\n]",
                  &users[quantidade].id,
                  users[quantidade].nome,
                  users[quantidade].senha,
                  users[quantidade].tipo) == 4) {
        quantidade++;
    }

    fclose(arquivo);

    for (int i = 0; i < quantidade; i++) {
        if (strcmp(users[i].nome, user) == 0 &&
            strcmp(users[i].senha, senha) == 0) {
            return 1;
        }
    }

    return 0;
}

/* =========================
   LISTA DINAMICA
   ========================= */

void inicializarLista(ListaDinamica *lista) {
    lista->inicio = NULL;
    lista->quantidade = 0;
}

int carregarDinamico(ListaDinamica *lista) {
    FILE *arquivo = fopen("livros.txt", "r");

    if (arquivo == NULL) {
        return 1;
    }

    Livro livro;

    while (fscanf(arquivo, "%d|%99[^|]|%99[^|]|%d|%d",
                  &livro.id, livro.titulo, livro.autor,
                  &livro.ano, &livro.disponivel) == 5) {
        No *novo = malloc(sizeof(No));

        if (novo == NULL) {
            fclose(arquivo);
            return 0;
        }

        novo->livro = livro;
        novo->prox = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = novo;
        } else {
            No *atual = lista->inicio;

            while (atual->prox != NULL) {
                atual = atual->prox;
            }

            atual->prox = novo;
        }

        lista->quantidade++;
    }

    fclose(arquivo);
    return 1;
}

void salvarDinamico(ListaDinamica *lista) {
    FILE *arquivo = fopen("livros.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar livros!\n");
        return;
    }

    No *atual = lista->inicio;

    while (atual != NULL) {
        Livro livro = atual->livro;

        fprintf(arquivo, "%d|%s|%s|%d|%d\n",
                livro.id, livro.titulo, livro.autor,
                livro.ano, livro.disponivel);

        atual = atual->prox;
    }

    fclose(arquivo);
}

void cadastrarDinamico(ListaDinamica *lista) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    novo->livro.id = 1;

    for (No *p = lista->inicio; p != NULL; p = p->prox) {
        if (p->livro.id >= novo->livro.id) {
            novo->livro.id = p->livro.id + 1;
        }
    }

    printf("\n=== CADASTRO DINAMICO ===\n");
    lerDadosLivro(&novo->livro);

    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *atual = lista->inicio;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = novo;
    }

    lista->quantidade++;
    salvarDinamico(lista);

    printf("Livro cadastrado na lista dinamica!\n");
}

void listarDinamico(ListaDinamica *lista) {
    if (lista->inicio == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    No *atual = lista->inicio;

    while (atual != NULL) {
        exibirLivro(atual->livro);
        atual = atual->prox;
    }
}

void buscarDinamico(ListaDinamica *lista) {
    int id;

    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    limparEntrada();

    for (No *p = lista->inicio; p != NULL; p = p->prox) {
        if (p->livro.id == id) {
            exibirLivro(p->livro);
            return;
        }
    }

    printf("Livro nao encontrado!\n");
}

void emprestarDinamico(ListaDinamica *lista) {
    int id;

    printf("ID do livro para emprestar: ");
    scanf("%d", &id);
    limparEntrada();

    for (No *p = lista->inicio; p != NULL; p = p->prox) {
        if (p->livro.id == id) {
            if (p->livro.disponivel) {
                p->livro.disponivel = 0;
                salvarDinamico(lista);
                printf("Emprestimo realizado!\n");
            } else {
                printf("Livro ja emprestado!\n");
            }
            return;
        }
    }

    printf("Livro nao encontrado!\n");
}

void devolverDinamico(ListaDinamica *lista) {
    int id;

    printf("ID do livro para devolver: ");
    scanf("%d", &id);
    limparEntrada();

    for (No *p = lista->inicio; p != NULL; p = p->prox) {
        if (p->livro.id == id) {
            if (!p->livro.disponivel) {
                p->livro.disponivel = 1;
                salvarDinamico(lista);
                printf("Devolucao realizada!\n");
            } else {
                printf("Livro ja esta disponivel!\n");
            }
            return;
        }
    }

    printf("Livro nao encontrado!\n");
}

void liberarLista(ListaDinamica *lista) {
    No *atual = lista->inicio;

    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    lista->inicio = NULL;
    lista->quantidade = 0;
}
