// Arquivo: vendas.h | Autor: Bernardo Novaski Vidal de Almeida
#ifndef VENDAS_H
#define VENDAS_H

#include <stdio.h>
#include <string.h>
#include "discos.h"
#include "clientes.h"

#define MAX_VENDAS 50

struct Venda {
    int idVenda;
    int idClienteComprador;
    int idDiscoVendido;
    int quantidade;
    float valorTotal;
    char dataVenda[11];      // "DD/MM/AAAA"
    int ativo;               // 1 = Efetivada, 0 = Cancelada
};

struct Venda historicoVendas[MAX_VENDAS];
int totalVendas = 0;

// PERSISTENCIA: regrava o vetor inteiro em vendas.csv
void salvarVendasCSV() {
    FILE *arq = fopen("vendas.csv", "w");
    int i;

    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar vendas.csv!\n");
        return;
    }

    for (i = 0; i < totalVendas; i++) {
        fprintf(arq, "%d;%d;%d;%d;%.2f;%s;%d\n",
                historicoVendas[i].idVenda,
                historicoVendas[i].idClienteComprador,
                historicoVendas[i].idDiscoVendido,
                historicoVendas[i].quantidade,
                historicoVendas[i].valorTotal,
                historicoVendas[i].dataVenda,
                historicoVendas[i].ativo);
    }
    fclose(arq);
}

// PERSISTENCIA: le vendas.csv ao abrir o programa
void carregarVendasCSV() {
    FILE *arq = fopen("vendas.csv", "r");

    if (arq == NULL) {
        return;
    }

    totalVendas = 0;
    while (totalVendas < MAX_VENDAS &&
           fscanf(arq, "%d;%d;%d;%d;%f;%10[^;];%d\n",
                  &historicoVendas[totalVendas].idVenda,
                  &historicoVendas[totalVendas].idClienteComprador,
                  &historicoVendas[totalVendas].idDiscoVendido,
                  &historicoVendas[totalVendas].quantidade,
                  &historicoVendas[totalVendas].valorTotal,
                  historicoVendas[totalVendas].dataVenda,
                  &historicoVendas[totalVendas].ativo) == 7) {
        totalVendas++;
    }
    fclose(arq);
}

int buscarVendaPorId(int id) {
    int i;

    for (i = 0; i < totalVendas; i++) {
        if (historicoVendas[i].idVenda == id) {
            return i;
        }
    }
    return -1;
}

int proximoIdVenda() {
    int i, maior = 0;

    for (i = 0; i < totalVendas; i++) {
        if (historicoVendas[i].idVenda > maior) {
            maior = historicoVendas[i].idVenda;
        }
    }
    return maior + 1;
}

void exibirVenda(int i) {
    int posDisco = buscarDiscoPorId(historicoVendas[i].idDiscoVendido);
    int posCliente = buscarClientePorId(historicoVendas[i].idClienteComprador);

    printf("\nVenda %d | %s | ", historicoVendas[i].idVenda, historicoVendas[i].dataVenda);
    if (posCliente != -1) {
        printf("Cliente: %s | ", listaClientes[posCliente].nome);
    } else {
        printf("Cliente ID %d (removido) | ", historicoVendas[i].idClienteComprador);
    }
    if (posDisco != -1) {
        printf("Disco: %s\n", acervoDiscos[posDisco].titulo);
    } else {
        printf("Disco ID %d (removido)\n", historicoVendas[i].idDiscoVendido);
    }
    printf("Qtd: %d | Total: R$ %.2f | %s\n",
           historicoVendas[i].quantidade,
           historicoVendas[i].valorTotal,
           historicoVendas[i].ativo == 1 ? "EFETIVADA" : "CANCELADA");
}

