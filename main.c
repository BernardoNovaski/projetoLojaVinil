#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 1 STRUCT POR INTEGRANTE)
// ============================================================================

// 1. Nathan Souza Gusso: Acervo de Discos de Vinil
struct Disco {
    int idDisco;
    char titulo[50];
    char artista[50];
    float preco;
    int quantidadeEstoque;
    int ativo;               // 1 = Ativo, 0 = Removido
};

struct Disco acervoDiscos[50];
int totalDiscos = 0;

// 2. Guilherme Monteiro de Andrade: Cabines de Escuta da Loja
struct Cabine {
    int idCabine;
    int numeroCabine;
    char descricao[40];      // ex.: "Cabine_Jazz", "Cabine_Rock"
    float valorHoraUso;
    int statusOcupacao;      // 1 = Ocupada, 0 = Livre
    int tempoUsoMinutos;
    int idClienteUsando;     // 0 = nenhum cliente
    int ativo;               // 1 = Ativa, 0 = Baixada
};

struct Cabine listaCabines[50];
int totalCabines = 0;

// 3. Jose Gustavo da Silva Bertoche: Clientes do Clube do Vinil
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    int pontosFidelidade;
    int ativo;               // 1 = Ativo, 0 = Removido
};

struct Cliente listaClientes[50];
int totalClientes = 0;

// 4. Bernardo Novaski Vidal de Almeida: Vendas no Caixa e Relatorios
struct Venda {
    int idVenda;
    int idClienteComprador;
    int idDiscoVendido;
    int quantidade;
    float valorTotal;
    char dataVenda[11];      // "DD/MM/AAAA"
    int ativo;               // 1 = Efetivada, 0 = Cancelada
};

struct Venda historicoVendas[50];
int totalVendas = 0;

// ============================================================================
// PARTE 2: FUNCOES DE INTERFACE, AUXILIARES E MODULOS
// ============================================================================

// Funcao visual comum da equipe
// Autor: Equipe
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("   VINYL HUB - SISTEMA DE GESTAO RETRO (1985)      \n");
    printf("   Discos de Vinil | Cabines de Escuta | Caixa        \n");
    printf("======================================================\n");
}

