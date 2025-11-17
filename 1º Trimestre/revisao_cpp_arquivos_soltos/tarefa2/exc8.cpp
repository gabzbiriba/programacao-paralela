/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programação Paralela.
Aluno.....: Gabrielle Arruda Rodrigues
Matrícula.: 2312130129
--------------------------------------------------------------------------------------------------------------------------
8. Ponteiros e Referências (009.cpp)
a) Declare uma variável int x = 10. Use um ponteiro para dobrar o valor e uma
referência para triplicá-lo.

b) Crie um ponteiro dinâmico para armazenar um número e libere a memória com delete.
--------------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <memory>
using namespace std;

void dobra(int* p) {
    if (p) *p *= 2;
}

void triplica(int& r) {
    r *= 3;
}

int main() {

    int x = 10;
    int* px = &x;
    cout << "x = " << x << ", &x = " << &x << endl;
    cout << "px = " << px << ", *px = " << *px << endl;

    dobra(px);
    cout << "x após dobrar = " << x << endl;

    triplica(x);
    cout << "x após triplicar = " << x << endl;

    int* pHeap = new int(42);
    cout << "*pHeap = " << *pHeap << endl;
    delete pHeap;

    unique_ptr<int> up = make_unique<int>(99);
    cout << "*up = " << *up << endl;

    system("pause");
    return 0;
}