// REGRA DE NEGOCIO: valida cliente e disco nos modulos dos colegas,
// calcula o valor, abate estoque e soma pontos de fidelidade
void registrarVenda() {
    int idCliente, idDisco, quantidade, posCliente, posDisco;
    int pos = totalVendas;

    if (totalVendas >= MAX_VENDAS) {
        printf("\nLimite de %d vendas atingido!\n", MAX_VENDAS);
        return;
    }

    printf("\nID do cliente comprador: ");
    scanf("%d", &idCliente);
    posCliente = buscarClientePorId(idCliente);
    if (posCliente == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("ID do disco vendido: ");
    scanf("%d", &idDisco);
    posDisco = buscarDiscoPorId(idDisco);
    if (posDisco == -1) {
        printf("\nDisco nao encontrado!\n");
        return;
    }

    do {
        printf("Quantidade: ");
        scanf("%d", &quantidade);
        if (quantidade <= 0) {
            printf("Quantidade invalida! Deve ser maior que zero.\n");
        }
    } while (quantidade <= 0);

    if (quantidade > acervoDiscos[posDisco].quantidadeEstoque) {
        printf("\nEstoque insuficiente! Disponivel: %d unidade(s).\n",
               acervoDiscos[posDisco].quantidadeEstoque);
        return;
    }

    historicoVendas[pos].idVenda = proximoIdVenda();
    historicoVendas[pos].idClienteComprador = idCliente;
    historicoVendas[pos].idDiscoVendido = idDisco;
    historicoVendas[pos].quantidade = quantidade;
    historicoVendas[pos].valorTotal = acervoDiscos[posDisco].preco * quantidade;

    printf("Data da venda (DD/MM/AAAA): ");
    scanf(" %10s", historicoVendas[pos].dataVenda);

    historicoVendas[pos].ativo = 1;

    // abate estoque e soma 1 ponto por disco comprado
    acervoDiscos[posDisco].quantidadeEstoque -= quantidade;
    listaClientes[posCliente].pontosFidelidade += quantidade;

    printf("\nVenda %d registrada! Total: R$ %.2f\n",
           historicoVendas[pos].idVenda, historicoVendas[pos].valorTotal);

    totalVendas++;

    // grava os tres arquivos que mudaram
    salvarVendasCSV();
    salvarDiscosCSV();
    salvarClientesCSV();
}

void listarHistoricoVendas() {
    int i;
    float faturamento = 0;

    printf("\n===== HISTORICO DE VENDAS (%d) =====\n", totalVendas);
    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    for (i = 0; i < totalVendas; i++) {
        exibirVenda(i);
        if (historicoVendas[i].ativo == 1) {
            faturamento += historicoVendas[i].valorTotal;
        }
    }
    printf("\nFaturamento total (vendas efetivadas): R$ %.2f\n", faturamento);
}

// Busca textual: procura o termo na data da venda (ex.: "/11/" ou "2026")
void buscarVendaPorData() {
    char termo[11];
    int i, encontrou = 0;

    printf("\nDigite parte da data (ex.: 11/2026): ");
    scanf(" %10s", termo);

    for (i = 0; i < totalVendas; i++) {
        if (strstr(historicoVendas[i].dataVenda, termo) != NULL) {
            exibirVenda(i);
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhuma venda encontrada com '%s'.\n", termo);
    }
}

// Edicao: corrige a data de uma venda e regrava o CSV
void editarVenda() {
    int id, pos;

    printf("\nDigite o ID da venda que deseja editar: ");
    scanf("%d", &id);

    pos = buscarVendaPorId(id);
    if (pos == -1) {
        printf("\nVenda nao encontrada!\n");
        return;
    }

    exibirVenda(pos);
    printf("\nNova data (DD/MM/AAAA): ");
    scanf(" %10s", historicoVendas[pos].dataVenda);

    salvarVendasCSV();
    printf("\nVenda atualizada na memoria e no arquivo CSV!\n");
}

// Cancelamento: devolve estoque, tira pontos, marca ativo = 0 e regrava os CSVs
void cancelarVenda() {
    int id, pos, posDisco, posCliente;

    printf("\nDigite o ID da venda que deseja cancelar: ");
    scanf("%d", &id);

    pos = buscarVendaPorId(id);
    if (pos == -1) {
        printf("\nVenda nao encontrada!\n");
        return;
    }
    if (historicoVendas[pos].ativo == 0) {
        printf("\nEssa venda ja foi cancelada!\n");
        return;
    }

    historicoVendas[pos].ativo = 0;

    posDisco = buscarDiscoPorId(historicoVendas[pos].idDiscoVendido);
    if (posDisco != -1) {
        acervoDiscos[posDisco].quantidadeEstoque += historicoVendas[pos].quantidade;
    }

    posCliente = buscarClientePorId(historicoVendas[pos].idClienteComprador);
    if (posCliente != -1) {
        listaClientes[posCliente].pontosFidelidade -= historicoVendas[pos].quantidade;
        if (listaClientes[posCliente].pontosFidelidade < 0) {
            listaClientes[posCliente].pontosFidelidade = 0;
        }
    }

    salvarVendasCSV();
    salvarDiscosCSV();
    salvarClientesCSV();
    printf("\nVenda %d cancelada! Estoque e pontos foram ajustados.\n", id);
}

// RELATORIO: disco mais vendido
void relatorioDiscoMaisVendido() {
    int i, j, soma, maior = 0, posMaior = -1;

    for (i = 0; i < totalDiscos; i++) {
        soma = 0;
        for (j = 0; j < totalVendas; j++) {
            if (historicoVendas[j].ativo == 1 &&
                historicoVendas[j].idDiscoVendido == acervoDiscos[i].idDisco) {
                soma += historicoVendas[j].quantidade;
            }
        }
        if (soma > maior) {
            maior = soma;
            posMaior = i;
        }
    }

    printf("\n===== RELATORIO: DISCO MAIS VENDIDO =====\n");
    if (posMaior == -1) {
        printf("Nenhuma venda efetivada ate o momento.\n");
    } else {
        printf("Titulo: %s\nArtista: %s\nUnidades vendidas: %d\n",
               acervoDiscos[posMaior].titulo, acervoDiscos[posMaior].artista, maior);
    }
}

// RELATORIO: ranking de clientes por numero de compras.
// Usa MATRIZ 2D: cada linha = um cliente, coluna 0 = idCliente, coluna 1 = compras.
// A matriz e ordenada do maior para o menor com BUBBLE SORT.
void relatorioRankingClientes() {
    int ranking[MAX_CLIENTES][2];
    int i, j, k, aux0, aux1, posCliente;

    for (i = 0; i < totalClientes; i++) {
        ranking[i][0] = listaClientes[i].idCliente;
        ranking[i][1] = 0;
        for (j = 0; j < totalVendas; j++) {
            if (historicoVendas[j].ativo == 1 &&
                historicoVendas[j].idClienteComprador == listaClientes[i].idCliente) {
                ranking[i][1]++;
            }
        }
    }

    // Bubble Sort decrescente pela coluna 1 (numero de compras)
    for (i = 0; i < totalClientes - 1; i++) {
        for (j = 0; j < totalClientes - 1 - i; j++) {
            if (ranking[j][1] < ranking[j + 1][1]) {
                aux0 = ranking[j][0];
                aux1 = ranking[j][1];
                ranking[j][0] = ranking[j + 1][0];
                ranking[j][1] = ranking[j + 1][1];
                ranking[j + 1][0] = aux0;
                ranking[j + 1][1] = aux1;
            }
        }
    }

    printf("\n===== RELATORIO: RANKING DE CLIENTES (compras efetivadas) =====\n");
    for (k = 0; k < totalClientes; k++) {
        posCliente = buscarClientePorId(ranking[k][0]);
        printf("%2d. %-25s | %d compra(s)\n",
               k + 1, listaClientes[posCliente].nome, ranking[k][1]);
    }
}

// RELATORIO: compras de um cliente especifico
void relatorioComprasPorCliente() {
    int id, pos, i, encontrou = 0;
    float totalGasto = 0;

    printf("\nDigite o ID do cliente: ");
    scanf("%d", &id);

    pos = buscarClientePorId(id);
    if (pos == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    printf("\n===== COMPRAS DE %s =====\n", listaClientes[pos].nome);
    for (i = 0; i < totalVendas; i++) {
        if (historicoVendas[i].ativo == 1 && historicoVendas[i].idClienteComprador == id) {
            exibirVenda(i);
            totalGasto += historicoVendas[i].valorTotal;
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
        printf("1. Registrar Nova Venda (Cruza Cliente + Disco)\n");
        printf("2. Listar Historico de Vendas\n");
        printf("3. Buscar Venda por Data\n");
        printf("4. Editar Data de uma Venda\n");
        printf("5. Cancelar / Estornar Venda\n");
        printf("6. [RELATORIO] Disco Mais Vendido\n");
        printf("7. [RELATORIO] Ranking de Clientes (Matriz 2D + Bubble Sort)\n");
        printf("8. [RELATORIO] Compras de um Cliente Especifico\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoVenda);

        switch (opcaoVenda) {
            case 1: registrarVenda(); break;
            case 2: listarHistoricoVendas(); break;
            case 3: buscarVendaPorData(); break;
            case 4: editarVenda(); break;
            case 5: cancelarVenda(); break;
            case 6: relatorioDiscoMaisVendido(); break;
            case 7: relatorioRankingClientes(); break;
            case 8: relatorioComprasPorCliente(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcaoVenda != 0);
}

#endif
