#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "categoria.h"
#include "heap.h"
#include "livro.h"

// --- Protótipos das Funções Auxiliares ---

/**
 * @brief Carrega as categorias do arquivo CSV para a Árvore Binária de Busca.
 * @return A raiz da árvore de categorias preenchida.
 */
No* carregarCategoriasDaFonte();

/**
 * @brief Carrega os livros de um arquivo CSV específico para a heap de uma categoria.
 * @param noCategoria Ponteiro para o nó da categoria que receberá os livros.
 */
void carregarLivrosParaCategoria(No* noCategoria);

/**
 * @brief Libera todos os recursos alocados (heaps e a árvore).
 * @param r A raiz da árvore de categorias.
 */
void liberarRecursos(No* r);

// --- Função Principal ---

int main() {
    No* arvoreCategorias = NULL;
    No* categoriaSelecionada = NULL;
    int opcao;

    do {
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

        switch (opcao) {
            case 1:
                // Libera a árvore antiga se o usuário carregar novamente
                if (arvoreCategorias != NULL) {
                    liberarRecursos(arvoreCategorias);
                    categoriaSelecionada = NULL;
                }
                arvoreCategorias = carregarCategoriasDaFonte();
                if (arvoreCategorias != NULL) {
                    printf("Categorias carregadas com sucesso!\n");
                }
                break;

            case 2:
                if (arvoreCategorias == NULL) {
                    printf("Por favor, carregue as categorias primeiro (Opcao 1).\n");
                } else {
                    printf("\n--- Categorias Disponiveis (em ordem alfabetica) ---\n");
                    emOrdem(arvoreCategorias);
                    printf("----------------------------------------------------\n");
                }
                break;

            case 3:
                if (arvoreCategorias == NULL) {
                    printf("Por favor, carregue as categorias primeiro (Opcao 1).\n");
                } else {
                    char nomeCategoria[100];
                    printf("Digite o nome da categoria que deseja selecionar: ");
                    // O " " antes de % é para consumir newlines pendentes do scanf anterior
                    scanf(" %[^\n]", nomeCategoria);

                    categoriaSelecionada = buscar(arvoreCategorias, nomeCategoria);

                    if (categoriaSelecionada != NULL) {
                        printf("Categoria '%s' selecionada.\n", nomeCategoria);
                        carregarLivrosParaCategoria(categoriaSelecionada);
                    } else {
                        printf("Categoria '%s' nao encontrada.\n", nomeCategoria);
                    }
                }
                break;

            case 4:
                if (categoriaSelecionada == NULL) {
                    printf("Por favor, selecione uma categoria primeiro (Opcao 3).\n");
                } else {
                    Livro top1 = buscarRaiz(categoriaSelecionada->c.livros);
                    if (top1.isbn != 0) { // Verifica se não é um livro vazio
                        printf("\n--- Livro Mais Vendido ---\n");
                        exibirLivro(top1);
                        printf("--------------------------\n");
                    }
                }
                break;

            case 5:
                if (categoriaSelecionada == NULL) {
                    printf("Por favor, selecione uma categoria primeiro (Opcao 3).\n");
                } else {
                    int n;
                    printf("Digite o valor de N para o Top N: ");
                    scanf("%d", &n);
                    buscarN(categoriaSelecionada->c.livros, n);
                }
                break;

            case 6:
                if (categoriaSelecionada == NULL) {
                    printf("Por favor, selecione uma categoria primeiro (Opcao 3).\n");
                } else {
                    int isbn, quantidade;
                    printf("Digite o ISBN do livro vendido: ");
                    scanf("%d", &isbn);
                    printf("Digite a quantidade vendida: ");
                    scanf("%d", &quantidade);
                    atualizarVendas(categoriaSelecionada->c.livros, isbn, quantidade);
                }
                break;

            case 0:
                printf("Encerrando o sistema. Ate mais!\n");
                liberarRecursos(arvoreCategorias);
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções Auxiliares ---

No* carregarCategoriasDaFonte() {
    FILE* arquivo = fopen("ArquivosCSV/categorias.csv", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo 'ArquivosCSV/categorias.csv'");
        return NULL;
    }

    No* raiz = NULL;
    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        int id;
        char nome[100];
        char arquivoLivros[100];

        // Usando sscanf para parsear a linha
        if (sscanf(linha, "%d;%99[^;];%99[^\n]", &id, nome, arquivoLivros) == 3) {
            Categoria c = criarCategoria(id, nome, arquivoLivros);
            raiz = inserirCategoria(raiz, c);
        }
    }

    fclose(arquivo);
    return raiz;
}

void carregarLivrosParaCategoria(No* noCategoria) {
    // Se já existirem livros carregados para esta categoria, libera a heap antiga
    if (noCategoria->c.livros != NULL) {
        liberarHeap(noCategoria->c.livros);
        noCategoria->c.livros = NULL;
    }

    char caminhoArquivo[200];
    sprintf(caminhoArquivo, "ArquivosCSV/%s", noCategoria->c.arquivo);

    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo de livros: %s\n", caminhoArquivo);
        return;
    }

    // Contar linhas para determinar a capacidade da heap
    int numLinhas = 0;
    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho
    while(fgets(linha, sizeof(linha), arquivo)) {
        numLinhas++;
    }
    rewind(arquivo); // Volta para o início do arquivo

    if (numLinhas == 0) {
        printf("Aviso: O arquivo '%s' esta vazio ou nao contem livros.\n", caminhoArquivo);
        fclose(arquivo);
        return;
    }

    noCategoria->c.livros = criarHeap(numLinhas);
    
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho novamente

    while (fgets(linha, sizeof(linha), arquivo)) {
        int isbn, ano, estoque, vendas;
        char titulo[200], autor[200];
        float preco;

        if (sscanf(linha, "%d;%199[^;];%199[^;];%d;%f;%d;%d", &isbn, titulo, autor, &ano, &preco, &estoque, &vendas) == 7) {
            Livro l = criarLivro(isbn, titulo, autor, ano, preco, estoque, vendas);
            inserirLivro(noCategoria->c.livros, l);
        }
    }
    
    printf("Livros da categoria '%s' carregados.\n", noCategoria->c.nome);
    fclose(arquivo);
}

void liberarRecursos(No* r) {
    if (r == NULL) {
        return;
    }
    // Percorre a árvore em pós-ordem para liberar os filhos primeiro
    liberarRecursos(r->esq);
    liberarRecursos(r->dir);

    // Antes de liberar o nó da categoria, libera a heap de livros associada a ele
    if (r->c.livros != NULL) {
        liberarHeap(r->c.livros);
    }
    free(r); // Libera o nó da árvore
}