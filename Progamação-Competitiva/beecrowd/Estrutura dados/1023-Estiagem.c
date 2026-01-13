#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, x, y;
    int cidade = 1;
    int primeiro_caso = 1;
    
    while (scanf("%d", &n) && n != 0) {
        int consumo[201] = {0}; // Inicializa com zeros
        int total_pessoas = 0;
        int total_consumo = 0;
        
        // Ler dados dos imóveis
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            
            total_pessoas += x;
            total_consumo += y;
            
            // Calcular consumo por pessoa (arredondado para baixo)
            int consumo_pp = y / x;
            //Agrupar as pessoas com consumo iguais e ja organiza em ordem crescente com a tabela hash
            consumo[consumo_pp] += x;
        }
        
        // Imprimir resultado
        if (!primeiro_caso) {
            printf("\n");
        }
        primeiro_caso = 0;
        
        printf("Cidade# %d:\n", cidade++);
        
        // Imprimir grupos em ordem ascendente
        int first = 1;
        for (int i = 0; i < 201; i++) {
            if (consumo[i] > 0) {
                if (!first) {
                    printf(" ");
                }   
                first = 0;
                printf("%d-%d", consumo[i], i);
            }
        }
        
        // Calcular consumo médio (truncado para 2 casas decimais)
        double consumo_medio = (double)total_consumo / total_pessoas;
        // Truque para truncar sem arredondar
        int temp = (int)(consumo_medio * 100);
        consumo_medio = temp / 100.0;
        
        printf("\nConsumo medio: %.2lf m3.\n", consumo_medio);
    }
    
    return 0;
}