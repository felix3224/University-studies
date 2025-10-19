#ifndef __TAD_LISTAHET_H__
    #define __TAD_LISTAHET_H__
    
    #define RET 0
    #define CIR 1
    #define TRI 2

    #include <stdlib.h>

    struct listahet{
        int id;
        int tipo;
        void* info;
        struct listahet* prox;
    };

    struct retangulo{
        float b;
        float h;
    };

    struct circulo{
        float r;
    };

    struct triangulo{
        float b;
        float h;
    };

    typedef struct listahet Listahet;
    typedef struct retangulo Retangulo;
    typedef struct circulo Circulo;
    typedef struct triangulo Triangulo;

    Listahet* lsthet_cria(void);
    Listahet* lsthet_libera(Listahet* l);

    Listahet* lsthet_insere(Listahet *l,int id, int tipo, void* info);
    Listahet* lsthet_retira(Listahet* l, int id);

    int lsthet_vazia(Listahet* l);
    Listahet* lsthet_busca(Listahet *l, int id);
    void lsthet_imprime(Listahet *l);

    #include "TAD_LISTAHET.c"
#endif