#ifndef __TAD_INTEIRO_H__
    #define __TAD_INTEIRO_H__

    #include <stdlib.h>

    struct lista{
        int info;
        struct lista* prox;
    };

    typedef struct lista Lista;

    Lista* lst_cria(void);
    Lista* lst_libera(Lista* l);

    Lista* lst_insere(Lista *l, int i);
    Lista* lst_retira(Lista* l, int v);

    int lst_vazia(Lista* l);
    Lista* lst_busca(Lista *l, int v);
    void lst_imprime(Lista *l);

    #include "TAD_INTEIRO.c"
#endif