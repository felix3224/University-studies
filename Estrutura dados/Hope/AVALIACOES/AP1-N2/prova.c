#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../TAD_TREE/TAD_TREE.h"

// Estrutura para os chamados de TI
typedef struct atendimento
{
    int id_chamado;
    int id_usuario;
    char solicitante[100];
    char setor[50];
    char data[11];
    char problema[100];
    int resolvido;
} AtendimentoTI;

// Estrutura para as avaliações de satisfação
typedef struct avaliacao
{
    int id_chamado;
    int satisfacao;
    char comentario[200];
} AvaliacaoTI;

// Estrutura para combinar Atendimento e Avaliação
typedef struct
{
    AtendimentoTI atendimento;
    AvaliacaoTI avaliacao;
} ChamadoCompleto;

// Protótipos das funções
void *ler_linha_atendimento(char *linha_arquivo);
void *ler_linha_avaliacao(char *linha_arquivo);
int compara_atendimento_por_id(void *elem1, void *elem2);
int compara_avaliacao_por_id(void *elem1, void *elem2);
int compara_chamado_por_satisfacao(void *elem1, void *elem2);

void imprimir_chamado_completo(AtendimentoTI *atendimento, AvaliacaoTI *avaliacao);
void processa_e_imprime_atendimento(void *atendimento_info);
void filtrar_e_inserir_insatisfeitos(void *atendimento_info);
void imprimir_chamado_filtrado(void *chamado_completo_info);

int buscar_avaliacao_callback(void *avaliacao_info);

// Variáveis globais para acesso nas funções de callback
Node *arvore_avaliacoes_ref = NULL;
Node *arvore_insatisfeitos = NULL;
int id_busca_global = 0;

int main(void)
{
    // a) Carregar e imprimir os dados das duas árvores
    printf("=============== CHAMADOS DE TI E AVALIACOES ===============\n");

    // Cria e carrega a árvore de atendimentos
    Node *arvore_atendimentos = tree_create_empty();
    arvore_atendimentos = tree_load_from_file("./banco_de_dados_chamados.csv", ler_linha_atendimento, compara_atendimento_por_id);

    // Cria e carrega a árvore de avaliações
    arvore_avaliacoes_ref = tree_create_empty();
    arvore_avaliacoes_ref = tree_load_from_file("./banco_de_dados_satisfacao.csv", ler_linha_avaliacao, compara_avaliacao_por_id);

    // Itera sobre a árvore de atendimentos para buscar a avaliação correspondente e imprimir
    tree_map(arvore_atendimentos, processa_e_imprime_atendimento);

    // b) Criar e imprimir a árvore de chamados com satisfação <= 3
    printf("\n\n===== CHAMADOS COM SATISFACAO MENOR OU IGUAL A 3 =====\n");
    printf("(Ordenado por nota de satisfação)\n\n");

    // Popula a terceira árvore com os registros insatisfeitos
    arvore_insatisfeitos = tree_create_empty();
    tree_map(arvore_atendimentos, filtrar_e_inserir_insatisfeitos);

    // Imprime a árvore de insatisfeitos
    tree_map(arvore_insatisfeitos, imprimir_chamado_filtrado);

    // Liberar memória
    tree_free(arvore_atendimentos);
    tree_free(arvore_avaliacoes_ref);
    tree_free(arvore_insatisfeitos);

    return 0;
}

/**
 * @brief Imprime os detalhes combinados de um atendimento e sua avaliação.
 */
void imprimir_chamado_completo(AtendimentoTI *atendimento, AvaliacaoTI *avaliacao)
{
    if (!atendimento)
        return;

    printf("[Chamado ID %d]\n", atendimento->id_chamado);
    printf("Solicitante: %s | Setor: %s | Data: %s\n", atendimento->solicitante, atendimento->setor, atendimento->data);
    printf("Problema: %s\n", atendimento->problema);

    if (avaliacao)
    {
        printf("Satisfacao: %d | Comentario: %s\n", avaliacao->satisfacao, avaliacao->comentario);
    }
    else
    {
        printf("Satisfacao: N/A | Comentario: N/A\n");
    }
    printf("--------------------------------------------------------------\n");
}

/**
 * @brief Função de callback para o tree_map. Processa cada atendimento,
 * busca sua avaliação e chama a função de impressão.
 */
void processa_e_imprime_atendimento(void *atendimento_info)
{
    AtendimentoTI *atendimento = (AtendimentoTI *)atendimento_info;

    // Configura o ID global para a busca
    id_busca_global = atendimento->id_chamado;

    // Busca o nó da avaliação correspondente na árvore de avaliações
    Node *no_avaliacao = tree_search(arvore_avaliacoes_ref, buscar_avaliacao_callback);

    if (no_avaliacao)
    {
        imprimir_chamado_completo(atendimento, (AvaliacaoTI *)no_avaliacao->info);
    }
    else
    {
        imprimir_chamado_completo(atendimento, NULL);
    }
}

