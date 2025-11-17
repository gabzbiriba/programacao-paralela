/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
5. Laços (for, while, do-while) (006.cpp)
a) Escreva um programa que exiba todos os números ímpares de 1 a 20.

b) Implemente um contador regressivo de 10 até 0 usando while.

c) Simule um menu que só termina quando o usuário digitar 0, usando do-while.
--------------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

int main() {
    cout << "Números ímpares de 1 a 20: ";
    for (int i = 1; i <= 20; i++) {
        if (i % 2 != 0) cout << i << ' ';
    }
    cout << endl;

    cout << "Contador regressivo: ";
    int contador = 10;
    while (contador >= 0) {
        cout << contador-- << ' ';
    }
    cout << endl;

    int opcaoMenu;
    do {
        cout << "\nMenu:\n1 - Opção A\n2 - Opção B\n0 - Sair\nEscolha a alternativa: ";
        cin >> opcaoMenu;
    } while (opcaoMenu != 0);

    system("pause");
    return 0;
}