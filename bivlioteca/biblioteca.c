#include "biblioteca.h"
int main() {
    int c = 0;
    User users[qt_max];
    char user[30]; 
    char senha[100];
   
    do{
         printf("Informe o usuario: ");
        scanf("%s", &user);
        printf("Informe a senha: ");
        scanf("%s", &senha);
        int login = login_v(user, senha, users);
        if(login == 1){
            Livro livros[qt_max];
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
                if(opcao == 0){
                    return 0;
                }
            } while (opcao != 0);
        }
        c++;
        printf("senha ou usuario invalido!\n Resta %d tentativas\n",(3 - c));
    }while(c < 3);
    return 0;
}