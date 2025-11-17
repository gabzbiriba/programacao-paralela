/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
7. Arrays e std::vector (008.cpp)
a) Crie um array de 5 inteiros e calcule a soma dos elementos.

b) Crie um vector<int> com os valores {5, 10, 15} e insira mais dois números usando
push_back. Exiba o tamanho e a soma.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
using namespace std;

int main() {

    int array[5] = {1,2,3,4,5};
    int somaArray = 0;
    for (int i = 0; i < 5; ++i) somaArray += array[i];
    cout << "Soma dos números do array: " << somaArray << endl;

    vector<int> v = {5, 10, 15};
    v.push_back(20);
    v.push_back(25);
    int somaV = 0;
    for (int x : v) somaV += x;
    cout << "Soma do vetor: " << somaV << endl;
    cout << "Tamanho do vetor: " << v.size() << endl;

    system("pause");
    return 0;
}