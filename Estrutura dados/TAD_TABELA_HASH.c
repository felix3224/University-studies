#include "TAD_TABELA_HASH.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// 1. Calcula o hash de uma chave primária
static int hash(int mat){ return abs(mat) % N; }

// 2. Busca um aluno por matrícula e retorna o ponteiro para a estrutura, caso exista.
Aluno* hash_busca(Aluno** tab, int mat){

    Aluno* p = tab[hash(mat)];

    while( p != NULL){
        if(p->mat == mat) return p;
        p = p -> prox;
    }
    return NULL;
}

// 3. Insere um aluno na tabela de dispersão, caso a matrícula já exista, atualizar os dados do aluno.
Aluno* hash_insere(Aluno** tab, int mat, char* nome, char* tel, char* email){
    int hash_id = hash(mat);

    Aluno* p = tab[hash_id];
    Aluno* ant = NULL;

    while(p != NULL){
        if( p->mat == mat) break;
        ant = p;
        p = p ->prox;
    }
    // if mat was find -> 'update dates'
    if(p){
        strcpy(p->email, email);
        strcpy(p->tel, tel);
        strcpy(p->nome, nome);
        return p;
    }
    else{
        Aluno* new_student = (Aluno*)malloc(sizeof(Aluno));

        if(!new_student){ printf("Haven't memore enough for cadastre new aluno..."); exit(1);}

        new_student->mat = mat;
        strcpy(new_student->nome, nome);
        strcpy(new_student->email, email);
        strcpy(new_student->tel, tel);
        new_student ->prox = NULL;

        //TRATAMENT OF COLISION OF STUDENT.
        if(ant) ant->prox = new_student;     //if already have student, that go for final of the da list 
        
        else    tab[hash_id] = new_student;  //if is the first

        return new_student;
    }
}

//4. Remover aluno pela matrícula
int hsh_remove(Aluno** tab, int mat){

    Aluno* p = tab[hash(mat)];
    Aluno* ant = NULL;

    while ( p != NULL){
        if(p->mat == mat) break;
        ant = p;
        p = p -> prox;
    }

    if(!p) return 0;                // NOPE FIND NOTHING
    if(ant) ant -> prox = p -> prox; // THERE IS A LIST OF COLISION 
    else tab[hash(mat)] = p->prox;   // THERE IS JUST A ELEMENT 

    free(p);
    return 1;
}

// 5. Atualizar dados de um aluno
int hash_atualiza(Aluno** tab, int mat, char* nome, char* tel, char* email){

    Aluno* p = tab[hash(mat)];

    while( p != NULL){
        if(p -> mat == mat) break;
        p = p->prox;
    }
    if(p){
        strcpy(p->nome, nome);
        strcpy(p->email, email);
        strcpy(p->tel, tel);
        return 1;
    }else
        return 0;
}

// 6. Listar todos os alunos
void hash_lista_todos(Aluno** tab){
    Aluno* aluno = NULL;

    for(int i = 0 ; i < N ; i++){
        if(tab[i]){
            aluno = tab[i];
        while(aluno){
            printf("MATRICULA:%d\n",aluno->mat);
            printf("NOME:%s\n",aluno->nome);
            printf("EMAIL:%s\n",aluno->email);
            printf("TEL:%s\n",aluno->tel);
            aluno = aluno ->prox;
        }
        }
    }
}

// 7. Contar número de alunos na tabela
int hsh_conta_alunos(Aluno** tab){
   int qtd_aluno = 0;
   Aluno* p = NULL;

   for(int i = 0; i < N; i++){
        p = tab[i];
    while(p){
            qtd_aluno++;
            p = p->prox;
            }
   }
   return qtd_aluno;
}

// 8. Buscar aluno por nome (busca parcial)
Aluno* hsh_busca_por_nome(Aluno** tab, char* nome){

    for( int i = 0; i < N ; i++ ){
            Aluno* find = tab[i];

            while(find){
                if(strstr(find -> nome, nome) !=  NULL) return find;
                    find = find ->prox;
            }
    }
    return NULL;
}

// 9. Limpar/liberar toda a tabela
void hsh_limpa_tabela(Aluno** tab){
    if ( tab == NULL)return;
    Aluno* p = NULL;
    for(int i = 0; i < N; i++ ){
        p = tab[i];

        while(p){
            Aluno* aux = p->prox;
            free(p);
            p = aux;
        }
        tab[i] = NULL;
    }
}

// 10. Calcular fator de carga da tabela
float hsh_fator_carga(Aluno** tab){
    if( tab == NULL)return 0.0;

    int elementO = hsh_conta_alunos(tab);
    return (float) elementO / N;
}

// 11. Verificar se tabela está vazia
int hsh_vazia(Aluno** tab){
    if( tab == NULL) return 1;
    
    for(int i = 0; i < N ; i++){
        if(tab[i]) return 0;
    }
    return 1;
}
// 12. Exportar dados para arquivo
int hsh_exporta_arquivo(Aluno** tab, char* filename, char* (*escrever_linha_csv)(void*)) {
   if(tab == NULL || filename == NULL )return 0;

    FILE* saida = fopen(filename,"wt");

    for(int i = 0; i < N; i++){
        Aluno* p = tab[i];

        while(p){
            char* linha = escrever_linha_csv(p);
            if(linha){
                fprintf(saida,"%s\n",linha);
                free(linha);
            }
            p = p->prox;
        }
    }
    fclose(saida);
    return 1;
}

// 13. Importar dados de arquivo
int hsh_importa_arquivo(Aluno** tab, char* filename, void* (*ler_linha_csv)(char*)){
   
    FILE* ler_arquivo = fopen(filename, "rt");
    if(!ler_arquivo) return 0;

    char linha[256];
    int cont = 0;

    while(fgets(linha, sizeof(linha), ler_arquivo) != NULL){
        linha[strcspn(linha,"\n")] = 0;

        Aluno* student = (Aluno*) ler_linha_csv(linha);

        if(student != NULL){
            Aluno* result = hash_insere(
                tab,
                student->mat,
                student->nome,
                student->tel,
                student->email
            );
            if(student) cont++;
            free(student);
        }
    }
    fclose(ler_arquivo);
    printf(("Quantidades de alunos importados: %d do arquivo %s",cont, filename));
    return cont > 0 ? 1 : 0;
}