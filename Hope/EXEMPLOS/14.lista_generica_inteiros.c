#include <stdio.h>
#include <stdlib.h>
#include "../TAD_LISTA/TAD_LISTA.h"

int verifica_posicao(void* elemento_posicao, void* elemento_inserir);
int todos_elementos(void* elemento_posicao);
int elementos_impares(void* elemento_posicao);
int se_igual(void* elemento1, void* elemento2);
void duplica(void* elemento);
void formatacao(void* elemento);

int main(int argc, char* argv[]){
    
    int qtd_elementos=0;

    Lista* minha_lista = lst_cria();

    printf("=> Nossa lista genérica!!!\n\
        Faremos uma lista de números INTEIROS.");

    printf("\nDigite a quantidade de elementos\n\
         INTEIROS que quer inserir na LISTA: ");
    scanf("%d%*c", &qtd_elementos);
    
    // Inserindo inteiros na minha lista.
    int* novo_elemento;

    for(int i = 0; i < qtd_elementos; i++){
        // Alocando a memória para acondicionar um inteiro.
        novo_elemento = (int*)malloc(sizeof(int));
        // Escolhendo um inteiro aleatoriamente no intervalo de 0 a 100
        *novo_elemento = rand()%101;
        // Insere o elemento na lista.
        minha_lista = lst_insere(minha_lista, (void*)novo_elemento, verifica_posicao);
    }

    // Imprime a lista de inteiros criada.
    lst_imprime(minha_lista, formatacao);

    // Excluir um número inteiro.
    int* elemento_exclusao = (int*)malloc(sizeof(int));

    printf("\nDigite um número INTEIRO para excluir: ");
    scanf("%d%*c", elemento_exclusao);

    minha_lista = lst_retira(minha_lista, (void*)elemento_exclusao, se_igual);
    
    // Imprime minha lista após exclusão do elemento.

    printf("\nMinha lista após exclusão: \n");
    lst_imprime(minha_lista, formatacao);

    //Buscar um número inteiro.
    int* elemento_busca = (int*)malloc(sizeof(int));
    Lista* elemento_encontrado = NULL;

    printf("\nDigite um número para buscar: ");
    scanf("%d%*c", elemento_busca);

    elemento_encontrado = lst_busca(minha_lista, (void*)elemento_busca, se_igual);

    if (elemento_encontrado)
        printf("\nElemento %d encontrado!\n", *((int*)(elemento_encontrado->info)));
    else
        printf("\nElemento não encontrado!\n");
    
    // Utilizando a função MAP para duplicar os elementos da minha lista
    printf("\n\nUtilizando a função MAP para duplicar a lista de inteiros...\n");

    if(lst_map(minha_lista, duplica, todos_elementos))
        lst_imprime(minha_lista, formatacao);

    
    // Liberando a lista completa.
    printf("\n\nLiberando minha Lista de INTEIROS...\n");
    
    minha_lista = lst_libera(minha_lista);

    if(lst_vazia(minha_lista))
        printf("\nLista liberada com sucesso...\n");
    else
        printf("\nLista não liberou memória corretamente...\n");
    
    return 0;
}

// Funções ÚTEIS
// Retorna a verificação lógica para saber se a posição de inserção 
// do novo elemento na lista é aceitável. Retorna 1 para aceitável ou
// 0 para não.
int verifica_posicao(void* elemento_posicao, void* elemento_inserir){
    return (int)elemento_posicao > (int)elemento_inserir;
}

// Define o formato e imprime elemento da lista genérica.
void formatacao(void* elemento){
    printf("| %d |", *((int*)elemento));
}

// Retorna a verificação lógica para identificar que
// todos os valores são para impressão.
int todos_elementos(void* elemento){
    return 1;
}

// Retorna a verificação lógica para identificar
// os elementos ímpares para impressão.
int elementos_impares(void* elemento){
    if (*((int*)elemento) % 2 != 0)
        return 1;
    else
        return 0;
}

// Retorna a verificação lógica para identificar
// se os elementos 1 e 2 são iguais.
int se_igual(void* elemento1, void* elemento2){
    return *(int*)elemento1 == *((int*)elemento2);
}

// Duplica um elemento inteiro repassado como
// ponteior para void.
void duplica(void* elemento){
    *(int*)elemento = 2 * (*(int*)elemento);
}