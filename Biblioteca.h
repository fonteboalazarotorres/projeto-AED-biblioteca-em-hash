#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <string>

typedef int TypeKey;

struct jogo {
    std::string titulo;
    int preco;
    std::string genero;
    TypeKey codigo;
};

class Biblioteca {
private:
    // Cada posicao da tabela pode estar vazia, ocupada ou removida.
    // A marcacao REMOVIDA e importante para a busca continuar depois de uma exclusao.
    enum EstadoPosicao {
        VAZIA,
        OCUPADA,
        REMOVIDA
    };

    struct PosicaoHash {
        jogo registro;
        EstadoPosicao estado;
    };

    static const int MAX_JOGOS = 100;
    static const int TAMANHO_HASH = 211;

    int wallet;
    int quantidade;
    PosicaoHash tabela[TAMANHO_HASH];

    int funcaoHash(TypeKey codigo) const;
    int posicaoPeloNumeroDaLista(int numero) const;

public:
    Biblioteca();

    int balance() const;
    void addfunds(int valor);
    void spendfunds(int valor);

    bool full() const;
    bool empty() const;
    int size() const;

    bool insert(const jogo& novoJogo);
    bool remove(TypeKey codigo);

    // Retorna a posicao interna da tabela ou -1 quando nao encontra.
    int searchHash(TypeKey codigo) const;
    bool searchByCode(TypeKey codigo, jogo& encontrado) const;
    bool searchbyindice(int indice, jogo& encontrado) const;

    void displaygame(int numeroDaLista) const;
    void displaygamebycode(TypeKey codigo) const;
    void displaybib() const;
};

#endif
