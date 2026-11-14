// Arquivo: discos.h | Autor: Nathan Souza Gusso
#ifndef DISCOS_H
#define DISCOS_H

#include <stdio.h>
#include <string.h>

#define MAX_DISCOS 50

struct Disco {
    int idDisco;
    char titulo[50];
    char artista[50];
    float preco;
    int quantidadeEstoque;
};

struct Disco acervoDiscos[MAX_DISCOS];
int totalDiscos = 0;

// PERSISTENCIA: regrava o vetor inteiro no arquivo (modo "w" zera o arquivo)
void salvarDiscosCSV() {
    FILE *arq = fopen("discos.csv", "w");
    int i;

    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar discos.csv!\n");
        return;
    }

    for (i = 0; i < totalDiscos; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d\n",
                acervoDiscos[i].idDisco,
                acervoDiscos[i].titulo,
                acervoDiscos[i].artista,
                acervoDiscos[i].preco,
                acervoDiscos[i].quantidadeEstoque);
    }
    fclose(arq);
}

// PERSISTENCIA: le o arquivo ao abrir o programa e preenche o vetor
void carregarDiscosCSV() {
    FILE *arq = fopen("discos.csv", "r");

    if (arq == NULL) {
        return; // sem arquivo ainda: comeca com 0 registros
    }

    totalDiscos = 0;
    while (totalDiscos < MAX_DISCOS &&
           fscanf(arq, "%d;%49[^;];%49[^;];%f;%d\n",
                  &acervoDiscos[totalDiscos].idDisco,
                  acervoDiscos[totalDiscos].titulo,
                  acervoDiscos[totalDiscos].artista,
                  &acervoDiscos[totalDiscos].preco,
                  &acervoDiscos[totalDiscos].quantidadeEstoque) == 5) {
        totalDiscos++;
    }
    fclose(arq);
}

// Retorna a posicao do ID no vetor ou -1 se nao existir
int buscarDiscoPorId(int id) {
    int i;

    for (i = 0; i < totalDiscos; i++) {
        if (acervoDiscos[i].idDisco == id) {
            return i;
        }
    }
    return -1;
}

// Novo ID = maior ID existente + 1 (evita repetir ID depois de remover)
int proximoIdDisco() {
    int i, maior = 0;

    for (i = 0; i < totalDiscos; i++) {
        if (acervoDiscos[i].idDisco > maior) {
            maior = acervoDiscos[i].idDisco;
        }
    }
    return maior + 1;
}

void exibirDisco(int i) {
    printf("ID: %d | %-25s | %-20s | R$ %7.2f | Estoque: %d\n",
           acervoDiscos[i].idDisco,
           acervoDiscos[i].titulo,
           acervoDiscos[i].artista,
           acervoDiscos[i].preco,
           acervoDiscos[i].quantidadeEstoque);
}

void cadastrarDisco() {
    int pos = totalDiscos;

    if (totalDiscos >= MAX_DISCOS) {
        printf("\nLimite de %d discos atingido!\n", MAX_DISCOS);
        return;
    }

    acervoDiscos[pos].idDisco = proximoIdDisco();
    printf("\nID gerado para o disco: %d\n", acervoDiscos[pos].idDisco);

    printf("Titulo: ");
    scanf(" %49[^\n]", acervoDiscos[pos].titulo);

    printf("Artista: ");
    scanf(" %49[^\n]", acervoDiscos[pos].artista);

    do {
        printf("Preco do disco: R$ ");
        scanf("%f", &acervoDiscos[pos].preco);
        if (acervoDiscos[pos].preco <= 0) {
            printf("Preco invalido! Deve ser maior que zero.\n");
        }
    } while (acervoDiscos[pos].preco <= 0);

    do {
        printf("Quantidade em estoque: ");
        scanf("%d", &acervoDiscos[pos].quantidadeEstoque);
        if (acervoDiscos[pos].quantidadeEstoque < 0) {
            printf("Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (acervoDiscos[pos].quantidadeEstoque < 0);

    totalDiscos++;
    salvarDiscosCSV();
    printf("\nDisco cadastrado e salvo em 'discos.csv'!\n");
}

void listarDiscos() {
    int i;

    printf("\n===== ACERVO DE DISCOS (%d itens) =====\n", totalDiscos);
    if (totalDiscos == 0) {
        printf("Nenhum disco cadastrado.\n");
        return;
    }
    for (i = 0; i < totalDiscos; i++) {
        exibirDisco(i);
    }
}

// Busca textual: procura o termo dentro do titulo ou do artista
void buscarDiscoPorNome() {
    char termo[50];
    int i, encontrou = 0;

    printf("\nDigite parte do titulo ou do artista: ");
    scanf(" %49[^\n]", termo);

    for (i = 0; i < totalDiscos; i++) {
        if (strstr(acervoDiscos[i].titulo, termo) != NULL ||
            strstr(acervoDiscos[i].artista, termo) != NULL) {
            exibirDisco(i);
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum disco encontrado com '%s'.\n", termo);
    }
}

void editarDisco() {
    int id, pos;

    printf("\nDigite o ID do disco que deseja editar: ");
    scanf("%d", &id);

    pos = buscarDiscoPorId(id);
    if (pos == -1) {
        printf("\nDisco nao encontrado!\n");
        return;
    }

    printf("\nDados atuais:\n");
    exibirDisco(pos);

    do {
        printf("\nNovo preco: R$ ");
        scanf("%f", &acervoDiscos[pos].preco);
        if (acervoDiscos[pos].preco <= 0) {
            printf("Preco invalido! Deve ser maior que zero.\n");
        }
    } while (acervoDiscos[pos].preco <= 0);

    do {
        printf("Novo estoque: ");
        scanf("%d", &acervoDiscos[pos].quantidadeEstoque);
        if (acervoDiscos[pos].quantidadeEstoque < 0) {
            printf("Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (acervoDiscos[pos].quantidadeEstoque < 0);

    salvarDiscosCSV();
    printf("\nDisco atualizado na memoria e no arquivo CSV!\n");
}

// Remocao fisica: puxa os itens seguintes para cobrir a posicao e regrava o CSV
void removerDisco() {
    int id, pos, j;

    printf("\nDigite o ID do disco que deseja remover: ");
    scanf("%d", &id);

    pos = buscarDiscoPorId(id);
    if (pos == -1) {
        printf("\nDisco nao encontrado!\n");
        return;
    }

    printf("\nDisco '%s' removido do acervo!\n", acervoDiscos[pos].titulo);
    for (j = pos; j < totalDiscos - 1; j++) {
        acervoDiscos[j] = acervoDiscos[j + 1];
    }
    totalDiscos--;
    salvarDiscosCSV();
}

void moduloDiscos() {
    int opcaoDisco;

    do {
        printf("\n--- [MODULO 1: ACERVO DE DISCOS (Nathan Souza Gusso)] ---\n");
        printf("1. Cadastrar Novo Disco\n");
        printf("2. Listar Discos\n");
        printf("3. Buscar Disco por Titulo/Artista\n");
        printf("4. Editar Disco (Preco / Estoque)\n");
        printf("5. Remover Disco do Acervo\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoDisco);

        switch (opcaoDisco) {
            case 1: cadastrarDisco(); break;
            case 2: listarDiscos(); break;
            case 3: buscarDiscoPorNome(); break;
            case 4: editarDisco(); break;
            case 5: removerDisco(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcaoDisco != 0);
}

#endif
