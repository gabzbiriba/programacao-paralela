/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
6. Funções e Passagem por Referência (007.cpp)
a) Implemente uma função int soma(int a, int b) e use-a no main.

b) Crie uma função que incremente em 1 um número passado por referência.

c) Faça sobrecarga de função soma para receber 3 inteiros.
--------------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

int soma(int a, int b) {
    return a + b;
}

void incremente(int& num) {
    num += 1;
}

int soma(int a, int b, int c) {
    return a + b + c;
}

int main() {

    cout << "Soma 2 números (2 + 3): " << soma(2, 3) << endl;
    cout << "Soma 3 números (1 + 2 + 3): " << soma(1, 2, 3) << endl;

    int valor = 5;
    incremente(valor);
    cout << "Valor após incremento: " << valor << endl;

    system("pause");
    return 0;
}