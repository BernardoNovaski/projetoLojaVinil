// Arquivo: clientes.h | Autor: Jose Gustavo da Silva Bertoche
#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 50

struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    int pontosFidelidade;
};

struct Cliente listaClientes[MAX_CLIENTES];
int totalClientes = 0;

// PERSISTENCIA: regrava o vetor inteiro em clientes.csv
void salvarClientesCSV() {
    FILE *arq = fopen("clientes.csv", "w");
    int i;

    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar clientes.csv!\n");
        return;
    }

    for (i = 0; i < totalClientes; i++) {
        fprintf(arq, "%d;%s;%s;%d\n",
                listaClientes[i].idCliente,
                listaClientes[i].nome,
                listaClientes[i].telefone,
                listaClientes[i].pontosFidelidade);
    }
    fclose(arq);
}

// PERSISTENCIA: le clientes.csv ao abrir o programa
void carregarClientesCSV() {
    FILE *arq = fopen("clientes.csv", "r");

    if (arq == NULL) {
        return;
    }

    totalClientes = 0;
    while (totalClientes < MAX_CLIENTES &&
           fscanf(arq, "%d;%49[^;];%19[^;];%d\n",
                  &listaClientes[totalClientes].idCliente,
                  listaClientes[totalClientes].nome,
                  listaClientes[totalClientes].telefone,
                  &listaClientes[totalClientes].pontosFidelidade) == 4) {
        totalClientes++;
    }
    fclose(arq);
}

int buscarClientePorId(int id) {
    int i;

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id) {
            return i;
        }
    }
    return -1;
}

int proximoIdCliente() {
    int i, maior = 0;

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente > maior) {
            maior = listaClientes[i].idCliente;
        }
    }
    return maior + 1;
}

void exibirCliente(int i) {
    printf("ID: %d | %-25s | Tel: %-12s | Pontos: %d\n",
           listaClientes[i].idCliente,
           listaClientes[i].nome,
           listaClientes[i].telefone,
           listaClientes[i].pontosFidelidade);
}

void cadastrarCliente() {
    int pos = totalClientes;

    if (totalClientes >= MAX_CLIENTES) {
        printf("\nLimite de %d clientes atingido!\n", MAX_CLIENTES);
        return;
    }

    listaClientes[pos].idCliente = proximoIdCliente();
    printf("\nID gerado para o cliente: %d\n", listaClientes[pos].idCliente);

    printf("Nome: ");
    scanf(" %49[^\n]", listaClientes[pos].nome);

    printf("Telefone (somente numeros): ");
    scanf(" %19s", listaClientes[pos].telefone);

    listaClientes[pos].pontosFidelidade = 0;

    totalClientes++;
    salvarClientesCSV();
    printf("\nCliente cadastrado e salvo em 'clientes.csv'!\n");
}

void listarClientes() {
    int i;

    printf("\n===== CLIENTES DO CLUBE DO VINIL (%d) =====\n", totalClientes);
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    for (i = 0; i < totalClientes; i++) {
        exibirCliente(i);
    }
}

// Busca textual: procura o termo dentro do nome
void buscarClientePorNome() {
    char termo[50];
    int i, encontrou = 0;

    printf("\nDigite parte do nome do cliente: ");
    scanf(" %49[^\n]", termo);

    for (i = 0; i < totalClientes; i++) {
        if (strstr(listaClientes[i].nome, termo) != NULL) {
            exibirCliente(i);
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum cliente encontrado com '%s'.\n", termo);
    }
}

void editarCliente() {
    int id, pos, opcaoEdicao;

    printf("\nDigite o ID do cliente que deseja editar: ");
    scanf("%d", &id);

    pos = buscarClientePorId(id);
    if (pos == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("\nDados atuais:\n");
    exibirCliente(pos);

    printf("\nO que deseja alterar?\n");
    printf("1. Nome\n2. Telefone\n3. Pontos de fidelidade\nEscolha: ");
    scanf("%d", &opcaoEdicao);

    switch (opcaoEdicao) {
        case 1:
            printf("Novo nome: ");
            scanf(" %49[^\n]", listaClientes[pos].nome);
            break;
        case 2:
            printf("Novo telefone (somente numeros): ");
            scanf(" %19s", listaClientes[pos].telefone);
            break;
        case 3:
            do {
                printf("Novos pontos de fidelidade: ");
                scanf("%d", &listaClientes[pos].pontosFidelidade);
                if (listaClientes[pos].pontosFidelidade < 0) {
                    printf("Pontos invalidos! Nao podem ser negativos.\n");
                }
            } while (listaClientes[pos].pontosFidelidade < 0);
            break;
        default:
            printf("\nOpcao invalida!\n");
            return;
    }

    salvarClientesCSV();
    printf("\nCliente atualizado na memoria e no arquivo CSV!\n");
}

void removerCliente() {
    int id, pos, j;

    printf("\nDigite o ID do cliente que deseja remover: ");
    scanf("%d", &id);

    pos = buscarClientePorId(id);
    if (pos == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("\nCliente '%s' removido com sucesso!\n", listaClientes[pos].nome);
    for (j = pos; j < totalClientes - 1; j++) {
        listaClientes[j] = listaClientes[j + 1];
    }
    totalClientes--;
    salvarClientesCSV();
}

void moduloClientes() {
    int opcaoCliente;

    do {
        printf("\n--- [MODULO 3: CLIENTES DO CLUBE DO VINIL (Jose Gustavo da Silva Bertoche)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente por Nome\n");
        printf("4. Editar Cliente\n");
        printf("5. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCliente);

        switch (opcaoCliente) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: buscarClientePorNome(); break;
            case 4: editarCliente(); break;
            case 5: removerCliente(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcaoCliente != 0);
}

#endif
