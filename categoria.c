#include "categoria.h"


Categoria criarCategoria(int id, char *nome, char *arquivo){
    Categoria c;
    c.id = id;
    strcpy(c.nome, nome);
    strcpy(c.arquivo, arquivo);
    c.livros = NULL;

    return c;
}

void exibirCategoria(Categoria c){
    printf("ID: %d | Nome: %s\n", c.id, c.nome);
}

void carregarLivro(Categoria* c){
    if (c == NULL){
        printf("\n---> Não há nenhuma categoria listada!\n\n");

        return;
    }

    if (c->livros != NULL) {
        liberarHeap(c->livros);
    }

    char arquivos[300];
    sprintf(arquivos, "ArquivosCSV/%s", c->arquivo);
    FILE* arquivo = fopen(arquivos, "r");

    if(arquivo == NULL){
        printf("\n---> Não foi possível abrir o arquivo!\n\n");
        c->livros = NULL;

        return;
    }

    int numLinhas = 0;
    char linha[512];
    fgets(linha, sizeof(linha), arquivo);

    while(fgets(linha, sizeof(linha), arquivo)){
        numLinhas++;
    }

    rewind(arquivo);

    if(numLinhas == 0){
        printf("\n---> Não há nenhum livro para carregar!\n\n");
        c->livros = NULL;
        fclose(arquivo);

        return;
    }
    
    c->livros = criarHeap(numLinhas);
    fgets(linha, sizeof(linha), arquivo);

    while(fgets(linha, sizeof(linha), arquivo)){
        int isbn, ano, estoque, vendas;
        char titulo[200], autor[200];
        float preco;

        if(sscanf(linha, "%d;%199[^;];%199[^;];%d;%f;%d;%d", &isbn, titulo, autor, &ano, &preco, &estoque, &vendas) == 7){
            Livro l = criarLivro(isbn, titulo, autor, ano, preco, estoque, vendas);
            inserirLivro(c->livros, l);
        }
    }

    fclose(arquivo);
}