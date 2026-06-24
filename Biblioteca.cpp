#include "Biblioteca.h"
#include <iostream>

using namespace std;

Biblioteca::Biblioteca() : wallet(0), quantidade(0) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela[i].estado = VAZIA;
    }
}

int Biblioteca::funcaoHash(TypeKey codigo) const {
    int resultado = codigo % TAMANHO_HASH;

    // Garante uma posicao valida mesmo se algum codigo negativo for informado.
    if (resultado < 0) {
        resultado += TAMANHO_HASH;
    }

    return resultado;
}

int Biblioteca::balance() const {
    return wallet;
}

void Biblioteca::addfunds(int valor) {
    if (valor < 0) {
        valor = -valor;
    }

    wallet += valor;
}

void Biblioteca::spendfunds(int valor) {
    wallet -= valor;
}

bool Biblioteca::full() const {
    return quantidade == MAX_JOGOS;
}

bool Biblioteca::empty() const {
    return quantidade == 0;
}

int Biblioteca::size() const {
    return quantidade;
}

int Biblioteca::searchHash(TypeKey codigo) const {
    int posicaoInicial = funcaoHash(codigo);

    for (int tentativa = 0; tentativa < TAMANHO_HASH; tentativa++) {
        int posicaoAtual = (posicaoInicial + tentativa) % TAMANHO_HASH;

        if (tabela[posicaoAtual].estado == VAZIA) {
            return -1;
        }

        if (tabela[posicaoAtual].estado == OCUPADA &&
            tabela[posicaoAtual].registro.codigo == codigo) {
            return posicaoAtual;
        }
    }

    return -1;
}

bool Biblioteca::insert(const jogo& novoJogo) {
    if (full()) {
        cout << "A biblioteca esta cheia!" << endl;
        return false;
    }

    if (searchHash(novoJogo.codigo) != -1) {
        cout << "Ja existe um jogo com o codigo " << novoJogo.codigo
             << " na biblioteca." << endl;
        return false;
    }

    int posicaoInicial = funcaoHash(novoJogo.codigo);

    // Sondagem linear: caso a posicao esteja ocupada, tenta a seguinte.
    for (int tentativa = 0; tentativa < TAMANHO_HASH; tentativa++) {
        int posicaoAtual = (posicaoInicial + tentativa) % TAMANHO_HASH;

        if (tabela[posicaoAtual].estado != OCUPADA) {
            tabela[posicaoAtual].registro = novoJogo;
            tabela[posicaoAtual].estado = OCUPADA;
            quantidade++;
            return true;
        }
    }

    return false;
}

bool Biblioteca::remove(TypeKey codigo) {
    int posicao = searchHash(codigo);

    if (posicao == -1) {
        return false;
    }

    // Nao marcamos como VAZIA, pois isso poderia quebrar uma cadeia de colisoes.
    tabela[posicao].estado = REMOVIDA;
    quantidade--;
    return true;
}

bool Biblioteca::searchByCode(TypeKey codigo, jogo& encontrado) const {
    int posicao = searchHash(codigo);

    if (posicao == -1) {
        return false;
    }

    encontrado = tabela[posicao].registro;
    return true;
}

int Biblioteca::posicaoPeloNumeroDaLista(int numero) const {
    if (numero < 1 || numero > quantidade) {
        return -1;
    }

    int contador = 0;

    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela[i].estado == OCUPADA) {
            contador++;

            if (contador == numero) {
                return i;
            }
        }
    }

    return -1;
}

bool Biblioteca::searchbyindice(int indice, jogo& encontrado) const {
    int posicao = posicaoPeloNumeroDaLista(indice);

    if (posicao == -1) {
        return false;
    }

    encontrado = tabela[posicao].registro;
    return true;
}

void Biblioteca::displaygame(int numeroDaLista) const {
    int posicao = posicaoPeloNumeroDaLista(numeroDaLista);

    if (posicao == -1) {
        cout << "Insira um numero de jogo valido!" << endl;
        return;
    }

    const jogo& jogoEncontrado = tabela[posicao].registro;

    cout << "Jogo: " << jogoEncontrado.titulo << endl;
    cout << "Preco pago: " << jogoEncontrado.preco << " BRL" << endl;
    cout << "Genero: " << jogoEncontrado.genero << endl;
    cout << "Codigo do jogo: " << jogoEncontrado.codigo << endl;
}

void Biblioteca::displaygamebycode(TypeKey codigo) const {
    jogo encontrado;

    if (!searchByCode(codigo, encontrado)) {
        cout << "Jogo com codigo " << codigo << " nao encontrado!" << endl;
        return;
    }

    cout << "Jogo: " << encontrado.titulo << endl;
    cout << "Preco pago: " << encontrado.preco << " BRL" << endl;
    cout << "Genero: " << encontrado.genero << endl;
    cout << "Codigo do jogo: " << encontrado.codigo << endl;
}

void Biblioteca::displaybib() const {
    if (empty()) {
        cout << "Sua biblioteca esta vazia!" << endl;
        return;
    }

    int numeroDaLista = 1;

    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela[i].estado == OCUPADA) {
            cout << numeroDaLista << ". " << tabela[i].registro.titulo
                 << " (codigo " << tabela[i].registro.codigo << ")" << endl;
            numeroDaLista++;
        }
    }
}
