/*-----------------------------------------------------

Exercício 5 — Escalonamento
Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
a) Execute com schedule(static) e schedule(dynamic, 1000).
b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
c) Explique em quais situações static e dynamic são mais adequados.

-----------------------------------------------------*/

#include <iostream> // Biblioteca de entrada e saída
#include <omp.h>    // Biblioteca OpenMP
#include <vector>   // Vetores dinâmicos
#include <iomanip>  // Formatação de saída (std::setprecision)

int main() {
    const int N = 1000000;
    std::vector<double> x(N), y(N), z(N), a(N);

    // Inicializa os vetores
    for (int i = 0; i < N; i++) {
        x[i] = i * 0.001;
        y[i] = i * 0.002;
        z[i] = i * 0.003;
    }

    double inicio, fim;
    int thread_counts[] = {2, 4, 8}; // Quantidades de threads para teste

    std::cout << std::fixed << std::setprecision(6);

    // Testa com diferentes números de threads
    for (int tc : thread_counts) {
        omp_set_num_threads(tc); // Define número de threads
        std::cout << "== Threads: " << tc << " ==\n";

        // --- Escalonamento Estático ---
        // As iterações do loop são divididas igualmente entre as threads.
        inicio = omp_get_wtime();
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
        fim = omp_get_wtime();
        std::cout << "Tempo com schedule(static):          " << (fim - inicio) << " s\n";

        // --- Escalonamento Dinâmico ---
        // As iterações são distribuídas em blocos (chunk = 1000),
        // e threads que terminam mais cedo recebem novos blocos.
        inicio = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic, 1000)
        for (int i = 0; i < N; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
        fim = omp_get_wtime();
        std::cout << "Tempo com schedule(dynamic, 1000):  " << (fim - inicio) << " s\n\n";
    }

    return 0;
}

// Escalonamento estático (static) → melhor para cargas de trabalho uniformes (divisão fixa).
// Escalonamento dinâmico (dynamic) → melhor quando o tempo de cada iteração varia, pois redistribui o trabalho conforme as threads terminam.