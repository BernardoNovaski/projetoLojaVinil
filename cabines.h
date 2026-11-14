// Arquivo: cabines.h | Autor: Guilherme Monteiro de Andrade
#ifndef CABINES_H
#define CABINES_H

#include <stdio.h>
#include <string.h>
#include "clientes.h"

#define MAX_CABINES 50

struct Cabine {
    int idCabine;
    int numeroCabine;
    char descricao[40];
    float valorHoraUso;
    int statusOcupacao;      // 1 = Ocupada, 0 = Livre
    int tempoUsoMinutos;
    int idClienteUsando;     // 0 = nenhum cliente
};

struct Cabine listaCabines[MAX_CABINES];
int totalCabines = 0;

// PERSISTENCIA: regrava o vetor inteiro em cabines.csv
void salvarCabinesCSV() {
    FILE *arq = fopen("cabines.csv", "w");
    int i;

    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar cabines.csv!\n");
        return;
    }

    for (i = 0; i < totalCabines; i++) {
        fprintf(arq, "%d;%d;%s;%.2f;%d;%d;%d\n",
                listaCabines[i].idCabine,
                listaCabines[i].numeroCabine,
                listaCabines[i].descricao,
                listaCabines[i].valorHoraUso,
                listaCabines[i].statusOcupacao,
                listaCabines[i].tempoUsoMinutos,
                listaCabines[i].idClienteUsando);
    }
    fclose(arq);
}

