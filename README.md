# Vinyl Hub - Sistema de Gestão para Loja de Discos de Vinil

Sistema de gestão de uma loja de discos de vinil retrô (tema anos 80), desenvolvido em **linguagem C** e executado no **terminal**. Cada integrante da equipe é responsável por um módulo completo, com sua própria struct, seu submenu e as operações de cadastrar, listar/buscar, editar e remover.

Projeto da disciplina **Algoritmos e Pensamento Computacional**, curso de Análise e Desenvolvimento de Sistemas, Universidade Positivo.

> Vídeo de apresentação: [cole aqui o link do YouTube]

---

## Funcionalidades

### Módulo 1: Acervo de Discos
- Cadastro de discos com título, artista, preço e estoque
- Listagem de todos os discos ou busca por ID
- Edição de preço e estoque
- Remoção do acervo

### Módulo 2: Cabines de Escuta
- Cadastro de cabines (número, descrição e valor por hora)
- Listagem de todas, só livres, só ocupadas ou busca por ID
- Edição de status, cliente e tempo de uso
- Baixa de cabine
- Escuta de músicas por gênero (Rock, Pop, Gaúcha e Jazz)

### Módulo 3: Clientes do Clube do Vinil
- Cadastro de clientes com nome e telefone
- Listagem e busca por ID
- Edição de nome, telefone ou pontos de fidelidade
- Remoção de clientes

### Módulo 4: Vendas e Relatórios
- Registro de vendas, cruzando cliente e disco, com validação de estoque
- Histórico de vendas com faturamento total
- Cancelamento de venda, que devolve o disco ao estoque e retira os pontos
- Relatórios analíticos:
  - disco mais vendido
  - cliente VIP (maior número de compras)
  - compras de um cliente específico

### Geral
- Menu principal em loop que direciona para os quatro módulos
- Persistência: os dados são salvos em arquivo

---

## Conceitos utilizados

- `struct` e vetores globais de structs (`#define` para o tamanho máximo)
- Matrizes de texto (músicas por gênero)
- Funções `void` e funções com retorno (busca por ID retorna a posição ou `-1`)
- Menus com `do-while` e `switch-case`
- Laços `for` e `while`, inclusive aninhados nos relatórios
- Remoção lógica: o registro não é apagado, apenas marcado com `ativo = 0`
- Leitura e escrita de arquivos

---

## Como compilar e executar

### Com GCC

```bash
gcc main.c -o vinylhub
./vinylhub
```

No Windows, execute `vinylhub.exe`.

### Com Dev-C++

1. Abra o arquivo `main.c`
2. Compile e execute com `F11`

---

## Como usar

1. No menu principal, escolha um módulo digitando o número correspondente.
2. Dentro do módulo, escolha a ação desejada. O `0` volta ao menu anterior.
3. Para registrar uma venda, cadastre antes ao menos **um cliente** e **um disco**.

Dicas de digitação:
- digite um valor por vez e aperte **Enter** depois de cada um;
- use **ponto** nos preços (`80.50`);
- nos campos de texto, escreva sem espaços ou use `_` no lugar (`Michael_Jackson`).

---

## Equipe

| Integrante | Módulo |
|---|---|
| Nathan Souza Gusso | Acervo de Discos |
| Guilherme Monteiro de Andrade | Cabines de Escuta |
| José Gustavo da Silva Bertoche | Clientes do Clube do Vinil |
| Bernardo Novaski Vidal de Almeida | Vendas e Relatórios |

Cada função do código está identificada com o autor responsável (`// Autor: Nome`).
