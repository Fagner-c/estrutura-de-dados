#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#define MAX_LIVROS 100

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int disponivel;
} Livro;

// Funções
void cadastrarLivro(Livro *livros, int *quantidade);
void listarLivros(Livro *livros, int quantidade);
void buscarLivro(Livro *livros, int quantidade);
void emprestarLivro(Livro *livros, int quantidade);
void devolverLivro(Livro *livros, int quantidade);

void salvarLivros(Livro *livros, int quantidade);
int carregarLivros(Livro *livros);

#endif