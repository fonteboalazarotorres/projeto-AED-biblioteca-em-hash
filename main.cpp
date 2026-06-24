#include "Biblioteca.h"
#include "Loja.h"
#include <iostream>
#include <limits>

using namespace std;

void limparEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Biblioteca biblioteca;
    Loja loja;
    int opcaoPrincipal;

    while (true) {
        cout << "\n===== BIBLIOTECA DE JOGOS =====" << endl;
        cout << "1. Ver minha biblioteca" << endl;
        cout << "2. Abrir a loja" << endl;
        cout << "3. Sair" << endl;
        cout << "Escolha: ";
        cin >> opcaoPrincipal;

        if (opcaoPrincipal == 1) {
            bool naBiblioteca = true;

            while (naBiblioteca) {
                cout << "\n===== SUA BIBLIOTECA =====" << endl;
                biblioteca.displaybib();

                cout << "\n1. Mostrar informacoes pelo numero da lista" << endl;
                cout << "2. Buscar jogo pelo codigo (hash)" << endl;
                cout << "3. Reembolsar um jogo" << endl;
                cout << "4. Voltar" << endl;
                cout << "Escolha: ";

                int opcaoBiblioteca;
                cin >> opcaoBiblioteca;

                switch (opcaoBiblioteca) {
                case 1: {
                    int numero;
                    cout << "Numero do jogo: ";
                    cin >> numero;
                    biblioteca.displaygame(numero);
                    break;
                }

                case 2: {
                    TypeKey codigo;
                    cout << "Codigo do jogo: ";
                    cin >> codigo;
                    biblioteca.displaygamebycode(codigo);
                    break;
                }

                case 3: {
                    if (biblioteca.empty()) {
                        cout << "Nao ha jogos para reembolsar." << endl;
                        break;
                    }

                    int numero;
                    cout << "Numero do jogo que sera reembolsado: ";
                    cin >> numero;

                    jogo jogoEscolhido;

                    if (!biblioteca.searchbyindice(numero, jogoEscolhido)) {
                        cout << "Numero de jogo invalido." << endl;
                        break;
                    }

                    if (loja.reembolsar(jogoEscolhido, biblioteca)) {
                        cout << "Jogo reembolsado com sucesso!" << endl;
                    }
                    break;
                }

                case 4:
                    naBiblioteca = false;
                    break;

                default:
                    cout << "Insira uma opcao valida." << endl;
                }
            }
        }
        else if (opcaoPrincipal == 2) {
            bool naLoja = true;

            while (naLoja) {
                cout << "\n===== LOJA =====" << endl;
                loja.vercatalogo();
                cout << "Seu saldo: " << biblioteca.balance() << " BRL" << endl;

                cout << "\n1. Comprar um jogo" << endl;
                cout << "2. Adicionar um jogo novo a loja" << endl;
                cout << "3. Adicionar fundos" << endl;
                cout << "4. Voltar" << endl;
                cout << "Escolha: ";

                int opcaoLoja;
                cin >> opcaoLoja;

                switch (opcaoLoja) {
                case 1: {
                    limparEntrada();
                    string titulo;
                    cout << "Nome exato do jogo: ";
                    getline(cin, titulo);

                    int codigo = loja.searchbyname(titulo);

                    if (codigo == -1) {
                        cout << "Jogo nao encontrado na loja." << endl;
                    }
                    else {
                        loja.comprar(codigo, biblioteca);
                    }
                    break;
                }

                case 2: {
                    jogo novoJogo;

                    limparEntrada();
                    cout << "Titulo: ";
                    getline(cin, novoJogo.titulo);

                    cout << "Preco: ";
                    cin >> novoJogo.preco;

                    limparEntrada();
                    cout << "Genero: ";
                    getline(cin, novoJogo.genero);

                    cout << "Codigo de 6 digitos: ";
                    cin >> novoJogo.codigo;

                    if (novoJogo.codigo < 100000 || novoJogo.codigo > 999999) {
                        cout << "O codigo precisa possuir 6 digitos." << endl;
                        break;
                    }

                    jogo jogoComMesmoCodigo;
                    bool codigoNaBiblioteca =
                        biblioteca.searchByCode(novoJogo.codigo, jogoComMesmoCodigo);

                    if (loja.thiscodeexist(novoJogo.codigo) || codigoNaBiblioteca) {
                        cout << "Esse codigo ja esta sendo utilizado." << endl;
                        break;
                    }

                    if (loja.deploy(novoJogo)) {
                        cout << "Jogo adicionado a loja com sucesso!" << endl;
                    }
                    break;
                }

                case 3: {
                    int valor;
                    cout << "Valor que sera adicionado: ";
                    cin >> valor;
                    biblioteca.addfunds(valor);
                    cout << "Novo saldo: " << biblioteca.balance() << " BRL" << endl;
                    break;
                }

                case 4:
                    naLoja = false;
                    break;

                default:
                    cout << "Insira uma opcao valida." << endl;
                }
            }
        }
        else if (opcaoPrincipal == 3) {
            cout << "Programa encerrado." << endl;
            return 0;
        }
        else {
            cout << "Insira uma opcao valida." << endl;
        }
    }
}
