#include "TAD_INTEIRO.h"
#include <stdlib.h>
#include <stdio.h>
Lista* lst_cria(void){
    return NULL;
}

Lista* lst_libera(Lista* l){
    Lista* aux;

    while(l != NULL){
        aux=l;
        l=l->prox;
        free(aux);
    }

    return NULL;
}

Lista* lst_insere(Lista *l, int i){
    Lista* novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;

    return novo;
}

Lista* lst_retira(Lista* l, int v){
    Lista* p;
    Lista* ant;
    
    for(p=l, ant= NULL; p != NULL && p->info != v; ant=p, p=p->prox);

    if(p != NULL && ant == NULL){
        l = p->prox;
        free(p);
    }
    else if(p!= NULL && ant != NULL){
        ant->prox = p->prox;
        free(p);
    }

    return l;
}

int lst_vazia(Lista* l){
    return l == NULL;
}

Lista* lst_busca(Lista *l, int v){
    Lista* p;
    for(p=l; p != NULL && p->info !=v; p = p->prox);

    return p;
}

void lst_imprime(Lista *l){
    for( ; l != NULL; l = l->prox)
        printf("Elemento: %d\n", l->info);
}