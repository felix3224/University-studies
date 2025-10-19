#include <stdio.h>

int comprimento(char* string);

int main(){

    char cidade[51] = {'\0'};
    char rua[81] = {'\0'};
    
    printf("Digite o nome da cidade: ");
    scanf("%50[^\n]%*c", cidade);

    printf("%s tem %d caracreres...\n", cidade, comprimento(cidade));
    
    printf("Digite o nome da rua: ");
    scanf("%80[^\n]%*c", rua);

    printf("%s tem %d caracreres...\n", rua, comprimento(rua));

    return 0;
}

int comprimento(char* string){
    int comp = 0;
    for(int i =0; string[i] != '\0'; i++, comp++);

    return comp;
}