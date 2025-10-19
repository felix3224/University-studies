#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_STRING_PADRAO 50

void imprime_rec(char* s);
void imprime_rec_inv(char* s);
int comprimento_rec(char* s);
void copia_rec(char* dest, char* orig);

int main(){
    char linha[TAMANHO_STRING_PADRAO+1] = "Palavra Composta Original";
    char* string_constante = "Palavra Composta Constante Original";

    imprime_rec(linha);
    printf("\n");
    imprime_rec_inv(linha);
    printf("\n");
    imprime_rec(string_constante);
    printf("\n");
    imprime_rec_inv(string_constante);
    printf("\n");
    

    printf("\nUsando as funções: comprimento recursivo e cópia recursiva...\n");
    printf("O comprimento de \"%s\" é %d...\n", linha, comprimento_rec(linha));

    printf("Copiando a string constante para o vetor linha...\n");
    printf("Linha contém \" %s \"", linha);
    copia_rec(linha, string_constante);
    printf("\nLinha agora contém \" %s \"", linha);

    return 0;
}

void imprime_rec(char* s){
    if (s[0] != '\0'){
        printf("%c", s[0]);
        imprime_rec(&s[1]);
    }
}

void imprime_rec_inv(char* s){
    if (s[0] != '\0'){
        imprime_rec_inv(&s[1]);
        printf("%c", s[0]);
    }
}

int comprimento_rec(char* s){
    if(s[0]=='\0')
        return 0;
    else
        return 1 + comprimento_rec(&s[1]);
}

void copia_rec(char* dest, char* orig){
    if(orig[0] != '\0'){
        dest[0] = orig[0];
        copia_rec(&dest[1], &orig[1]);
    }
    else{
        dest[0] = orig[0];
    }

}
