#include <stdio.h>
#include "../TAD_INTEIRO/TAD_INTEIRO.h"

int main() {
    printf("Criando um lista de Inteiros!\n");
    Lista* minha_lista = lst_cria();

    for(int i=0; i<5; i++)
        minha_lista = lst_insere(minha_lista, i);

    if(lst_vazia(minha_lista))
        printf("Minha lista está vazia!\n");
    else{
        printf("Lista de Números interios:\n");
        lst_imprime(minha_lista);
    }
        
    //minha_lista=lst_libera(minha_lista);

    minha_lista=lst_retira(minha_lista, 3);
    minha_lista=lst_retira(minha_lista, 10);

    if(lst_vazia(minha_lista))
        printf("Minha lista está vazia!\n");
    else{
        printf("Lista de Números interios:\n");
        lst_imprime(minha_lista);
    }

    printf("Procurando o valor 20: ");

    if(lst_busca(minha_lista, 20) != NULL)
        printf("encontrei!");
    else    
        printf("não encontrei...");

    return 0;
}
