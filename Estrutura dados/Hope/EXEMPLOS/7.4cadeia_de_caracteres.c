#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int lenomes(char** alunos);
char* lelinha();
char* duplica(char* s);
void liberanomes(int n, char** alunos);
void imprimenomes(int n, char** alunos);

int main(){
    char* alunos[MAX];
    
    int n = lenomes(alunos);
    
    imprimenomes(n, alunos);
    liberanomes(n,alunos);

    return 0;
}


int lenomes(char** alunos){
    int n = 0;

    do{
        printf("Digite uma quantidade de nomes (máximo: %d): ", MAX);
        scanf("%d", &n);
    }while(n> MAX);

    for(int i = 0; i < n; i++)
        alunos[i] = lelinha();
    
    return n;
}

char* lelinha(){
    char linha[121];
    
    printf("Digite um nome: ");
    scanf(" %120[^\n]%*c", linha);

    return duplica(linha);
}

int len(char* s){
    int cont = 0; 

    while(s[cont]!= '\0')
        cont++;

    return cont;
}

char* duplica(char* s){

    int i = 0;
    char* nova_string = (char*)malloc((len(s)+1)*sizeof(char));

    for(i = 0; s[i] != '\0'; i++)
        nova_string[i] = s[i];
    
    nova_string[i] = '\0';

    return nova_string;
}

void liberanomes(int n, char** alunos){

    for(int i = 0; i < n; i++)
        free(alunos[i]);
}

void imprimenomes(int n, char** alunos){
    
    printf("\n####Nomes###\n");
    for(int i = 0; i < n; i++)
        printf("%s\n", alunos[i]);

}