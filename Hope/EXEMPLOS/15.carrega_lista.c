#include <stdio.h>
#include <stdlib.h>
#include "../TAD_LISTA/TAD_LISTA.h"


void formatacao(void* elemento);
void* ler_linha(char* linha_arquivo);
char* montar_linha(void* elemento);

typedef struct contato{
    char nome[81];
    char telefone[15];
} Contato;

int main(int argc, char* argv[]){

    Lista* minha_lista = lst_cria();

    // Carrega dados da memória secundária na memória principal
    minha_lista = lst_carrega(minha_lista, "arquivo_contatos.txt", ler_linha);

    printf("=> Nossa lista CARREGADA DA MEMÓRIA!!!\n\
        Faremos uma lista de contatos.\n");

    // Imprime a lista de inteiros criada.
    lst_imprime(minha_lista, formatacao);

    // Grava os dados da memória principal para a secundária.
    lst_grava(minha_lista, "arquivo_contatos.txt", montar_linha);

    // Liberando a lista completa.
    printf("\n\nLiberando minha Lista de CONTATOS...\n");
    
    minha_lista = lst_libera(minha_lista);

    if(lst_vazia(minha_lista))
        printf("\nLista liberada com sucesso...\n");
    else
        printf("\nLista não liberou memória corretamente...\n");
    
    return 0;
}

// Funções ÚTEIS
// Define o formato e imprime elemento da lista genérica.
void formatacao(void* elemento){
    Contato* contato = (Contato*)elemento;
    printf("| %s | %s |\n", contato->nome, contato->telefone);
}

// Processa a linha do arquivo e
// retorna um ponteiro para a estrutura com os dados inseridos nela.
void* ler_linha(char* linha_arquivo){
    // Aloca a memória para receber os dados presentes em linha_arquivo
    Contato* novo_contato = (Contato*)malloc(sizeof(Contato));

    // Copia os caracteres de linha_arquivo enquanto não
    // encontra o caracter de separação ';'
    int i=0;
    while(linha_arquivo[i] != ';'){
        novo_contato->nome[i] = linha_arquivo[i];
        i++;
    }

    // Fecha a string nome.
    novo_contato->nome[i] = '\0';

    // Vai para o próximo caracter em linha_arquivo.
    i++;

    int j=0;
    while(linha_arquivo[i] != '\n' && linha_arquivo[i] != '\0'){
        novo_contato->telefone[j] = linha_arquivo[i];
        i++;
        j++;
    }

    // Fecha a string telefone
    novo_contato->telefone[j] = '\0';

    // Retorna a estrutura como void* para ser guardada na lista.
    return (void*)novo_contato;
}

char* montar_linha(void* elemento){
    
    Contato* contato = (Contato*)elemento;
    char* linha = (char*)malloc((81 + 15 + 2)*sizeof(char));
    
    if(!linha)
        NULL;
    
    // Pecorre a estrutura elemento montando a string linha
    // que será escrita no arquivo.
    // Campo NOME
    int i = 0;
    while(contato->nome[i] != '\0'){
        linha[i] = contato->nome[i];
        i++;
    }
    
    // Fim dos caracteres do campo NOME
    linha[i]=';';
    i++;
    
    // Campo TELEFONE
    int j = 0;
    while(contato->telefone[j] != '\0'){
        linha[i] = contato->telefone[j];
        j++;
        i++;
    }

    // Fim dos caracteres do campo TELEFONE
    linha[i]='\n';
    // Fecha a string.
    linha[i+1]='\0';

    return linha;
}