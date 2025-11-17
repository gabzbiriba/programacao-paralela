/*-----------------------------------------------------

Exercício 1 — Programação Paralela (OpenMP)

Faça um programa que utilize OpenMP para paralelizar a resolução das equações do segundo grau com a fórmula de Bhaskara.

-----------------------------------------------------*/

#include <iostream> // Entrada e saída
#include <vector> // Vetor
#include <cmath> // Operações matemáticas
#include <omp.h> // OpenMP API

// Função para resolução de equações de segundo grau que utiliza bhaskara
std::pair<double, double> resolver_bhaskara(double a, double b, double c) {
    
    // Calcula delta
    double delta = (b * b) - (4 * a * c);

    // Verifica se o delta é positivo
    if (delta < 0) {
        return {0.0, 0.0};
    }

    // Calcula as raízes da equação
    double x1 = (-b + std::sqrt(delta)) / (2 * a);
    double x2 = (-b - std::sqrt(delta)) / (2 * a);

    // Retorna as raízes
    return {x1, x2};
}

int main () {

    // Número de equações que serão resolvidas em paralelo
    const int N = 1000;

    // Vetores que armazenam os coeficientes
    std::vector<double> a(N), b(N), c(N);

    // Valores de exemplo para os vetores
    for (int i = 0; i < N; ++i) {
        a[i] = 1.0;
        if (i % 2 == 0) {
            // x^2 - 7x + 10 = 0 (raízes 5 e 2)
            b[i] = -7.0;
            c[i] = 10.0;
        } else {
            // x^2 + 2x + 5 = 0 (delta < 0)
            b[i] = 2.0;
            c[i] = 5.0;
        }
    }

    // ===============================================================
    //               ÁREA PARA RESOLVER OS EXERCÍCIOS
    // ===============================================================

    // Vetores que armazenam as soluções
    std::vector<std::pair<double, double>> solucoes(N);

    // Início da execução - Usado para calcular o tempo de execução
    double inicio = omp_get_wtime();

    // Início da região paralela
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        
        // Resolve as equações de segundo grau
        solucoes[i] = resolver_bhaskara(a[i], b[i], c[i]);

    }

    // Fim da execução - Usado para calcular o tempo de execução
    double fim = omp_get_wtime();

    // Exibe 10 resultados para exemplificar o problema
    for (int i = 0; i < 10; ++i) {
        if(std::isnan(solucoes[i].first)) {
            std::cout << "Eq " << i << ": sem raízes reais.\n"; 
        } else {
            std::cout << "Eq " << i << ": x1 = " << solucoes[i].first << ", x2 = " << solucoes[i].second << "\n";
        }
    }

    // Saída Demonstra o tempo de execução do código com paralelismo
    std::cout << "\nTempo total de execucao: " << (fim - inicio) << " segundos.\n";

    // ===============================================================

    return 0;
}