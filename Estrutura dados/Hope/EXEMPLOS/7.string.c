#include <stdio.h>
#include <locale.h>

int digito(char c);
char maiuscula(char c);

int main(){
    // Define a linguagem
    setlocale(LC_ALL, "pt_BR.UTF-8");

    char cidade[8] = {'A', 'r', 'a', 'c', 'a', 't', 'i', '\0'};
    char city[] = "Aracati";

    
    for(int i = 0 ; cidade[i]!= '\0'; i++)
    printf("%c", cidade[i]);
    
    printf("\n");
    
    printf("%s\n\n", city);
    
    // Cadeia de caracteres constantes.
    char* segunda = "segunda-feira";

    printf("\n%s\n\n", segunda);

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