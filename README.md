# Biblioteca de jogos com tabela hash

Nesta versao, os jogos comprados pelo usuario sao guardados em uma tabela hash.
A chave de cada registro e o codigo inteiro do jogo.

## Estrutura utilizada

- Funcao hash: `codigo % TAMANHO_HASH`.
- Tratamento de colisoes: sondagem linear.
- Exclusao: a posicao recebe o estado `REMOVIDA`, em vez de voltar diretamente para `VAZIA`.
- Limite da biblioteca: 100 jogos.
- Tamanho interno da tabela: 211 posicoes, um numero primo maior que o limite de jogos.

## Por que existe o estado REMOVIDA?

Quando dois codigos caem na mesma posicao, o segundo e colocado em uma posicao seguinte.
Se o primeiro for removido e sua posicao virar `VAZIA`, a busca pelo segundo poderia parar antes de encontra-lo.
A marcacao `REMOVIDA` informa que a busca deve continuar.

## Arquivos alterados

- `Biblioteca.h`: declaracao da tabela hash e de seus estados.
- `Biblioteca.cpp`: insercao, busca e remocao usando hash.
- `Loja.cpp`: a compra so desconta o saldo depois que a insercao na biblioteca funciona.
- `main.cpp`: inclui uma opcao para buscar diretamente pelo codigo do jogo.

## Compilacao

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Biblioteca.cpp Loja.cpp -o biblioteca
```

## Execucao

```bash
./biblioteca
```

## Compilacao no macOS com VS Code

Nao use a tarefa `clang arquivo de build ativo`, pois ela compila somente o arquivo que esta aberto.
Este projeto possui implementacoes separadas em `Biblioteca.cpp` e `Loja.cpp`, entao os tres arquivos `.cpp` precisam participar da compilacao.

Comando correto no terminal:

```bash
clang++ -std=gnu++14 -Wall -Wextra -pedantic -g main.cpp Biblioteca.cpp Loja.cpp -o main
./main
```

O projeto tambem inclui `.vscode/tasks.json`. Abra a pasta inteira no VS Code e pressione `Cmd + Shift + B` para executar a tarefa `Compilar projeto C++ completo`.

Outra opcao e usar o Makefile:

```bash
make
./main
```
