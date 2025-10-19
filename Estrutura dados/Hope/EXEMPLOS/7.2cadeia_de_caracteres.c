#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_STRING_PADRAO 50

void copia(char* destino, char* origem);
void concatena(char* destino, char* origem);
int compara(char* string1, char* string2);
char* duplica(char* string1);


int main(){
    char linha[TAMANHO_STRING_PADRAO+1] = "Palavra de Origem";
    char* string_final = "Palavra de Origem...";

    char* linha_duplicada = (char*)malloc((TAMANHO_STRING_PADRAO+1)*sizeof(char));

    copia(linha_duplicada, linha);

    printf("%s\n", linha_duplicada);

    concatena(linha_duplicada, string_final);

    printf("%s\n", linha_duplicada);
    
    switch(compara(linha, string_final)){
        case -1: printf("%s < %s\n",linha, string_final);
        break;
        case 0: printf("%s é igual a %s\n",linha, string_final);
        break;
        case 1: printf("%s < %s\n", string_final, linha);
        break;
    }

    char* string_duplicada = duplica(string_final);

    printf("%s\n", string_duplicada);

    return 0;
}

void copia(char* destino, char* origem){
    for(int i=0; origem[i] != '\0'; i++, destino[i] = '\0')
        destino[i] = origem[i];
}

void concatena(char* destino, char* origem){

    int i=0, j=0;

    for(i=0; destino[i]!='\0'; i++);

    for(j=0; origem[j] != '\0'; j++, i++, destino[i]='\0')
        destino[i] = origem[j];
}

int compara(char* string1, char* string2){
    int i = 0;
    
    for(i=0; string1[i] != '\0' && string2[i]!= '\0'; i++)
        if (string1[i] < string2[i])
            return -1;
        else if (string1[i] > string2[i])
            return 1;
    
    if(string1[i] == string2[i])
        return 0;

    if(string1[i]=='\0')
        return -1;
    
    if(string2[i]=='\0')
        return 1;
}

char* duplica(char* string1){
    int i = 0;
    for(i=0;string1[i]!= '\0'; i++);

    char* string2 = (char*)malloc((i+1)*sizeof(char));

    for(int j=0; string1[j] != '\0'; j++, string2[j]='\0')
        string2[j] = string1[j];
    
    return string2;
}