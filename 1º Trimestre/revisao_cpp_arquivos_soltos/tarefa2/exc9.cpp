/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
9. Struct e Classe (010.cpp)
a) Crie uma struct Aluno com nome e idade. Leia os dados do teclado e exiba-os.

b) Crie uma classe ContaBancaria com: depositar(double valor), sacar(double valor),
imprimir(). Teste-a criando uma conta e fazendo operações.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
using namespace std;

struct Aluno {
    string nome;
    int idade{};
};

class ContaBancaria {
private:
    string titular;
    double saldo{0.0};
public:
    ContaBancaria(const string& t, double s = 0.0) : titular(t), saldo(s) {}

    void depositar(double valor) { saldo += valor; }

    bool sacar(double valor) {
        if (valor <= saldo) { saldo -= valor; return true; }
        return false;
    }

    void imprimir() const {
        cout << "Titular: " << titular << ", Saldo: R$ " << saldo << endl;
    }
};

int main() {

    Aluno p { "Cleitin", 80 };
    cout << p.nome << ", " << p.idade << " anos" << endl;

    ContaBancaria c{ "Anna", 200.0 };
    c.depositar(100);
    if(!c.sacar(250)) cout << "Saldo insuficiente" << endl;
    c.imprimir();

    system("pause");
    return 0;
}