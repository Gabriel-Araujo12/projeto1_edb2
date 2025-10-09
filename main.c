#include "categoria.h"
#include "livro.h"
#include "arvore.h"
#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerCategorias(){

}

void lerLivros(){
    
}

int main(){
    int opcao;

    do{
        printf("\n========= MENU =========\n");
        printf("[1] Carregar categorias\n");
        printf("[2] Listar categorias\n");
        printf("[3] Selecionar categoria\n");
        printf("[4] Mostrar Top 1 livro mais vendido\n");
        printf("[5] Listar Top N livros mais vendidos\n");
        printf("[6] Registrar venda\n");
        printf("[0] Sair\n");
        printf("========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 0:
                
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }

    }while (opcao != 0);

    return 0;
}