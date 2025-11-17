/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
2. Entrada e Saída (cin, getline) (003.cpp)
a) Peça ao usuário que digite o primeiro nome e a idade. Depois, mostre uma
mensagem: Olá, João! Você tem 20 anos.

b) Agora, peça o nome completo usando getline e exiba-o no formato: Nome
completo: João da Silva.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    string nome;
    int idade;
    cout << "Digite seu nome: ";
    cin >> nome;
    cout << "Digite sua idade: ";
    cin >> idade;
    cout << "Olá, " << nome << "! Você tem " << idade << " anos." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nomeCompleto;
    cout << "Digite o seu nome completo: ";
    getline(cin, nomeCompleto);
    cout << "Nome completo: " << nomeCompleto << endl;
    
    system("pause");
    return 0;
}