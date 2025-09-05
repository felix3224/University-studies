
/*EXERCÍCIOS:
Questão 1:
Crie uma função chamada transforma que recebe um vetor de 
inteiros, seu tamanho e um callback que realiza uma operação 
matemática sobre cada elemento do vetor. O vetor deve ser 
modificado diretamente pela função. Teste transforma() com 
diferentes callbacks, como dobrar os valores, calcular o 
quadrado de cada número e inverter o sinal dos elementos.  #VAVA
*/

#include <stdio.h>

int dobra(int n);
int quadrado(int n);
int inverte(int n);
void transforma(int *vet, int tam, int (*operacao)(int));

int main(){
    int vet[] = {1,2,3,4,5,6,7};
    
    transforma(vet, sizeof(vet)/sizeof(int), inverte);

    for(int i=0;i<sizeof(vet)/sizeof(int); i++){
        printf("%d ", vet[i]);
    }

    return 0;
}

void transforma(int *vet, int tam, int(*operacao)(int)){
    for(int i=0; i<tam; i++){
        vet[i] = operacao(vet[i]);
    }
}

int dobra(int n){
    return 2*n;
}

int quadrado(int n){
    return n*n;
}

int inverte(int n){
    return -n;
}