/**
 * @brief Função de callback para popular a árvore de chamados insatisfeitos.
 */
void filtrar_e_inserir_insatisfeitos(void *atendimento_info)
{
    AtendimentoTI *atendimento = (AtendimentoTI *)atendimento_info;
    id_busca_global = atendimento->id_chamado;

    Node *no_avaliacao = tree_search(arvore_avaliacoes_ref, buscar_avaliacao_callback);

    if (no_avaliacao)
    {
        AvaliacaoTI *avaliacao = (AvaliacaoTI *)no_avaliacao->info;
        if (avaliacao->satisfacao <= 3)
        {
            // Aloca memória para a estrutura combinada
            ChamadoCompleto *novo_completo = (ChamadoCompleto *)malloc(sizeof(ChamadoCompleto));
            if (!novo_completo)
                exit(1);

            // Copia os dados
            novo_completo->atendimento = *atendimento;
            novo_completo->avaliacao = *avaliacao;

            // Cria um novo nó e o insere na árvore de insatisfeitos
            Node *novo_no = tree_create_node(novo_completo, tree_create_empty(), tree_create_empty());
            arvore_insatisfeitos = tree_insert_node(arvore_insatisfeitos, novo_no, compara_chamado_por_satisfacao);
        }
    }
}

/**
 * @brief Função de callback para imprimir os nós da árvore de insatisfeitos.
 */
void imprimir_chamado_filtrado(void *chamado_completo_info)
{
    ChamadoCompleto *chamado = (ChamadoCompleto *)chamado_completo_info;
    imprimir_chamado_completo(&chamado->atendimento, &chamado->avaliacao);
}

/**
 * @brief Função de callback para a busca na árvore de avaliações.
 * Compara o ID da avaliação com uma variável global.
 */
int buscar_avaliacao_callback(void *avaliacao_info)
{
    AvaliacaoTI *avaliacao = (AvaliacaoTI *)avaliacao_info;
    return avaliacao->id_chamado == id_busca_global;
}

/**
 * @brief Compara dois atendimentos pelo ID do chamado para ordenação na árvore.
 * Retorna 1 se o ID do elem1 < ID do elem2 (para inserção à esquerda).
 */
int compara_atendimento_por_id(void *elem1, void *elem2)
{
    AtendimentoTI *a1 = (AtendimentoTI *)elem1;
    AtendimentoTI *a2 = (AtendimentoTI *)elem2;
    return a1->id_chamado < a2->id_chamado;
}

/**
 * @brief Compara duas avaliações pelo ID do chamado para ordenação na árvore.
 */
int compara_avaliacao_por_id(void *elem1, void *elem2)
{
    AvaliacaoTI *av1 = (AvaliacaoTI *)elem1;
    AvaliacaoTI *av2 = (AvaliacaoTI *)elem2;
    return av1->id_chamado < av2->id_chamado;
}

/**
 * @brief Compara dois chamados completos pela nota de satisfação.
 * Usado para ordenar a árvore de insatisfeitos.
 * Em caso de empate na satisfação, ordena pelo id_chamado.
 */
int compara_chamado_por_satisfacao(void *elem1, void *elem2)
{
    ChamadoCompleto *c1 = (ChamadoCompleto *)elem1;
    ChamadoCompleto *c2 = (ChamadoCompleto *)elem2;
    if (c1->avaliacao.satisfacao < c2->avaliacao.satisfacao)
    {
        return 1;
    }
    if (c1->avaliacao.satisfacao == c2->avaliacao.satisfacao)
    {
        return c1->atendimento.id_chamado < c2->atendimento.id_chamado;
    }
    return 0;
}

/**
 * @brief Lê uma linha do arquivo de atendimentos e a converte para a struct AtendimentoTI.
 */
void *ler_linha_atendimento(char *linha_arquivo)
{
    AtendimentoTI *novo = (AtendimentoTI *)malloc(sizeof(AtendimentoTI));
    if (!novo)
        exit(1);

    sscanf(linha_arquivo, "%d;%d;%[^;];%[^;];%[^;];%[^;];%d",
           &novo->id_chamado, &novo->id_usuario, novo->solicitante,
           novo->setor, novo->data, novo->problema, &novo->resolvido);

    return (void *)novo;
}

/**
 * @brief Lê uma linha do arquivo de satisfação e a converte para a struct AvaliacaoTI.
 */
void *ler_linha_avaliacao(char *linha_arquivo)
{
    AvaliacaoTI *novo = (AvaliacaoTI *)malloc(sizeof(AvaliacaoTI));
    if (!novo)
        exit(1);

    sscanf(linha_arquivo, "%d;%d;%[^\n]",
           &novo->id_chamado, &novo->satisfacao, novo->comentario);

    return (void *)novo;
}