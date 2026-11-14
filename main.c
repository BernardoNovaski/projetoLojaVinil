// Arquivo: main.c | Projeto Vinyl Hub
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "discos.h"
#include "clientes.h"
#include "cabines.h"
#include "vendas.h"

// Limpa o console a cada troca de menu (cls no Windows, clear no Linux/Mac)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("   VINYL HUB - SISTEMA DE GESTAO RETRO (1985)      \n");
    printf("   Discos de Vinil | Cabines de Escuta | Caixa        \n");
    printf("======================================================\n");
}

int main() {
    int opcaoPrincipal;

    setlocale(LC_ALL, "Portuguese");

    // carrega os 4 arquivos CSV para os vetores na memoria
    carregarDiscosCSV();
    carregarCabinesCSV();
    carregarClientesCSV();
    carregarVendasCSV();

    do {
        limparTela();
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
            case 1: limparTela(); moduloDiscos(); break;
            case 2: limparTela(); moduloCabines(); break;
            case 3: limparTela(); moduloClientes(); break;
            case 4: limparTela(); moduloVendasRelatorios(); break;
            case 0: printf("\nEncerrando o sistema Vinyl Hub... Ate logo!\n"); break;
            default: printf("\n[ALERTA] Opcao invalida! Digite um numero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
