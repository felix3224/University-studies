/*Questão 2:
Implemente uma função chamada processa que recebe um vetor
 de inteiros, seu tamanho e dois callbacks: um para aplicar 
 uma transformação em cada elemento do vetor e outro para 
 definir uma condição de exibição na tela. O programa deve 
 modificar os elementos do vetor conforme o primeiro callback
  e imprimir apenas aqueles que satisfazem o segundo callback.
Teste a função com diferentes combinações, como dobrar os 
valores e exibir apenas os números divisíveis por 5, ou calcular
 o quadrado e exibir apenas os maiores que 50. Joao desenrolado
*/

#include <stdio.h>
#include <stdlib.h>

int duplica(int n);
int cinco_divide(int n);
int ele_vezes_ele(int n);
int maior_cinquenta(int n);
void map(int *vet, int tam, int(*transforma)(int), int(*condicao)(int));


int main() {
    int tam = 5 + rand()%26;
    int vet[tam];

    printf("Vetor original: ");
    for (int i = 0; i < tam; i++) {
        vet[i] = rand()%100;
        printf("%d ", vet[i]);
    }
    
    printf("\n");
    printf("Joao Vitor Bossal\n");
    printf("Dobrar valores e retornar maiores que cinquenta.\n");
    map(vet, tam, duplica, maior_cinquenta);

    printf("\n\n");
    return 0;
}

int duplica(int n) {
    return n * 2;
}

int cinco_divide(int n){
    return n%5==0;
}

int ele_vezes_ele(int n){
    return n*n;
}

int maior_cinquenta(int n){
    return n>50;
}

void map(int *vet, int tam, int(*transforma)(int), int(*condicao)(int)){
        for(int i=0;i<tam;i++){
            vet[i]= transforma(vet[i]);
            if(condicao(vet[i])){
                printf("|%d| ",vet[i]);
            }
        }

}
