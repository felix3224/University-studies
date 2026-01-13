#include<stdio.h>
#include<stdlib.h>
#include "List_encadeada.h"

int main(){
    // Cria uma nova lista vazia
    Produto* produto = pdt_criar();
    
    // Insere 4 novos produtos na lista
    produto = pdt_insere(produto,pdt_new_element());
    produto = pdt_insere(produto,pdt_new_element());
    produto = pdt_insere(produto,pdt_new_element());
    produto = pdt_insere(produto,pdt_new_element());

    // Busca um produto pelo ID fornecido pelo usuário
    int id;
    scanf("%d",&id);
    if(pdt_buscar(produto, id)){
        printf("Produto encontrado!!!");
    }else{
        printf("Produto nao encontrado");
    }

    // Imprime todos os produtos da lista
    pdt_imprimir(produto);

    // Remove o produto com o ID fornecido
    pdt_retirar(produto, id);

    // Imprime a lista atualizada
    pdt_imprimir(produto);
    
    // Libera a memória alocada
    pdt_liberar(produto);
    return 0;
}