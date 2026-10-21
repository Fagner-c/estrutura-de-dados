
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#define qt_max 100

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int disponivel;
} Livro;

typedef struct {
    int id;
    char nome[30];
    char senha[100];
    char tipo[10];
} User;

/* Lista dinamica */
typedef struct No {
    Livro livro;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    int quantidade;
} ListaDinamica;

/* Funcoes da lista estatica */
void cadastrarLivro(Livro livros[], int *quantidade);
void listarLivros(Livro livros[], int quantidade);
void buscarLivro(Livro livros[], int quantidade);
void emprestarLivro(Livro livros[], int quantidade);
void devolverLivro(Livro livros[], int quantidade);
void salvarLivros(Livro livros[], int quantidade);
int carregarLivros(Livro livros[]);

/* Funcoes de usuario */
int login_v(const char *user, const char *senha,
            User users[]);

/* Funcoes da lista dinamica */
void inicializarLista(ListaDinamica *lista);
int carregarDinamico(ListaDinamica *lista);
void salvarDinamico(ListaDinamica *lista);
void cadastrarDinamico(ListaDinamica *lista);
void listarDinamico(ListaDinamica *lista);
void buscarDinamico(ListaDinamica *lista);
void emprestarDinamico(ListaDinamica *lista);
void devolverDinamico(ListaDinamica *lista);
void liberarLista(ListaDinamica *lista);

#endif
