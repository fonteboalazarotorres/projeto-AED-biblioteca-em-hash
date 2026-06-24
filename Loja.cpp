#include "Loja.h"
#include <iostream>

using namespace std;

Loja::Loja() : s(10) {
    jogosdisponiveis[1] = {"The Witcher 3", 70, "RPG, MUNDO ABERTO", 101285};
    jogosdisponiveis[2] = {"GTA V", 100, "ACAO, MUNDO ABERTO", 182346};
    jogosdisponiveis[3] = {"Counter-Strike", 60, "FPS", 193748};
    jogosdisponiveis[4] = {"Resident Evil 4", 150, "TERROR", 284716};
    jogosdisponiveis[5] = {"Minecraft", 80, "SANDBOX", 317865};
    jogosdisponiveis[6] = {"The Last of Us I", 180, "ACAO/TERROR", 473829};
    jogosdisponiveis[7] = {"God of War", 160, "ACAO", 539104};
    jogosdisponiveis[8] = {"Mortal Kombat I", 190, "LUTA", 625437};
    jogosdisponiveis[9] = {"Elden Ring", 220, "RPG", 748291};
    jogosdisponiveis[10] = {"Silent Hill 2", 200, "TERROR", 912397};
}

bool Loja::fullL() const {
    return s == MAXTAMANHO;
}

bool Loja::emptyL() const {
    return s == 0;
}

bool Loja::deploy(const jogo& novoJogo) {
    if (fullL()) {
        cout << "A loja esta cheia!" << endl;
        return false;
    }

    if (thiscodeexist(novoJogo.codigo)) {
        cout << "Esse codigo ja existe na loja!" << endl;
        return false;
    }

    int posicao = 1;

    while (posicao <= s && novoJogo.codigo > jogosdisponiveis[posicao].codigo) {
        posicao++;
    }

    for (int i = s + 1; i > posicao; i--) {
        jogosdisponiveis[i] = jogosdisponiveis[i - 1];
    }

    jogosdisponiveis[posicao] = novoJogo;
    s++;
    return true;
}

bool Loja::comprar(TypeKey codigo, Biblioteca& biblioteca) {
    int posicao = searchbin(codigo);

    if (posicao == -1) {
        cout << "Jogo com codigo " << codigo << " nao encontrado!" << endl;
        return false;
    }

    const jogo jogoComprado = jogosdisponiveis[posicao];

    if (biblioteca.balance() < jogoComprado.preco) {
        cout << "Saldo insuficiente. Seu saldo atual e de "
             << biblioteca.balance() << " BRL." << endl;
        return false;
    }

    // O dinheiro e descontado e o jogo sai da loja somente se a hash aceitar a insercao.
    if (!biblioteca.insert(jogoComprado)) {
        return false;
    }

    biblioteca.spendfunds(jogoComprado.preco);

    for (int i = posicao; i < s; i++) {
        jogosdisponiveis[i] = jogosdisponiveis[i + 1];
    }

    s--;
    cout << "Compra realizada com sucesso!" << endl;
    return true;
}

bool Loja::reembolsar(const jogo& jogoReembolso, Biblioteca& biblioteca) {
    if (fullL()) {
        cout << "Nao foi possivel reembolsar: a loja esta cheia." << endl;
        return false;
    }

    if (!biblioteca.remove(jogoReembolso.codigo)) {
        cout << "O jogo nao foi encontrado na biblioteca." << endl;
        return false;
    }

    // Como o jogo saiu originalmente da loja, seu codigo nao deve estar no catalogo.
    // Mesmo assim, se houver uma inconsistencia, desfazemos a remocao da biblioteca.
    if (!deploy(jogoReembolso)) {
        biblioteca.insert(jogoReembolso);
        return false;
    }

    biblioteca.addfunds(jogoReembolso.preco);
    return true;
}

void Loja::vercatalogo() const {
    if (emptyL()) {
        cout << "A loja esta vazia!" << endl;
        return;
    }

    for (int i = 1; i <= s; i++) {
        cout << "Jogo: " << jogosdisponiveis[i].titulo << endl;
        cout << "Preco: " << jogosdisponiveis[i].preco << " BRL" << endl;
        cout << "Genero: " << jogosdisponiveis[i].genero << endl;
        cout << "Codigo: " << jogosdisponiveis[i].codigo << endl;
        cout << endl;
    }
}

int Loja::searchbyname(const string& titulo) const {
    for (int i = 1; i <= s; i++) {
        if (jogosdisponiveis[i].titulo == titulo) {
            return jogosdisponiveis[i].codigo;
        }
    }

    return -1;
}

int Loja::searchbin(TypeKey codigo) const {
    int inicio = 1;
    int fim = s;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (jogosdisponiveis[meio].codigo == codigo) {
            return meio;
        }

        if (codigo > jogosdisponiveis[meio].codigo) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    return -1;
}

bool Loja::thiscodeexist(TypeKey codigo) const {
    return searchbin(codigo) != -1;
}