// Descarta o que sobrou digitado na linha (evita loop infinito por texto no lugar de numero)
// Autor: Equipe 
void limparBuffer() {
    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Le um numero inteiro; repete a pergunta ate o usuario digitar um numero valido
// Autor: Equipe 
int lerInteiro() {
    int valor, lidos;

    lidos = scanf("%d", &valor);
    while (lidos != 1) {
        if (lidos == EOF) {
            exit(0);
        }
        limparBuffer();
        printf("Entrada invalida! Digite apenas numeros inteiros: ");
        lidos = scanf("%d", &valor);
    }
    limparBuffer();
    return valor;
}

// Le um numero decimal (use ponto, ex.: 80.50); repete ate digitar um numero valido
// Autor: Equipe
float lerReal() {
    float valor;
    int lidos;

    lidos = scanf("%f", &valor);
    while (lidos != 1) {
        if (lidos == EOF) {
            exit(0);
        }
        limparBuffer();
        printf("Entrada invalida! Digite um numero (ex.: 80.50): ");
        lidos = scanf("%f", &valor);
    }
    limparBuffer();
    return valor;
}

// ----------------------------------------------------------------------------
// FUNCOES AUXILIARES DE BUSCA (usadas por mais de um modulo)
// ----------------------------------------------------------------------------

// Autor: Nathan Souza Gusso
int buscarDiscoPorId(int id) {
    int i;

    for (i = 0; i < totalDiscos; i++) {
        if (acervoDiscos[i].idDisco == id) {
            return i;
        }
    }
    return -1;
}

// Autor: Jose Gustavo da Silva Bertoche
int buscarClientePorId(int id) {
    int i;

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id) {
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DO ACERVO DE DISCOS
// Autor: Nathan Souza Gusso
// ----------------------------------------------------------------------------

void exibirDisco(int i) {
    printf("\nDisco ID %d\n", acervoDiscos[i].idDisco);
    printf("Titulo: %s\n", acervoDiscos[i].titulo);
    printf("Artista: %s\n", acervoDiscos[i].artista);
    printf("Preco: R$ %.2f\n", acervoDiscos[i].preco);
    printf("Estoque: %d unidade(s)\n", acervoDiscos[i].quantidadeEstoque);
}

void cadastrarDisco() {
    if (totalDiscos >= 50) {
        printf("\nLimite de 50 discos atingido!\n");
        return;
    }

    acervoDiscos[totalDiscos].idDisco = totalDiscos + 1;
    printf("\nID gerado para o disco: %d\n", acervoDiscos[totalDiscos].idDisco);

    printf("Titulo (sem espacos, use _ no lugar): ");
    scanf("%49s", acervoDiscos[totalDiscos].titulo);
    limparBuffer();

    printf("Artista (sem espacos, use _ no lugar): ");
    scanf("%49s", acervoDiscos[totalDiscos].artista);
    limparBuffer();

    do {
        printf("Preco do disco: R$ ");
        acervoDiscos[totalDiscos].preco = lerReal();
        if (acervoDiscos[totalDiscos].preco <= 0) {
            printf("Preco invalido! Deve ser maior que zero.\n");
        }
    } while (acervoDiscos[totalDiscos].preco <= 0);

    do {
        printf("Quantidade em estoque: ");
        acervoDiscos[totalDiscos].quantidadeEstoque = lerInteiro();
        if (acervoDiscos[totalDiscos].quantidadeEstoque < 0) {
            printf("Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (acervoDiscos[totalDiscos].quantidadeEstoque < 0);

    acervoDiscos[totalDiscos].ativo = 1;
    totalDiscos++;

    printf("\nDisco cadastrado com sucesso!\n");
}

void listarDiscos() {
    int opcaoListagem, id, indice, i, encontrou;

    printf("\n1. Listar todos os discos\n");
    printf("2. Buscar disco por ID\n");
    printf("Escolha: ");
    opcaoListagem = lerInteiro();

    switch (opcaoListagem) {
        case 1:
            encontrou = 0;
            printf("\n===== ACERVO DE DISCOS =====\n");
            for (i = 0; i < totalDiscos; i++) {
                if (acervoDiscos[i].ativo == 1) {
                    exibirDisco(i);
                    encontrou++;
                }
            }
            if (encontrou == 0) {
                printf("Nenhum disco cadastrado.\n");
            }
            break;
        case 2:
            printf("\nDigite o ID do disco: ");
            id = lerInteiro();
            indice = buscarDiscoPorId(id);
            if (indice == -1 || acervoDiscos[indice].ativo == 0) {
                printf("\nDisco nao encontrado!\n");
            } else {
                exibirDisco(indice);
            }
            break;
        default:
            printf("\nOpcao invalida!\n");
    }
}

void editarDisco() {
    int id, indice;

    printf("\nDigite o ID do disco que deseja editar: ");
    id = lerInteiro();

    indice = buscarDiscoPorId(id);
    if (indice == -1 || acervoDiscos[indice].ativo == 0) {
        printf("\nDisco nao encontrado!\n");
        return;
    }

    printf("\nDados atuais:");
    exibirDisco(indice);

    do {
        printf("\nNovo preco: R$ ");
        acervoDiscos[indice].preco = lerReal();
        if (acervoDiscos[indice].preco <= 0) {
            printf("Preco invalido! Deve ser maior que zero.\n");
        }
    } while (acervoDiscos[indice].preco <= 0);

    do {
        printf("Novo estoque: ");
        acervoDiscos[indice].quantidadeEstoque = lerInteiro();
        if (acervoDiscos[indice].quantidadeEstoque < 0) {
            printf("Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (acervoDiscos[indice].quantidadeEstoque < 0);

    printf("\nDisco atualizado com sucesso!\n");
}

void removerDisco() {
    int id, indice;

    printf("\nDigite o ID do disco que deseja remover: ");
    id = lerInteiro();

    indice = buscarDiscoPorId(id);
    if (indice == -1 || acervoDiscos[indice].ativo == 0) {
        printf("\nDisco nao encontrado!\n");
        return;
    }

    acervoDiscos[indice].ativo = 0;
    printf("\nDisco '%s' removido do acervo!\n", acervoDiscos[indice].titulo);
}

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
        opcaoDisco = lerInteiro();

        switch (opcaoDisco) {
            case 1:
                cadastrarDisco();
                break;
            case 2:
                listarDiscos();
                break;
            case 3:
                editarDisco();
                break;
            case 4:
                removerDisco();
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

void tocarMusica(char nomeGenero[], char musicas[][50], int totalMusicas) {
    int escolha;
    int i;

    printf("\n==============================\n");
    printf("   GENERO: %s\n", nomeGenero);
    printf("==============================\n");

    for (i = 0; i < totalMusicas; i++) {
        printf("[%d] %s\n", i + 1, musicas[i]);
    }

    printf("[0] Voltar aos generos\n");
    printf("Escolha o numero da musica que deseja tocar: ");
    escolha = lerInteiro();

    if (escolha > 0 && escolha <= totalMusicas) {
        printf("\n>> Tocando agora: '%s' <<\n\n", musicas[escolha - 1]);
    } else if (escolha == 0) {
        printf("\nVoltando...\n\n");
    } else {
        printf("\nOpcao invalida!\n\n");
    }
}

// Menu de generos da cabine de escuta
void escutarMusicas() {
    int opcaoGenero;
    int i;

    char generos[4][20] = {"Rock", "Pop", "Gaucha", "Jazz"};
    int totalGeneros = 4;

    char rockMusicas[3][50] = {
        "Stairway to Heaven - Led Zeppelin",
        "Smells Like Teen Spirit - Nirvana",
        "Back in Black - AC/DC"
    };

    char popMusicas[3][50] = {
        "Billie Jean - Michael Jackson",
        "Bad Romance - Lady Gaga",
        "Blinding Lights - The Weeknd"
    };

    char gauchaMusicas[3][50] = {
        "Canto Alegretense - Os Mateadores",
        "Baile de Fole - Teixeirinha",
        "Gauchinha Melindrosa - Almira e Zico"
    };

    char jazzMusicas[3][50] = {
        "Take Five - Dave Brubeck",
        "So What - Miles Davis",
        "Fly Me to the Moon - Frank Sinatra"
    };

    do {
        printf("\n==============================\n");
        printf("   CABINE DE ESCUTA - GENEROS\n");
        printf("==============================\n");
        for (i = 0; i < totalGeneros; i++) {
            printf("[%d] %s\n", i + 1, generos[i]);
        }
        printf("[0] Voltar ao Modulo de Cabines\n");
        printf("Escolha um genero musical: ");
        opcaoGenero = lerInteiro();

        switch (opcaoGenero) {
            case 1:
                tocarMusica(generos[0], rockMusicas, 3);
                break;
            case 2:
                tocarMusica(generos[1], popMusicas, 3);
                break;
            case 3:
                tocarMusica(generos[2], gauchaMusicas, 3);
                break;
            case 4:
                tocarMusica(generos[3], jazzMusicas, 3);
                break;
            case 0:
                printf("\nSaindo da cabine de escuta...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcaoGenero != 0);
}

int buscarCabinePorId(int id) {
    int i;

    for (i = 0; i < totalCabines; i++) {
        if (listaCabines[i].idCabine == id) {
            return i;
        }
    }
    return -1;
}

void exibirCabine(int i) {
    printf("\nCabine ID %d\n", listaCabines[i].idCabine);
    printf("Numero: %d\n", listaCabines[i].numeroCabine);
    printf("Descricao: %s\n", listaCabines[i].descricao);
    printf("Valor por hora: R$ %.2f\n", listaCabines[i].valorHoraUso);
    if (listaCabines[i].statusOcupacao == 1) {
        printf("Status: OCUPADA (Cliente ID %d, %d minuto(s) de uso)\n",
               listaCabines[i].idClienteUsando, listaCabines[i].tempoUsoMinutos);
    } else {
        printf("Status: LIVRE\n");
    }
}

void cadastrarCabine() {
    if (totalCabines >= 50) {
        printf("\nLimite de 50 cabines atingido!\n");
        return;
    }

    listaCabines[totalCabines].idCabine = totalCabines + 1;
    printf("\nID gerado para a cabine: %d\n", listaCabines[totalCabines].idCabine);

    printf("Numero da cabine: ");
    listaCabines[totalCabines].numeroCabine = lerInteiro();

    printf("Descricao (sem espacos, use _ no lugar): ");
    scanf("%39s", listaCabines[totalCabines].descricao);
    limparBuffer();

    do {
        printf("Valor por hora de uso: R$ ");
        listaCabines[totalCabines].valorHoraUso = lerReal();
        if (listaCabines[totalCabines].valorHoraUso < 0) {
            printf("Valor invalido! Nao pode ser negativo.\n");
        }
    } while (listaCabines[totalCabines].valorHoraUso < 0);

    listaCabines[totalCabines].statusOcupacao = 0;
    listaCabines[totalCabines].tempoUsoMinutos = 0;
    listaCabines[totalCabines].idClienteUsando = 0;
    listaCabines[totalCabines].ativo = 1;
    totalCabines++;

    printf("\nCabine cadastrada com sucesso!\n");
}

void listarCabines() {
    int opcaoListagem, id, indice, i, encontrou;

    printf("\n1. Listar todas as cabines\n");
    printf("2. Listar apenas cabines livres\n");
    printf("3. Listar apenas cabines ocupadas\n");
    printf("4. Buscar cabine por ID\n");
    printf("Escolha: ");
    opcaoListagem = lerInteiro();

    switch (opcaoListagem) {
        case 1:
        case 2:
        case 3:
            encontrou = 0;
            printf("\n===== CABINES DE ESCUTA =====\n");
            for (i = 0; i < totalCabines; i++) {
                if (listaCabines[i].ativo == 1) {
                    if (opcaoListagem == 1 ||
                        (opcaoListagem == 2 && listaCabines[i].statusOcupacao == 0) ||
                        (opcaoListagem == 3 && listaCabines[i].statusOcupacao == 1)) {
                        exibirCabine(i);
                        encontrou++;
                    }
                }
            }
            if (encontrou == 0) {
                printf("Nenhuma cabine encontrada.\n");
            }
            break;
        case 4:
            printf("\nDigite o ID da cabine: ");
            id = lerInteiro();
            indice = buscarCabinePorId(id);
            if (indice == -1 || listaCabines[indice].ativo == 0) {
                printf("\nCabine nao encontrada!\n");
            } else {
                exibirCabine(indice);
            }
            break;
        default:
            printf("\nOpcao invalida!\n");
    }
}

void editarCabine() {
    int id, indice, idCliente, indiceCliente;

    printf("\nDigite o ID da cabine que deseja editar: ");
    id = lerInteiro();

    indice = buscarCabinePorId(id);
    if (indice == -1 || listaCabines[indice].ativo == 0) {
        printf("\nCabine nao encontrada!\n");
        return;
    }

    printf("\nDados atuais:");
    exibirCabine(indice);

    do {
        printf("\nNovo status (1 = Ocupada, 0 = Livre): ");
        listaCabines[indice].statusOcupacao = lerInteiro();
        if (listaCabines[indice].statusOcupacao != 0 && listaCabines[indice].statusOcupacao != 1) {
            printf("Status invalido! Digite 0 ou 1.\n");
        }
    } while (listaCabines[indice].statusOcupacao != 0 && listaCabines[indice].statusOcupacao != 1);

    if (listaCabines[indice].statusOcupacao == 1) {
        printf("ID do cliente usando a cabine: ");
        idCliente = lerInteiro();

        indiceCliente = buscarClientePorId(idCliente);
        if (indiceCliente == -1 || listaClientes[indiceCliente].ativo == 0) {
            printf("\nCliente nao encontrado! A cabine foi mantida como LIVRE.\n");
            listaCabines[indice].statusOcupacao = 0;
            listaCabines[indice].tempoUsoMinutos = 0;
            listaCabines[indice].idClienteUsando = 0;
            return;
        }

        listaCabines[indice].idClienteUsando = idCliente;

        do {
            printf("Tempo de uso em minutos: ");
            listaCabines[indice].tempoUsoMinutos = lerInteiro();
            if (listaCabines[indice].tempoUsoMinutos < 0) {
                printf("Tempo invalido! Nao pode ser negativo.\n");
            }
        } while (listaCabines[indice].tempoUsoMinutos < 0);
    } else {
        listaCabines[indice].tempoUsoMinutos = 0;
        listaCabines[indice].idClienteUsando = 0;
    }

    printf("\nCabine atualizada com sucesso!\n");
}

void removerCabine() {
    int id, indice;

    printf("\nDigite o ID da cabine que deseja dar baixa: ");
    id = lerInteiro();

    indice = buscarCabinePorId(id);
    if (indice == -1 || listaCabines[indice].ativo == 0) {
        printf("\nCabine nao encontrada!\n");
        return;
    }

    listaCabines[indice].ativo = 0;
    listaCabines[indice].statusOcupacao = 0;
    listaCabines[indice].tempoUsoMinutos = 0;
    listaCabines[indice].idClienteUsando = 0;
    printf("\nBaixa da cabine %d realizada com sucesso!\n", listaCabines[indice].numeroCabine);
}

void moduloCabines() {
    int opcaoCabine;

    do {
        printf("\n--- [MODULO 2: CABINES DE ESCUTA (Guilherme Monteiro de Andrade)] ---\n");
        printf("1. Cadastrar Nova Cabine\n");
        printf("2. Listar / Buscar Cabines (Livres e Ocupadas)\n");
        printf("3. Editar Cabine (Status / Tempo de Uso / Cliente)\n");
        printf("4. Remover Cabine (Dar Baixa)\n");
        printf("5. Ouvir Musicas na Cabine (por Genero)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoCabine = lerInteiro();

        switch (opcaoCabine) {
            case 1:
                cadastrarCabine();
                break;
            case 2:
                listarCabines();
                break;
            case 3:
                editarCabine();
                break;
            case 4:
                removerCabine();
                break;
            case 5:
                escutarMusicas();
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

void exibirCliente(int i) {
    printf("\nCliente ID %d\n", listaClientes[i].idCliente);
    printf("Nome: %s\n", listaClientes[i].nome);
    printf("Telefone: %s\n", listaClientes[i].telefone);
    printf("Pontos de fidelidade: %d\n", listaClientes[i].pontosFidelidade);
}

void cadastrarCliente() {
    if (totalClientes >= 50) {
        printf("\nLimite de 50 clientes atingido!\n");
        return;
    }

    listaClientes[totalClientes].idCliente = totalClientes + 1;
    printf("\nID gerado para o cliente: %d\n", listaClientes[totalClientes].idCliente);

    printf("Nome (sem espacos, use _ no lugar): ");
    scanf("%49s", listaClientes[totalClientes].nome);
    limparBuffer();

    printf("Telefone (somente numeros): ");
    scanf("%19s", listaClientes[totalClientes].telefone);
    limparBuffer();

    listaClientes[totalClientes].pontosFidelidade = 0;
    listaClientes[totalClientes].ativo = 1;
    totalClientes++;

    printf("\nCliente cadastrado com sucesso!\n");
}

void listarClientes() {
    int opcaoListagem, id, indice, i, encontrou;

    printf("\n1. Listar todos os clientes\n");
    printf("2. Buscar cliente por ID\n");
    printf("Escolha: ");
    opcaoListagem = lerInteiro();

    switch (opcaoListagem) {
        case 1:
            encontrou = 0;
            printf("\n===== CLIENTES DO CLUBE DO VINIL =====\n");
            for (i = 0; i < totalClientes; i++) {
                if (listaClientes[i].ativo == 1) {
                    exibirCliente(i);
                    encontrou++;
                }
            }
            if (encontrou == 0) {
                printf("Nenhum cliente cadastrado.\n");
            }
            break;
        case 2:
            printf("\nDigite o ID do cliente: ");
            id = lerInteiro();
            indice = buscarClientePorId(id);
            if (indice == -1 || listaClientes[indice].ativo == 0) {
                printf("\nCliente nao encontrado!\n");
            } else {
                exibirCliente(indice);
            }
            break;
        default:
            printf("\nOpcao invalida!\n");
    }
}

void editarCliente() {
    int id, indice, opcaoEdicao;

    printf("\nDigite o ID do cliente que deseja editar: ");
    id = lerInteiro();

    indice = buscarClientePorId(id);
    if (indice == -1 || listaClientes[indice].ativo == 0) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("\nDados atuais:");
    exibirCliente(indice);

    printf("\nO que deseja alterar?\n");
    printf("1. Nome\n");
    printf("2. Telefone\n");
    printf("3. Pontos de fidelidade\n");
    printf("Escolha: ");
    opcaoEdicao = lerInteiro();

    switch (opcaoEdicao) {
        case 1:
            printf("Novo nome (sem espacos, use _ no lugar): ");
            scanf("%49s", listaClientes[indice].nome);
            limparBuffer();
            printf("\nNome atualizado com sucesso!\n");
            break;
        case 2:
            printf("Novo telefone (somente numeros): ");
            scanf("%19s", listaClientes[indice].telefone);
            limparBuffer();
            printf("\nTelefone atualizado com sucesso!\n");
            break;
        case 3:
            do {
                printf("Novos pontos de fidelidade: ");
                listaClientes[indice].pontosFidelidade = lerInteiro();
                if (listaClientes[indice].pontosFidelidade < 0) {
                    printf("Pontos invalidos! Nao podem ser negativos.\n");
                }
            } while (listaClientes[indice].pontosFidelidade < 0);
            printf("\nPontos atualizados com sucesso!\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
    }
}

void removerCliente() {
    int id, indice;

    printf("\nDigite o ID do cliente que deseja remover: ");
    id = lerInteiro();

    indice = buscarClientePorId(id);
    if (indice == -1 || listaClientes[indice].ativo == 0) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    listaClientes[indice].ativo = 0;
    printf("\nCliente '%s' removido com sucesso!\n", listaClientes[indice].nome);
}

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
        opcaoCliente = lerInteiro();

        switch (opcaoCliente) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                editarCliente();
                break;
            case 4:
                removerCliente();
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
// MODULO 4: PERSPECTIVA DE VENDAS E RELATORIOS
// Autor: Bernardo Novaski Vidal de Almeida
// ----------------------------------------------------------------------------

void exibirVenda(int i) {
    int indiceDisco, indiceCliente;

    indiceDisco = buscarDiscoPorId(historicoVendas[i].idDiscoVendido);
    indiceCliente = buscarClientePorId(historicoVendas[i].idClienteComprador);

    printf("\nVenda ID %d - Data: %s\n", historicoVendas[i].idVenda, historicoVendas[i].dataVenda);
    if (indiceCliente != -1) {
        printf("Cliente: %s (ID %d)\n", listaClientes[indiceCliente].nome, historicoVendas[i].idClienteComprador);
    }
    if (indiceDisco != -1) {
        printf("Disco: %s (ID %d)\n", acervoDiscos[indiceDisco].titulo, historicoVendas[i].idDiscoVendido);
    }
    printf("Quantidade: %d | Valor total: R$ %.2f\n", historicoVendas[i].quantidade, historicoVendas[i].valorTotal);
    if (historicoVendas[i].ativo == 1) {
        printf("Situacao: EFETIVADA\n");
    } else {
        printf("Situacao: CANCELADA\n");
    }
}

void registrarVenda() {
    int idCliente, idDisco, quantidade, indiceCliente, indiceDisco;

    if (totalVendas >= 50) {
        printf("\nLimite de 50 vendas atingido!\n");
        return;
    }

    if (totalClientes == 0 || totalDiscos == 0) {
        printf("\nCadastre ao menos 1 cliente e 1 disco antes de registrar uma venda!\n");
        return;
    }

    printf("\nID do cliente comprador: ");
    idCliente = lerInteiro();
    indiceCliente = buscarClientePorId(idCliente);
    if (indiceCliente == -1 || listaClientes[indiceCliente].ativo == 0) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("ID do disco vendido: ");
    idDisco = lerInteiro();
    indiceDisco = buscarDiscoPorId(idDisco);
    if (indiceDisco == -1 || acervoDiscos[indiceDisco].ativo == 0) {
        printf("\nDisco nao encontrado!\n");
        return;
    }

    do {
        printf("Quantidade: ");
        quantidade = lerInteiro();
        if (quantidade <= 0) {
            printf("Quantidade invalida! Deve ser maior que zero.\n");
        }
    } while (quantidade <= 0);

    if (quantidade > acervoDiscos[indiceDisco].quantidadeEstoque) {
        printf("\nEstoque insuficiente! Disponivel: %d unidade(s).\n", acervoDiscos[indiceDisco].quantidadeEstoque);
        return;
    }

    historicoVendas[totalVendas].idVenda = totalVendas + 1;
    historicoVendas[totalVendas].idClienteComprador = idCliente;
    historicoVendas[totalVendas].idDiscoVendido = idDisco;
    historicoVendas[totalVendas].quantidade = quantidade;
    historicoVendas[totalVendas].valorTotal = acervoDiscos[indiceDisco].preco * quantidade;

    printf("Data da venda (DD/MM/AAAA): ");
    scanf("%10s", historicoVendas[totalVendas].dataVenda);
    limparBuffer();

    historicoVendas[totalVendas].ativo = 1;

    // Atualiza estoque do disco e pontos do cliente (1 ponto por disco comprado)
    acervoDiscos[indiceDisco].quantidadeEstoque = acervoDiscos[indiceDisco].quantidadeEstoque - quantidade;
    listaClientes[indiceCliente].pontosFidelidade = listaClientes[indiceCliente].pontosFidelidade + quantidade;

    printf("\nVenda %d registrada! Total: R$ %.2f\n", historicoVendas[totalVendas].idVenda, historicoVendas[totalVendas].valorTotal);

    totalVendas++;
}

void listarHistoricoVendas() {
    int i;
    float faturamento = 0;

    printf("\n===== HISTORICO DE VENDAS =====\n");

    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    for (i = 0; i < totalVendas; i++) {
        exibirVenda(i);
        if (historicoVendas[i].ativo == 1) {
            faturamento = faturamento + historicoVendas[i].valorTotal;
        }
    }

    printf("\nFaturamento total (vendas efetivadas): R$ %.2f\n", faturamento);
}

void cancelarVenda() {
    int idVenda, indiceVenda, indiceDisco, indiceCliente, i;

    indiceVenda = -1;

    printf("\nDigite o ID da venda que deseja cancelar: ");
    idVenda = lerInteiro();

    for (i = 0; i < totalVendas; i++) {
        if (historicoVendas[i].idVenda == idVenda) {
            indiceVenda = i;
        }
    }

    if (indiceVenda == -1) {
        printf("\nVenda nao encontrada!\n");
        return;
    }

    if (historicoVendas[indiceVenda].ativo == 0) {
        printf("\nEssa venda ja foi cancelada!\n");
        return;
    }

    historicoVendas[indiceVenda].ativo = 0;

    // Devolve o disco no estoque
    indiceDisco = buscarDiscoPorId(historicoVendas[indiceVenda].idDiscoVendido);
    if (indiceDisco != -1) {
        acervoDiscos[indiceDisco].quantidadeEstoque = acervoDiscos[indiceDisco].quantidadeEstoque + historicoVendas[indiceVenda].quantidade;
    }

    // tira os pontos ganhos pelo cliente
    indiceCliente = buscarClientePorId(historicoVendas[indiceVenda].idClienteComprador);
    if (indiceCliente != -1) {
        listaClientes[indiceCliente].pontosFidelidade = listaClientes[indiceCliente].pontosFidelidade - historicoVendas[indiceVenda].quantidade;
        if (listaClientes[indiceCliente].pontosFidelidade < 0) {
            listaClientes[indiceCliente].pontosFidelidade = 0;
        }
    }

    printf("\nVenda %d cancelada! Estoque e pontos foram ajustados.\n", idVenda);
}

void relatorioDiscoMaisVendido() {
    int i, j, soma, maior, indiceMaior;

    maior = 0;
    indiceMaior = -1;

    for (i = 0; i < totalDiscos; i++) {
        soma = 0;
        for (j = 0; j < totalVendas; j++) {
            if (historicoVendas[j].ativo == 1 && historicoVendas[j].idDiscoVendido == acervoDiscos[i].idDisco) {
                soma = soma + historicoVendas[j].quantidade;
            }
        }
        if (soma > maior) {
            maior = soma;
            indiceMaior = i;
        }
    }

    printf("\n===== RELATORIO: DISCO MAIS VENDIDO =====\n");
    if (indiceMaior == -1) {
        printf("Nenhuma venda efetivada ate o momento.\n");
    } else {
        printf("Titulo: %s\n", acervoDiscos[indiceMaior].titulo);
        printf("Artista: %s\n", acervoDiscos[indiceMaior].artista);
        printf("Unidades vendidas: %d\n", maior);
    }
}

void relatorioClienteVip() {
    int i, j, compras, maior, indiceMaior;
    float gasto, gastoMaior;

    maior = 0;
    gastoMaior = 0;
    indiceMaior = -1;

    for (i = 0; i < totalClientes; i++) {
        compras = 0;
        gasto = 0;
        for (j = 0; j < totalVendas; j++) {
            if (historicoVendas[j].ativo == 1 && historicoVendas[j].idClienteComprador == listaClientes[i].idCliente) {
                compras = compras + 1;
                gasto = gasto + historicoVendas[j].valorTotal;
            }
        }
        if (compras > maior) {
            maior = compras;
            gastoMaior = gasto;
            indiceMaior = i;
        }
    }

    printf("\n===== RELATORIO: CLIENTE VIP =====\n");
    if (indiceMaior == -1) {
        printf("Nenhuma venda efetivada ate o momento.\n");
    } else {
        printf("Cliente: %s (ID %d)\n", listaClientes[indiceMaior].nome, listaClientes[indiceMaior].idCliente);
        printf("Numero de compras: %d\n", maior);
        printf("Total gasto: R$ %.2f\n", gastoMaior);
    }
}

void relatorioComprasPorCliente() {
    int idCliente, indiceCliente, i, encontrou;
    float totalGasto;

    encontrou = 0;
    totalGasto = 0;

    printf("\nDigite o ID do cliente: ");
    idCliente = lerInteiro();

    indiceCliente = buscarClientePorId(idCliente);
    if (indiceCliente == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("\n===== COMPRAS DE %s =====\n", listaClientes[indiceCliente].nome);

    for (i = 0; i < totalVendas; i++) {
        if (historicoVendas[i].ativo == 1 && historicoVendas[i].idClienteComprador == idCliente) {
            exibirVenda(i);
            totalGasto = totalGasto + historicoVendas[i].valorTotal;
            encontrou++;
        }
    }

    if (encontrou == 0) {
        printf("Nenhuma compra efetivada para este cliente.\n");
    } else {
        printf("\nTotal de compras: %d | Total gasto: R$ %.2f\n", encontrou, totalGasto);
    }
}

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
        opcaoVenda = lerInteiro();

        switch (opcaoVenda) {
            case 1:
                registrarVenda();
                break;
            case 2:
                listarHistoricoVendas();
                break;
            case 3:
                cancelarVenda();
                break;
            case 4:
                relatorioDiscoMaisVendido();
                break;
            case 5:
                relatorioClienteVip();
                break;
            case 6:
                relatorioComprasPorCliente();
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
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - MENUS
// ============================================================================
int main() {
    int opcaoPrincipal;

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
        opcaoPrincipal = lerInteiro();

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
