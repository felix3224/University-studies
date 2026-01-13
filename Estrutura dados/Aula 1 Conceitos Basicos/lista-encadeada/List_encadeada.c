#include<stdio.h>
#include<stdlib.h>
#include "List_encadeada.h"

Produto* pdt_criar(void) {
return NULL;
}

Produto* pdt_new_element(void ){
    Produto* new=(Produto* ) malloc(sizeof(Produto));
    new->next = NULL;

    printf("informe o id:");
    scanf(" %d", &new->id);
    printf("informe o nome:");
    scanf(" %9[^\n]", new->name);
    printf("informe a unidade:");
    scanf(" %49[^\n]", new->unidade);
    printf("informe o valor");
    scanf(" %f", &new->preco);
    printf("informe a quantidade no estoque:");
    scanf(" %f", &new->estoque);
return new;
}

Produto* pdt_insere(Produto* l , Produto* new_elemnt){  // acho essa funçao um pouco estranha, but all well
     new_elemnt->next = l;
    return new_elemnt;
}

Produto* pdt_retirar(Produto* l, int cod){
    Produto* p = l;
    Produto* ant = NULL;

    while( p != NULL && p->id != cod){
        ant->next = p;
        p = p->next;
    }
    if(p == NULL)return l;
    if(ant == NULL) l = p->next;
    else ant->next = p -> next;

    free(p);
    return l;
}

Produto* pdt_buscar(Produto* l, int cod){
    Produto * p = l;

    while(p != NULL && p->id != cod)
          p = p->next;
    
    return p;
}
void pdt_imprimir(Produto* l){
while(l != NULL){
    printf("id: %d\n",l->id);
    printf("nome:%s\n",l->name);
    printf("unidada:%s\n",l->unidade);
    printf("preco:%.2f\n",l->preco);
    printf("estoque:%.2f\n",l->estoque);
    l=l->next;
}
}
void pdt_liberar(Produto* l){
while(l != NULL){
    Produto* aux = l->next;
    free(l);
    l = aux;
}
}