// PERSISTENCIA: le cabines.csv ao abrir o programa
void carregarCabinesCSV() {
    FILE *arq = fopen("cabines.csv", "r");

    if (arq == NULL) {
        return;
    }

    totalCabines = 0;
    while (totalCabines < MAX_CABINES &&
           fscanf(arq, "%d;%d;%39[^;];%f;%d;%d;%d\n",
                  &listaCabines[totalCabines].idCabine,
                  &listaCabines[totalCabines].numeroCabine,
                  listaCabines[totalCabines].descricao,
                  &listaCabines[totalCabines].valorHoraUso,
                  &listaCabines[totalCabines].statusOcupacao,
                  &listaCabines[totalCabines].tempoUsoMinutos,
                  &listaCabines[totalCabines].idClienteUsando) == 7) {
        totalCabines++;
    }
    fclose(arq);
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

int proximoIdCabine() {
    int i, maior = 0;

    for (i = 0; i < totalCabines; i++) {
        if (listaCabines[i].idCabine > maior) {
            maior = listaCabines[i].idCabine;
        }
    }
    return maior + 1;
}

void exibirCabine(int i) {
    printf("ID: %d | Cabine %d | %-15s | R$ %.2f/h | ",
           listaCabines[i].idCabine,
           listaCabines[i].numeroCabine,
           listaCabines[i].descricao,
           listaCabines[i].valorHoraUso);
    if (listaCabines[i].statusOcupacao == 1) {
        printf("OCUPADA (Cliente %d, %d min)\n",
               listaCabines[i].idClienteUsando, listaCabines[i].tempoUsoMinutos);
    } else {
        printf("LIVRE\n");
    }
}

void cadastrarCabine() {
    int pos = totalCabines;

    if (totalCabines >= MAX_CABINES) {
        printf("\nLimite de %d cabines atingido!\n", MAX_CABINES);
        return;
    }

    listaCabines[pos].idCabine = proximoIdCabine();
    printf("\nID gerado para a cabine: %d\n", listaCabines[pos].idCabine);

    printf("Numero da cabine: ");
    scanf("%d", &listaCabines[pos].numeroCabine);

    printf("Descricao (ex.: Cabine Jazz): ");
    scanf(" %39[^\n]", listaCabines[pos].descricao);

    do {
        printf("Valor por hora de uso: R$ ");
        scanf("%f", &listaCabines[pos].valorHoraUso);
        if (listaCabines[pos].valorHoraUso < 0) {
            printf("Valor invalido! Nao pode ser negativo.\n");
        }
    } while (listaCabines[pos].valorHoraUso < 0);

    listaCabines[pos].statusOcupacao = 0;
    listaCabines[pos].tempoUsoMinutos = 0;
    listaCabines[pos].idClienteUsando = 0;

    totalCabines++;
    salvarCabinesCSV();
    printf("\nCabine cadastrada e salva em 'cabines.csv'!\n");
}

void listarCabines() {
    int opcaoListagem, i, encontrou = 0;

    printf("\n1. Todas as cabines\n2. Apenas livres\n3. Apenas ocupadas\nEscolha: ");
    scanf("%d", &opcaoListagem);

    printf("\n===== CABINES DE ESCUTA =====\n");
    for (i = 0; i < totalCabines; i++) {
        if (opcaoListagem == 1 ||
            (opcaoListagem == 2 && listaCabines[i].statusOcupacao == 0) ||
            (opcaoListagem == 3 && listaCabines[i].statusOcupacao == 1)) {
            exibirCabine(i);
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhuma cabine encontrada.\n");
    }
}

// Busca textual: procura o termo dentro da descricao
void buscarCabinePorDescricao() {
    char termo[40];
    int i, encontrou = 0;

    printf("\nDigite parte da descricao da cabine: ");
    scanf(" %39[^\n]", termo);

    for (i = 0; i < totalCabines; i++) {
        if (strstr(listaCabines[i].descricao, termo) != NULL) {
            exibirCabine(i);
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhuma cabine encontrada com '%s'.\n", termo);
    }
}

void editarCabine() {
    int id, pos, idCliente;

    printf("\nDigite o ID da cabine que deseja editar: ");
    scanf("%d", &id);

    pos = buscarCabinePorId(id);
    if (pos == -1) {
        printf("\nCabine nao encontrada!\n");
        return;
    }

    printf("\nDados atuais:\n");
    exibirCabine(pos);

    do {
        printf("\nNovo status (1 = Ocupada, 0 = Livre): ");
        scanf("%d", &listaCabines[pos].statusOcupacao);
        if (listaCabines[pos].statusOcupacao != 0 && listaCabines[pos].statusOcupacao != 1) {
            printf("Status invalido! Digite 0 ou 1.\n");
        }
    } while (listaCabines[pos].statusOcupacao != 0 && listaCabines[pos].statusOcupacao != 1);

    if (listaCabines[pos].statusOcupacao == 1) {
        printf("ID do cliente usando a cabine: ");
        scanf("%d", &idCliente);

        if (buscarClientePorId(idCliente) == -1) {
            printf("\nCliente nao encontrado! A cabine foi mantida como LIVRE.\n");
            listaCabines[pos].statusOcupacao = 0;
            listaCabines[pos].tempoUsoMinutos = 0;
            listaCabines[pos].idClienteUsando = 0;
            salvarCabinesCSV();
            return;
        }

        listaCabines[pos].idClienteUsando = idCliente;

        do {
            printf("Tempo de uso em minutos: ");
            scanf("%d", &listaCabines[pos].tempoUsoMinutos);
            if (listaCabines[pos].tempoUsoMinutos < 0) {
                printf("Tempo invalido! Nao pode ser negativo.\n");
            }
        } while (listaCabines[pos].tempoUsoMinutos < 0);
    } else {
        listaCabines[pos].tempoUsoMinutos = 0;
        listaCabines[pos].idClienteUsando = 0;
    }

    salvarCabinesCSV();
    printf("\nCabine atualizada na memoria e no arquivo CSV!\n");
}

void removerCabine() {
    int id, pos, j;

    printf("\nDigite o ID da cabine que deseja dar baixa: ");
    scanf("%d", &id);

    pos = buscarCabinePorId(id);
    if (pos == -1) {
        printf("\nCabine nao encontrada!\n");
        return;
    }

    printf("\nBaixa da cabine %d realizada!\n", listaCabines[pos].numeroCabine);
    for (j = pos; j < totalCabines - 1; j++) {
        listaCabines[j] = listaCabines[j + 1];
    }
    totalCabines--;
    salvarCabinesCSV();
}

// ---------------- Cabine de escuta: musicas por genero ----------------

void tocarMusica(char nomeGenero[], char musicas[][50], int totalMusicas) {
    int escolha, i;

    printf("\n==============================\n");
    printf("   GENERO: %s\n", nomeGenero);
    printf("==============================\n");

    for (i = 0; i < totalMusicas; i++) {
        printf("[%d] %s\n", i + 1, musicas[i]);
    }

    printf("[0] Voltar aos generos\n");
    printf("Escolha o numero da musica que deseja tocar: ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= totalMusicas) {
        printf("\n>> Tocando agora: '%s' <<\n\n", musicas[escolha - 1]);
    } else if (escolha == 0) {
        printf("\nVoltando...\n\n");
    } else {
        printf("\nOpcao invalida!\n\n");
    }
}

void escutarMusicas() {
    int opcaoGenero, i;

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
        scanf("%d", &opcaoGenero);

        switch (opcaoGenero) {
            case 1: tocarMusica(generos[0], rockMusicas, 3); break;
            case 2: tocarMusica(generos[1], popMusicas, 3); break;
            case 3: tocarMusica(generos[2], gauchaMusicas, 3); break;
            case 4: tocarMusica(generos[3], jazzMusicas, 3); break;
            case 0: printf("\nSaindo da cabine de escuta...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcaoGenero != 0);
}

void moduloCabines() {
    int opcaoCabine;

    do {
        printf("\n--- [MODULO 2: CABINES DE ESCUTA (Guilherme Monteiro de Andrade)] ---\n");
        printf("1. Cadastrar Nova Cabine\n");
        printf("2. Listar Cabines (Livres e Ocupadas)\n");
        printf("3. Buscar Cabine por Descricao\n");
        printf("4. Editar Cabine (Status / Tempo / Cliente)\n");
        printf("5. Remover Cabine (Dar Baixa)\n");
        printf("6. Ouvir Musicas na Cabine (por Genero)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCabine);

        switch (opcaoCabine) {
            case 1: cadastrarCabine(); break;
            case 2: listarCabines(); break;
            case 3: buscarCabinePorDescricao(); break;
            case 4: editarCabine(); break;
            case 5: removerCabine(); break;
            case 6: escutarMusicas(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcaoCabine != 0);
}

#endif
