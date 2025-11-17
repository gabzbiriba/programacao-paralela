/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
3. Operadores e Casting (004.cpp)
a) Leia dois números inteiros do usuário. Exiba: soma, subtração, multiplicação, divisão inteira e divisão real (com casting).

b) Use o operador ternário para mostrar qual dos dois números é o maior.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

int main() {
    int numero1, numero2;
    cout << "Insira o primeiro número: ";
    cin >> numero1;
    cout << "Insira o segundo número: ";
    cin >> numero2;

    cout << "Soma: " << numero1 + numero2 << endl;
    cout << "Subtração: " << numero1 - numero2 << endl;
    cout << "Multiplicação: " << numero1 * numero2 << endl;
    cout << "Divisão Inteira: " << numero1 / numero2 << endl;
    cout << "Divisão Real: " << (numero1 / static_cast<double>(numero2)) << endl;

    int maior = (numero1 > numero2) ? numero1 : numero2;
    cout << "O maior número é: " << maior << endl;

    system("pause");
    return 0;
}