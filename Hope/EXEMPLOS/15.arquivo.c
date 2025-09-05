#include <stdio.h>

int main(int qtd_param, char* param[]){

    if (qtd_param == 2){
        char* nome_arquivo = param[1];

        FILE* fp = fopen(nome_arquivo, "rt");
        
        if(!fp){
            printf("Erro ao abrir o arquivo: %s", nome_arquivo);
            exit(1);
        }

        printf("\nArquivo abriu com sucesso!\n");

        FILE* saida = fopen("saida.txt", "wt");

        if(!saida){
            printf("Erro ao abrir o arquivo: saida.txt");
            exit(1);
        }

        int c = 0;
        int nlinhas = 0;

        while((c = fgetc(fp)) != EOF){
            if(c == '\n')
                nlinhas++;
            
            if((int)'A' <= c && c <= (int)'Z')
                c = c - (int)'A' + (int)'a';

            fputc(c, saida);
        }
        
        printf("Foram processadas  %d linhas no arquivo %s...\n", nlinhas + 1, nome_arquivo);
        
        fclose(fp);
        fclose(saida);
    }
    return 0;
}