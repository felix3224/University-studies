#include <stdio.h>
#include <locale.h>

int digito(char c);
char maiuscula(char c);

int main(){
    // Define a linguagem
    setlocale(LC_ALL, "pt_BR.UTF-8");

    char c = 'a';
    printf("\n%d => %c\n\n", c, c);
    
    // Tarefinha de Casa: crie uma função para imprimir caracter em binário.
    // void print_binario(char c);

    c='d';

    if(digito(c))
        printf("\nO caracter \"%c\" é um dígito.\n", c);
    else
        printf("\nO caracter \"%c\" NÃO é um dígito e seu correspondente maiúsculo é %c.\n", c, maiuscula(c));

        
    return 0;
}

int digito(char c){
    return '0' <= c && c <= '9';
}

char maiuscula(char c){
    if( 'a' <= c && c <= 'z' )
        c = c-'a'+'A';
    
    return c;
}