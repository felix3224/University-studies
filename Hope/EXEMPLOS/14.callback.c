#include <stdio.h>

int soma(int a, int b);
int sub(int a, int b);
void exec(int a, int b, int (*func)(int, int));

int impar(int a);
int par(int a);
int primo(int a);

void imprime(int* v, int tam, int (*condicao)(int));

int main(){

    // Exemplo inicial: exec uma função qualquer
    // recebendo dois números, imprimindo o resultado
    // na tela.
    // exec(4,2,soma);
    // exec(4,2,sub);

    // Exemplo percorrendo um vetor.
    int vetor[]={1,2,10,11,25,33,40};
    int tam = sizeof(vetor)/sizeof(int);

    printf("\nImprimindo os primos: ");
    imprime(vetor, tam, primo);
    printf("\nImprimindo os ímpares: ");
    imprime(vetor, tam, impar);
    printf("\nImprimindo os pares: ");
    imprime(vetor, tam, par);

    return 0;
}

int soma(int a, int b){
    return a+b;
}
int sub(int a, int b){
    return a-b;
}
void exec(int a, int b, int (*func)(int, int)){
    printf("%d\n",func(a,b));
}

int impar(int a){
    return a % 2 == 1;
}

int par(int a){
    return a % 2 == 0;
}

int primo(int a){

    if(a == 1)
        return 0;

    for(int i = 2; i <= a/2; i++)
        if(a%i == 0)
            return 0;
    
    return 1;
}

void imprime(int* v, int tam, int (*condicao)(int)){

    for(int i=0; i<tam; i++)
        if(condicao(v[i]))
            printf("%d ", v[i]);
    
    printf("\n");
}

/*EXERCÍCIOS:
Questão 1:
Crie uma função chamada transforma que recebe um vetor de 
inteiros, seu tamanho e um callback que realiza uma operação 
matemática sobre cada elemento do vetor. O vetor deve ser 
modificado diretamente pela função. Teste transforma() com 
diferentes callbacks, como dobrar os valores, calcular o 
quadrado de cada número e inverter o sinal dos elementos.

Questão 2:
Implemente uma função chamada processa que recebe um vetor
 de inteiros, seu tamanho e dois callbacks: um para aplicar 
 uma transformação em cada elemento do vetor e outro para 
 definir uma condição de exibição na tela. O programa deve 
 modificar os elementos do vetor conforme o primeiro callback
  e imprimir apenas aqueles que satisfazem o segundo callback.
Teste a função com diferentes combinações, como dobrar os 
valores e exibir apenas os números divisíveis por 5, ou calcular
 o quadrado e exibir apenas os maiores que 50.
*/