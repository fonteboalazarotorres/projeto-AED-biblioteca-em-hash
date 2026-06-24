#ifndef LOJA_H
#define LOJA_H

#include "Biblioteca.h"
#include <string>

class Loja {
private:
    static const int MAXTAMANHO = 100;
    jogo jogosdisponiveis[MAXTAMANHO + 1];
    int s;

public:
    Loja();

    bool fullL() const;
    bool emptyL() const;

    bool deploy(const jogo& novoJogo);
    bool comprar(TypeKey codigo, Biblioteca& biblioteca);
    bool reembolsar(const jogo& jogoReembolso, Biblioteca& biblioteca);

    void vercatalogo() const;

    int searchbyname(const std::string& titulo) const;
    int searchbin(TypeKey codigo) const;
    bool thiscodeexist(TypeKey codigo) const;
};

#endif
