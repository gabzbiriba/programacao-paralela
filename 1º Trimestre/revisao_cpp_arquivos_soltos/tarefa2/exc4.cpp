/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
4. Estruturas de Controle (005.cpp)
a) Leia uma nota (0 a 10) e mostre: 'Aprovado' (nota ≥ 6), 'Prova final' (4 ≤ nota < 6),
'Reprovado' (nota < 4).

b) Crie um menu (switch): 1 – Cadastrar nome, 2 – Listar nomes, 3 – Sair.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

int main() {
    int nota;
    cout << "Insira uma nota de 0 a 10: ";
    cin >> nota;

    if (nota >= 6) cout << "Aprovado" << endl;
    else if (nota >= 4) cout << "Prova final" << endl;
    else cout << "Reprovado" << endl;

    int opcao;
    cout << "\nMenu: \n1 - Cadastrar nome \n2 - Listar nomes \n3 - Sair\n";
    cin >> opcao;

    switch (opcao) {
        case 1: cout << "Cadastrando..." << endl; break;
        case 2: cout << "Listando..." << endl; break;
        case 3: cout << "Saindo..." << endl; break;
        default: cout << "Opção inválida!" << endl; break;
    }

    system("pause");
    return 0;
}