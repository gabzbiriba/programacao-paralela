/*-----------------------------------------------------

Exercício 3 — Expressão Vetorial
Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
a) Faça a versão sequencial.
b) Paralelize com #pragma omp parallel for schedule(static).
c) Mostre o tempo total de execução em cada versão.

-----------------------------------------------------*/

#include <iostream> // Saída padrão
#include <omp.h>    // Biblioteca OpenMP
#include <vector>   // Vetores dinâmicos

int main() {
    const int N = 1000000; // Tamanho dos vetores

    // Criação dos vetores x, y, z e a
    std::vector<double> x(N), y(N), z(N), a(N);

    // Inicialização dos vetores de entrada
    for (int i = 0; i < N; i++) {
        x[i] = i * 0.001;
        y[i] = i * 0.002;
        z[i] = i * 0.003;
    }

    // --- Versão Sequencial ---
    double inicio = omp_get_wtime(); // Marca o início do tempo
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    double fim = omp_get_wtime(); // Marca o fim do tempo
    std::cout << "Tempo sequencial: " << (fim - inicio) << " s" << std::endl;

    // --- Versão Paralela ---
    inicio = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    fim = omp_get_wtime();
    std::cout << "Tempo paralelo:   " << (fim - inicio) << " s" << std::endl;

    return 0;
}