# projetoLojaVinil
# Vinyl Palace: Sistema de Gestão da Loja de Discos de Vinil Retrô (1985)

Projeto da disciplina **Algoritmos e Pensamento Computacional**, referente ao **Checkpoint 1 (Gateway 1)** do Projeto P2.

Sistema em modo console, escrito em linguagem C, para gerenciar uma loja de discos de vinil com cabines de escuta e caixa de vendas. Nesta etapa, a arquitetura completa (structs, menus e submenus) está pronta e as rotinas de cada opção estão marcadas como `[Em construcao]`, aguardando a lógica das próximas etapas.

## Equipe e responsabilidades

| Módulo | Perspectiva | Responsável |
|--------|-------------|-------------|
| 1 | Acervo de Discos de Vinil | Nathan Souza Gusso |
| 2 | Cabines de Escuta | Guilherme Monteiro de Andrade |
| 3 | Clientes do Clube do Vinil | José Gustavo da Silva Bertoche |
| 4 | Vendas no Caixa e Relatórios | Bernardo Novaski Vidal de Almeida |

## Modelagem de dados

Cada integrante é dono de uma `struct` declarada no escopo global, com seu vetor de armazenamento (50 posições) e um contador.

| Struct | Campos | Vetor global | Contador |
|--------|--------|--------------|----------|
| `Disco` | `idDisco`, `titulo[50]`, `artista[50]`, `preco`, `quantidadeEstoque` | `acervoDiscos[50]` | `totalDiscos` |
| `Cabine` | `idCabine`, `numeroCabine`, `statusOcupacao` (1 = ocupada, 0 = livre), `tempoUsoMinutos`, `idClienteUsando` | `listaCabines[50]` | `totalCabines` |
| `Cliente` | `idCliente`, `nome[50]`, `telefone[20]`, `pontosFidelidade`, `ativo` (1 = ativo, 0 = removido) | `listaClientes[50]` | `totalClientes` |
| `Venda` | `idVenda`, `idClienteComprador`, `idDiscoVendido`, `valorTotal` | `historicoVendas[50]` | `totalVendas` |

## Estrutura do menu

```
Menu Principal (main)
+-- 1. Módulo de Discos        -> Cadastrar | Listar/Buscar | Editar | Remover
+-- 2. Módulo de Cabines       -> Cadastrar | Listar/Buscar | Editar | Remover
+-- 3. Módulo de Clientes      -> Cadastrar | Listar/Buscar | Editar | Remover
+-- 4. Módulo de Vendas e Relatórios
¦       +-- Registrar venda (cruza ID do Cliente e ID do Disco)
¦       +-- Listar histórico de vendas
¦       +-- Cancelar / estornar venda
¦       +-- Relatórios: disco mais vendido, cliente VIP, compras por cliente
+-- 0. Encerrar o sistema
```

Todos os menus funcionam em laço `do-while` com `switch-case`, e a opção `0` de cada submenu volta ao menu principal sem fechar o programa.

## Organização do código

O arquivo único `main.c` está dividido em três partes:

1. **PARTE 1: Modelagem de dados (escopo global):** structs, vetores e contadores.
2. **PARTE 2: Funções de interface e módulos:** `exibirCabecalho()`, `moduloDiscos()`, `moduloCabines()`, `moduloClientes()` e `moduloVendasRelatorios()`, cada uma identificada com `// Autor: Nome`.
3. **PARTE 3: Função principal (`main`):** menu principal que direciona para os módulos.

Bibliotecas utilizadas: `stdio.h`, `stdlib.h`, `string.h` e `locale.h`. O projeto usa apenas o que foi ensinado em aula: `struct` padrão, vetores globais de tamanho fixo, `if/else`, `switch-case`, `for`, `while`, `do-while` e funções `void`.

## Como compilar e executar

Com o GCC instalado:

```bash
gcc main.c -o main
./main
```

No PowerShell (Windows), execute com `.\main.exe`. Também é possível abrir o `main.c` no Dev-C++ ou no VS Code e compilar por lá.

Se os acentos aparecerem errados no terminal do Windows, execute `chcp 65001` antes do programa.

## Próximas etapas

- Implementar o CRUD completo de cada módulo.
- Implementar o registro de vendas e os relatórios analíticos.
- Salvar e carregar os vetores em arquivos `.txt` ou `.csv` com `FILE *`.

## Fluxo de trabalho da equipe

- Cada integrante altera apenas a função do seu módulo, para evitar conflitos no `main.c`.
- Fazer commits frequentes, com mensagens claras (por exemplo: `Adiciona cadastro de disco`).
- Cada integrante deve saber explicar todas as linhas do seu módulo.
