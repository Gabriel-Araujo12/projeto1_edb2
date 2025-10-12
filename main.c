#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "categoria.h"
#include "heap.h"
#include "livro.h"

int main(){
    No* arvore = NULL;
    No* categoria = NULL;
    int opcao;

    do{
        printf("[1] Carregar categorias\n");
        printf("[2] Listar categorias\n");
        printf("[3] Selecionar categoria\n");
        printf("[4] Mostrar Top 1 livro mais vendido\n");
        printf("[5] Listar Top N livros mais vendidos\n");
        printf("[6] Registrar venda\n");
        printf("[0] Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(arvore != NULL){
                    liberarArvore(arvore);
                    categoria = NULL;
                }

                arvore = carregarCategoria("ArquivosCSV/categorias.csv");

                if(arvore != NULL){
                    printf("\n---> Categorias carregadas com sucesso!\n\n");
                }

                break;

            case 2:
                if(arvore == NULL){
                    printf("\n---> As categorias ainda não foram carregadas!\n\n");
                } 

                else{
                    printf("\n-------------- Categorias Em Ordem Alfabética --------------\n");
                    emOrdem(arvore);
                    printf("------------------------------------------------------------\n\n");
                }
                
                break;

            case 3:
                if(arvore == NULL){
                    printf("\n---> As categorias ainda não foram carregadas!\n\n");
                } 

                else{
                    char nomeCategoria[100];
                    printf("Digite o nome da categoria que deseja selecionar: ");
                    scanf(" %[^\n]", nomeCategoria);

                    categoria = buscar(arvore, nomeCategoria);

                    if(categoria != NULL){
                        printf("\n---> A categoria foi selecionada!\n\n");
                        carregarLivro(&categoria->c);
                    } 
                    else{
                        printf("\n---> A categoria não foi encontrada!\n\n");
                    }
                }

                break;

            case 4:
                if(categoria == NULL){
                    printf("\n---> Nenhuma categoria foi selecionada!\n\n");
                }
                else{
                    Livro top = buscarRaiz(categoria->c.livros);

                    if(top.isbn != 0){
                        printf("\n----------------- Top 1 Livro Mais Vendido -----------------\n\n");
                        exibirLivro(top);
                        printf("\n------------------------------------------------------------\n\n");
                    }
                }

                break;

            case 5:
                if(categoria == NULL){
                    printf("\n---> Nenhuma categoria foi selecionada!\n\n");
                } 
                else{
                    int n;

                    printf("Digite o valor de N para o Top N: ");
                    scanf("%d", &n);

                    buscarN(categoria->c.livros, n);
                }

                break;

            case 6:
                if(categoria == NULL){
                    printf("\n---> Nenhuma categoria foi selecionada!\n\n");
                } 
                else{
                    int isbn, quantidade;

                    printf("Digite o ISBN do livro vendido: ");
                    scanf("%d", &isbn);
                    printf("Digite a quantidade vendida: ");
                    scanf("%d", &quantidade);

                    atualizarVendas(categoria->c.livros, isbn, quantidade);
                }

                break;

            case 0:
                printf("\n---> Encerrando o Sistema de Livraria!\n\n");
                liberarArvore(arvore);

                break;

            default:
                printf("\n---> Opção inválida!\n\n");

                break;
        }

    }while(opcao != 0);

    return 0;
}