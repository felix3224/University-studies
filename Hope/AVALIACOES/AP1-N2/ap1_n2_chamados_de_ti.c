#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../TAD_LISTA/TAD_LISTA.h"
#include "../../TAD_TREE/TAD_TREE.h"

// Chamados de TI
void formatacao(void* elemento);
void* ler_linha(char* linha_arquivo);
char* montar_linha(void* elemento);
void* criar_chamado();
int insere_em_qualquer_lugar();
int todos_registros(void* elemento);
void* copia_chamado(void* info);
int verifica_chamado_aberto(void* elemento);
int verifica_id_chamado_igual(void* elemento1, void* elemento2);
int verifica_id_chamado_maior(void* elemento1, void* elemento2);

typedef struct atendimento{
    int  id_chamado;     // índice do chamado: chave primária.
    int  id_usuario;     // índice que designa o usuário que abriu o chamado: chave estrangeira.
    char solicitante[100];     // Nome do usuário que abriu o chamado
    char setor[50];            // Local do atendimento: "Biblioteca", "LabInfo1"
    char data[11];             // Formato "DD/MM/AAAA"
    char problema[100];        // Ex: "Impressora não imprime", "Sem internet"
    int resolvido;             // 0 = pendente, 1 = resolvido 
} AtendimentoTI;

typedef struct avaliacao {
    int id_chamado; // índice do chamado: chave estrangeira para a tabela atendimento.
    int satisfacao;         // 1 a 5
    char comentario[200]; // Comentário acerca do atendimento.
} AvaliacaoTI;


int main(void){

    Node* Atendimentos = tree_create_empty();

    // Carrega dados da memória secundária na memória principal
    Atendimentos = tree_load_from_file("../banco_de_dados_chamados.csv", ler_linha, verifica_id_chamado_maior);

    printf("=> Nossa ÁRVORE está CARREGADA DA MEMÓRIA!!!\nEsta é uma árvore de CHAMADOS DE TI.\n");

    // Imprime a árvore criada.
    tree_map(Atendimentos, formatacao);

    printf("\nImprimindo chamados não resolvidos:\n");

    Lista* chamados_abertos = tree_filter_as_list(Atendimentos, verifica_chamado_aberto, copia_chamado, verifica_id_chamado_maior);
    
    // Imprime a árvore chamados não atendidos.
    lst_map(chamados_abertos, formatacao, todos_registros);

    lst_libera(chamados_abertos);

    printf("\nInserindo 3 elementos novos na nossa árvore:\n");
    
    for(int i=0; i<3; i++){
        AtendimentoTI* chamado_novo = criar_chamado(51 + i);
        if(chamado_novo){
            Atendimentos = tree_insert_node(Atendimentos,\
                 tree_create_node(chamado_novo, tree_create_empty(), tree_create_empty()),\
                  verifica_id_chamado_maior);
        }
    }

    // Imprime a árvore com os novos registros.
    tree_map(Atendimentos, formatacao);

    // Grava os dados da memória principal para a secundária.
    tree_to_file(Atendimentos, "../banco_de_dados_chamados.csv", montar_linha);

    // Liberando a árvore completa.
    printf("\n\nLiberando minha ÁRVORE de CHAMADOS DE TI...\n");
    
    tree_free(Atendimentos);
    
    return 0;
}

// Funções ÚTEIS
// Define o formato e imprime informação do tipo AtendimentoTI.
void formatacao(void* elemento){
    AtendimentoTI* atendimento = (AtendimentoTI*)elemento;
    printf("| %d | %d | %s | %d\n", atendimento->id_chamado, atendimento->id_usuario, atendimento->solicitante, atendimento->resolvido);
}

/// @brief Função que discrimina que todos os elementos serão selecionados.
/// @param elemento 
/// @return True 
int todos_registros(void* elemento){
    return 1;
}

// Processa a linha do arquivo e
// retorna um ponteiro para a estrutura com os dados inseridos nela.
void* ler_linha(char* linha_arquivo){
    // Aloca a memória para receber os dados presentes em linha_arquivo
    AtendimentoTI* novo = (AtendimentoTI*)malloc(sizeof(AtendimentoTI));

    if(!novo){
        printf("\nFicamos sem memória criando um nó da árvore enquanto carregada a linha do arquivo...\n");
        exit(1);
    }

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

// Realiza a cópia de um chamado
void* copia_chamado(void* info){
    AtendimentoTI* info_original = (AtendimentoTI*)info;
    AtendimentoTI* info_copia = (AtendimentoTI*)malloc(sizeof(AtendimentoTI));

    if(!info_copia){
        printf("\nFicamos sem memória copiando um chamado...\n");
        exit(1);
    }

    strcpy(info_copia->data, info_original->data);
    info_copia->id_chamado = info_original->id_chamado;
    info_copia->id_usuario = info_original->id_usuario;
    strcpy(info_copia->problema, info_original->problema);
    info_copia->resolvido = info_original->resolvido;
    strcpy(info_copia->setor, info_original->setor);
    strcpy(info_copia->solicitante, info_original->solicitante);

    return info_copia;
}

int verifica_chamado_aberto(void* elemento){
    AtendimentoTI* chamado = (AtendimentoTI*)elemento;
    return chamado->resolvido == 0;
}

int verifica_id_chamado_igual(void* elemento1, void* elemento2){
    AtendimentoTI* chamado1 = (AtendimentoTI*)elemento1;
    AtendimentoTI* chamado2 = (AtendimentoTI*)elemento2;

    return chamado1->id_chamado == chamado2->id_chamado;
}

int verifica_id_chamado_maior(void* elemento1, void* elemento2){
    AtendimentoTI* chamado1 = (AtendimentoTI*)elemento1;
    AtendimentoTI* chamado2 = (AtendimentoTI*)elemento2;

    return chamado1->id_chamado < chamado2->id_chamado;
}

void* criar_chamado(int id_atual){
    AtendimentoTI* novo = (AtendimentoTI*)malloc(sizeof(AtendimentoTI));

    if(!novo){
        printf("\nFicamos sem memória criando um chamado...\n");
        exit(1);
    }

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
    
    if(!linha){
        printf("\nFicamos sem memória preparando a linha do chamado %d ser gravada no arquivo...\n", atendimento->id_chamado);
        exit(1);
    }
    
    sprintf(linha,"%d;%d;%s;%s;%s;%s;%d\n", atendimento->id_chamado, atendimento->id_usuario, atendimento->solicitante, atendimento->setor, atendimento->data, atendimento->problema, atendimento->resolvido);
 
    return linha;
}