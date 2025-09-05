#include <stdio.h>
#include <stdlib.h>
#include "../../TAD_LISTA/TAD_LISTA.h"

void formatacao(void* elemento);
void* ler_linha(char* linha_arquivo);
char* montar_linha(void* elemento);
void* criar_chamado();
int insere_em_qualquer_lugar();
int verifica_id_chamado_igual(void* elemento1, void* elemento2);

typedef struct atendimento{
    int  id_chamado;     // índice do chamado: chave primária.
    int  id_usuario;     // índice que designa o usuário que abriu o chamado: chave estrangeira.
    char solicitante[100];     // Nome do usuário que abriu o chamado
    char setor[50];            // Local do atendimento: "Biblioteca", "LabInfo1"
    char data[11];             // Formato "DD/MM/AAAA"
    char problema[100];        // Ex: "Impressora não imprime", "Sem internet"
    int resolvido;             // 0 = pendente, 1 = resolvido 
} AtendimentoTI;


int main(void){

    Lista* minha_lista = lst_cria();

    // Carrega dados da memória secundária na memória principal
    minha_lista = lst_carrega(minha_lista, "banco_de_dados_chamados.txt", ler_linha);

    printf("=> Nossa lista CARREGADA DA MEMÓRIA!!!\n\
        Faremos uma lista de CHAMADOS DE TI.\n");

    // Imprime a lista de inteiros criada.
    lst_imprime(minha_lista, formatacao);

    
    printf("\nImprimindo chamados não resolvidos:\n");

    for(Lista* p = minha_lista; p != NULL; p = p->prox){
        
        AtendimentoTI* elemento = (AtendimentoTI*)p->info;
        if(elemento->resolvido == 0)
            formatacao(elemento);
    }
    
    // Determinando o nosso id_atual:
    int id_atual = 0;
    for(Lista* p = minha_lista; p != NULL; p = p->prox){
        
        AtendimentoTI* elemento = (AtendimentoTI*)p->info;
        if(elemento->id_chamado > id_atual)
            id_atual = elemento->id_chamado; 
    }

    printf("\n\nID_ATUAL: %d\n", id_atual);

    printf("\nInserindo 3 elementos novos na nossa lista:\n");
    
    for(int i=0; i<3; i++){
        AtendimentoTI* chamado_novo = criar_chamado(id_atual);
        if(chamado_novo){
            minha_lista = lst_insere(minha_lista, chamado_novo, insere_em_qualquer_lugar);
            id_atual++;
        }
    }

    printf("\nExcluindo 3 elementos quaisquer da nossa lista:\n");
    
    AtendimentoTI* exclusao = (AtendimentoTI*)malloc(sizeof(AtendimentoTI));
    for(int i=0; i<3; i++){
        printf("Digite o id_chamado para exclusão: ");
        scanf("%d", &exclusao->id_chamado);
    
        minha_lista = lst_retira(minha_lista, exclusao, verifica_id_chamado_igual);
    }

    free(exclusao);

    // Grava os dados da memória principal para a secundária.
    lst_grava(minha_lista, "banco_de_dados_chamados.txt", montar_linha);

    // Liberando a lista completa.
    printf("\n\nLiberando minha Lista de CHAMADOS DE TI...\n");
    
    minha_lista = lst_libera(minha_lista);
    
    return 0;
}

// Funções ÚTEIS
// Define o formato e imprime elemento da lista genérica.
void formatacao(void* elemento){
    AtendimentoTI* atendimento = (AtendimentoTI*)elemento;
    printf("| %d | %d | %s | %d\n", atendimento->id_chamado, atendimento->id_usuario, atendimento->solicitante, atendimento->resolvido);
}

// Processa a linha do arquivo e
// retorna um ponteiro para a estrutura com os dados inseridos nela.
void* ler_linha(char* linha_arquivo){
    // Aloca a memória para receber os dados presentes em linha_arquivo
    AtendimentoTI* novo = (AtendimentoTI*)malloc(sizeof(AtendimentoTI));

    char aux[50];
    aux[0] ='\0';

    // Copia os caracteres de linha_arquivo enquanto não
    // encontra o caracter de separação ';'
    int i=0;
    int j=0;
    while(linha_arquivo[i] != ';'){
        aux[j] = linha_arquivo[i];
        i++;
        j++;
    }
    aux[j] = '\0';
    novo->id_chamado = atoi(aux);

    i++;
    j=0;
    while(linha_arquivo[i] != ';'){
        aux[j] = linha_arquivo[i];
        i++;
        j++;
    }
    aux[j] = '\0';
    novo->id_usuario = atoi(aux);

    // Vai para o próximo caracter em linha_arquivo.
    i++;

    j=0;
    while(linha_arquivo[i] != ';'){
        novo->solicitante[j] = linha_arquivo[i];
        i++;
        j++;
    }
    novo->solicitante[j]='\0';

    // Vai para o próximo caracter em linha_arquivo.
    i++;

    j=0;
    while(linha_arquivo[i] != ';'){
        novo->setor[j] = linha_arquivo[i];
        i++;
        j++;
    }
    novo->setor[j]='\0';

    // Vai para o próximo caracter em linha_arquivo.
    i++;

    j=0;
    while(linha_arquivo[i] != ';'){
        novo->data[j] = linha_arquivo[i];
        i++;
        j++;
    }
    novo->data[j]='\0';

    // Vai para o próximo caracter em linha_arquivo.
    i++;

    j=0;
    while(linha_arquivo[i] != ';'){
        novo->problema[j] = linha_arquivo[i];
        i++;
        j++;
    }
    novo->problema[j]='\0';

    i++;

    j=0;
    while(linha_arquivo[i] != '\n' && linha_arquivo[i] != '\0'){
        aux[j] = linha_arquivo[i];
        i++;
        j++;
    }
    aux[j]='\0';
    novo->resolvido = atoi(aux);

    // Retorna a estrutura como void* para ser guardada na lista.
    return (void*)novo;
}

int verifica_id_chamado_igual(void* elemento1, void* elemento2){
    AtendimentoTI* chamado1 = (AtendimentoTI*)elemento1;
    AtendimentoTI* chamado2 = (AtendimentoTI*)elemento2;

    return chamado1->id_chamado == chamado2->id_chamado;
}

void* criar_chamado(int id_atual){
    AtendimentoTI* novo = (AtendimentoTI*)malloc(sizeof(AtendimentoTI));

    novo->id_chamado = id_atual + 1;

    printf("id solicitante: ");
    scanf("%d%*c", &novo->id_usuario);

    printf("Solicitante: ");
    scanf("%99[^\n]%*c", novo->solicitante);
    
    printf("Setor: ");
    scanf("%49[^\n]%*c", novo->setor);

    printf("Data: ");
    scanf("%10[^\n]%*c", novo->data);

    printf("Problema: ");
    scanf("%99[^\n]%*c", novo->problema);

    novo->resolvido = 0;
    
    return novo;
}

int insere_em_qualquer_lugar(){
    return 1;
}

char* montar_linha(void* elemento){
    
    AtendimentoTI* atendimento = (AtendimentoTI*)elemento;
    // Aloca 300 caracteres para montar a linha
    char* linha = (char*)malloc((300)*sizeof(char));
    
    if(!linha)
        exit(1);
    
    sprintf(linha,"%d;%d;%s;%s;%s;%s;%d\n", atendimento->id_chamado, atendimento->id_usuario, atendimento->solicitante, atendimento->setor, atendimento->data, atendimento->problema, atendimento->resolvido);
 
    return linha;
}