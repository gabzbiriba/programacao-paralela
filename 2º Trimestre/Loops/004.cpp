/*-----------------------------------------------------

Exercício 4 — Medindo tempo por thread
Adapte o código do exercício anterior para:
a) Medir e exibir o tempo total de execução.
b) Medir e exibir o tempo gasto por cada thread.
c) Mostrar quantas threads foram utilizadas no cálculo.

-----------------------------------------------------*/

#include <iostream> // Biblioteca de saída
#include <omp.h>    // Biblioteca OpenMP
#include <vector>   // Vetores dinâmicos

int main() {
    const int N = 1000000;
    std::vector<double> x(N), y(N), z(N), a(N);

    // Inicializa os vetores de entrada
    for (int i = 0; i < N; i++) {
        x[i] = i * 0.001;
        y[i] = i * 0.002;
        z[i] = i * 0.003;
    }

    // Marca o início do tempo total
    double inicio_total = omp_get_wtime();
    int nthreads = 0; // Variável para armazenar o número de threads usadas

    // Região paralela: cada thread mede seu tempo
    #pragma omp parallel
    {
        double inicio = omp_get_wtime(); // Início do tempo da thread

        // Loop paralelo (cada thread executa uma parte)
        #pragma omp for
        for (int i = 0; i < N; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }

        double fim = omp_get_wtime(); // Fim do tempo da thread
        int id = omp_get_thread_num(); // Identificador da thread

        // Seção crítica para evitar mistura na saída
        #pragma omp critical
        {
            std::cout << "Thread " << id
                      << " executou em " << (fim - inicio)
                      << " s" << std::endl;
        }

        // Apenas a thread mestre coleta o número total de threads
        #pragma omp master
        {
            nthreads = omp_get_num_threads();
        }
    }

    double fim_total = omp_get_wtime(); // Fim do tempo total
    std::cout << "Tempo total: " << (fim_total - inicio_total)
              << " s com " << nthreads << " threads." << std::endl;

    return 0;
}