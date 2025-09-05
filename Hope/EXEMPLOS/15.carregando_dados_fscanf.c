#include <stdio.h>
#include <string.h>

typedef struct pessoa
{
    char nome[121];
    char idade[10];
    char profissao[51];
}Pessoa;

int main(){

    FILE* arquivo_entrada = fopen("arquivo_texto.txt", "rt");
    char linha_recuperada[121];
    int n_linha = 0;
    int qtd_registro =0;

    Pessoa registros[5];

    if(!arquivo_entrada){
        printf("Erro ao abrir o arquivo...");
   }

    printf("\nArquivo abriu com sucesso!\n");

    // Ler o arquivo linha a linha e guardar em um registro nosso.
    int i = 0;
    // Neste exemplo o fscanf retorna a quantidade de elementos lidos com sucesso,
    // -1 caso encontre EOF ou dê erro.
    while(fscanf(arquivo_entrada, "%120s", linha_recuperada)==1){
        n_linha++;

            switch(i%3){
            case 0:
                strcpy(registros[qtd_registro].nome, linha_recuperada);
                break;
            case 1:
                strcpy(registros[qtd_registro].idade, linha_recuperada);
                break;
            case 2:
                strcpy(registros[qtd_registro].profissao, linha_recuperada);
                qtd_registro++;
                break;
            }

        i++;
    }

    for(i = 0; i <qtd_registro; i++){
        printf("\nRegistro %d ====", i+1);
        printf("\nNome: %s", registros[i].nome);
        printf("\nIdade: %s", registros[i].idade);
        printf("\nProfissão: %s", registros[i].profissao);
        printf("\n================");
    }

    fclose(arquivo_entrada);
    
    return 0;
}