#include <stdio.h>
// Utilizando enumeração
enum t_dado{
    triangulo,
    retangulo,
    quadrado
};

// Utilizando define e unsigned char.
#define tri 0
#define qua 1
#define ret 2

typedef unsigned char T_dado;

int main(){

    enum t_dado tipo = retangulo;
    T_dado Tipo = ret;

    printf("Usando enum\n");
    printf("tipo: %u\n", tipo);
    printf("quantidade de Bytes usados: %d", sizeof(T_dado));

    printf("Usando #define e Unsigned Char\n");
    printf("tipo: %u\n", Tipo);
    printf("Quantidade de Bytes usados: %d", sizeof(T_dado));

    


    return 0;
}