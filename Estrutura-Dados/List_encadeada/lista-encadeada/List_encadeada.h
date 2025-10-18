#ifndef List_encadeada
    #define List_encadeada
    #define MAX_UNIDADE 50
    #define MAX_NAME 15
        struct produto{
            int id;
            char name[MAX_NAME];
            char unidade[MAX_UNIDADE];
            float preco;
            float estoque;
            struct produto* next;
        };

    typedef struct produto Produto;

    Produto* pdt_criar(void);
    Produto* pdt_new_element(void );
    Produto* pdt_insere(Produto* l , Produto* new_elemnt);
    Produto* pdt_retirar(Produto* l, int cod);
    Produto* pdt_buscar(Produto* l, int cod);
    void pdt_imprimir(Produto* l);
    void pdt_liberar(Produto* l);
    
    #include "List_encadeada.c"
#endif