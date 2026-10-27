#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 1 STRUCT POR INTEGRANTE)
// ============================================================================

// 1. Perspectiva de Nathan Souza Gusso: Acervo de Discos de Vinil
struct Disco {
    int idDisco;
    char titulo[50];
    char artista[50];
    float preco;
    int quantidadeEstoque;
};

struct Disco acervoDiscos[50];
int totalDiscos = 0;

// 2. Perspectiva de Guilherme Monteiro de Andrade: Cabines de Escuta da Loja
struct Cabine {
    int idCabine;
    int numeroCabine;
    int statusOcupacao;      // 1 = Ocupada, 0 = Livre
    int tempoUsoMinutos;
    int idClienteUsando;
};

struct Cabine listaCabines[50];
int totalCabines = 0;

// 3. Perspectiva de Jose Gustavo da Silva Bertoche: Clientes do Clube do Vinil
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    int pontosFidelidade;
    int ativo;               // 1 = Ativo, 0 = Removido
};

struct Cliente listaClientes[50];
int totalClientes = 0;

// 4. Perspectiva de Bernardo Novaski Vidal de Almeida: Vendas no Caixa e Relatorios
struct Venda {
    int idVenda;
    int idClienteComprador;
    int idDiscoVendido;
    float valorTotal;
};

struct Venda historicoVendas[50];
int totalVendas = 0;

// ============================================================================
// PARTE 2: FUNCOES DE INTERFACE E MODULOS
// ============================================================================

// Funcao visual comum da equipe
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("   VINYL HUB - SISTEMA DE GESTAO RETRO (1985)      \n");
    printf("   Discos de Vinil | Cabines de Escuta | Caixa        \n");
    printf("======================================================\n");
}

// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DO ACERVO DE DISCOS
// Autor: Nathan Souza Gusso
// ----------------------------------------------------------------------------
void moduloDiscos() {
    int opcaoDisco;

    do {
        printf("\n--- [MODULO 1: ACERVO DE DISCOS (Nathan Souza Gusso)] ---\n");
        printf("1. Cadastrar Novo Disco\n");
        printf("2. Listar / Buscar Discos\n");
        printf("3. Editar Dados de um Disco (Preco / Estoque)\n");
        printf("4. Remover Disco do Acervo\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoDisco);

        switch (opcaoDisco) {
            case 1:
                printf("\n[Em construcao] Cadastro de Disco...\n");
                printf("Campos previstos: ID, Titulo, Artista, Preco e Estoque.\n");
                break;
            case 2:
                printf("\n[Em construcao] Listagem e Busca de Discos...\n");
                break;
            case 3:
                printf("\n[Em construcao] Edicao de Disco por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Remocao de Disco do acervo...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Discos!\n");
        }
    } while (opcaoDisco != 0);
}

// ----------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DAS CABINES DE ESCUTA
// Autor: Guilherme Monteiro de Andrade
// ----------------------------------------------------------------------------
void moduloCabines() {
    int opcaoCabine;

    do {
        printf("\n--- [MODULO 2: CABINES DE ESCUTA (Guilherme Monteiro de Andrade)] ---\n");
        printf("1. Cadastrar Nova Cabine\n");
        printf("2. Listar / Buscar Cabines (Livres e Ocupadas)\n");
        printf("3. Editar Cabine (Status / Tempo de Uso / Cliente)\n");
        printf("4. Remover Cabine (Dar Baixa)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCabine);

        switch (opcaoCabine) {
            case 1:
                printf("\n[Em construcao] Cadastro de Cabine de Escuta...\n");
                printf("Campos previstos: ID, Numero, Status e Tempo de Uso.\n");
                break;
            case 2:
                printf("\n[Em construcao] Listagem e Busca de Cabines...\n");
                break;
            case 3:
                printf("\n[Em construcao] Edicao de Cabine por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Baixa de Cabine...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Cabines!\n");
        }
    } while (opcaoCabine != 0);
}

// ----------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DOS CLIENTES DO CLUBE DO VINIL
// Autor: Jose Gustavo da Silva Bertoche
// ----------------------------------------------------------------------------
void moduloClientes() {
    int opcaoCliente;

    do {
        printf("\n--- [MODULO 3: CLIENTES DO CLUBE DO VINIL (Jose Gustavo da Silva Bertoche)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Dados ou Pontos de Fidelidade\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCliente);

        switch (opcaoCliente) {
            case 1:
                printf("\n[Em construcao] Cadastro de Cliente...\n");
                printf("Campos previstos: ID, Nome, Telefone e Pontos.\n");
                break;
            case 2:
                printf("\n[Em construcao] Listagem e Busca de Clientes...\n");
                break;
            case 3:
                printf("\n[Em construcao] Edicao de Cliente por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Remocao de Cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}

// ----------------------------------------------------------------------------
// MODULO 4: PERSPECTIVA DE VENDAS E RELATORIOS ANALITICOS
// Autor: Bernardo Novaski Vidal de Almeida
// ----------------------------------------------------------------------------
void moduloVendasRelatorios() {
    int opcaoVenda;

    do {
        printf("\n--- [MODULO 4: VENDAS E RELATORIOS (Bernardo Novaski Vidal de Almeida)] ---\n");
        printf("1. Registrar Nova Venda no Caixa (Cruza Cliente + Disco)\n");
        printf("2. Listar Historico de Vendas\n");
        printf("3. Cancelar / Estornar Venda\n");
        printf("4. [RELATORIO] Disco Mais Vendido\n");
        printf("5. [RELATORIO] Cliente VIP (Maior Numero de Compras)\n");
        printf("6. [RELATORIO] Compras Realizadas por um Cliente Especifico\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoVenda);

        switch (opcaoVenda) {
            case 1:
                printf("\n[Em construcao] Lancamento de venda vinculando ID Cliente e ID Disco...\n");
                break;
            case 2:
                printf("\n[Em construcao] Exibindo historico de vendas...\n");
                break;
            case 3:
                printf("\n[Em construcao] Estorno de venda por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Calculando ranking do disco mais vendido...\n");
                break;
            case 5:
                printf("\n[Em construcao] Identificando cliente com mais compras...\n");
                break;
            case 6:
                printf("\n[Em construcao] Filtrando compras por ID de cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Vendas!\n");
        }
    } while (opcaoVenda != 0);
}

// ============================================================================
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// ============================================================================
int main() {
    int opcaoPrincipal;

    setlocale(LC_ALL, "Portuguese");

    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Modulo de Discos / Acervo (Nathan Souza Gusso)\n");
        printf("2. Modulo de Cabines de Escuta (Guilherme Monteiro de Andrade)\n");
        printf("3. Modulo de Clientes (Jose Gustavo da Silva Bertoche)\n");
        printf("4. Modulo de Vendas e Relatorios (Bernardo Novaski Vidal de Almeida)\n");
        printf("0. Encerrar o Sistema\n");
        printf("------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                moduloDiscos();
                break;
            case 2:
                moduloCabines();
                break;
            case 3:
                moduloClientes();
                break;
            case 4:
                moduloVendasRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema Vinyl Hub... Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite um numero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
