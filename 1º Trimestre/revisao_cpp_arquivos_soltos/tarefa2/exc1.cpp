/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------

1. Variáveis, Constantes e auto (002.cpp)
a) Declare variáveis para armazenar: nome do aluno (string), idade (int), altura
(double), aprovado (bool). Exiba-as no console.

b) Crie uma constante para representar o valor de π e calcule a área de um círculo
de raio 5.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
using namespace std;

int main () {
    string nome = "Cleiton";
    int idade = 25;
    double altura = 1.82;
    bool aprovado = true;

    cout << "Nome: " << nome << '\n'
         << "Idade: " << idade<< '\n'
         << "Altura: " << altura << '\n'
         << boolalpha << "Aprovado? " << aprovado << '\n';

    const double PI = 3.14159;
    auto areacirculo = PI * (5 * 5);
    cout << "Área do círculo de raio 5: " << areacirculo << endl;

    system("pause");
    return 0;
}