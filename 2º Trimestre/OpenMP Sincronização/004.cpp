/*-----------------------------------------------------

Exercício 4 — Programação Paralela (OpenMP)

#pragma omp ordered

-----------------------------------------------------*/
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Função para calcular as raízes de uma equação de segundo grau
// Retorna um std::pair contendo as raízes x1 e x2.
// Se não houver raízes reais, ambas serão 0.
std::pair<double, double> resolver_bhaskara(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);

    if (delta < 0) {
        return {0.0, 0.0};
    }

    double x1 = (-b + std::sqrt(delta)) / (2 * a);
    double x2 = (-b - std::sqrt(delta)) / (2 * a);

    return {x1, x2};
}

int main() {
    // Número de equações a serem resolvidas
    const int N = 1000;

    // Vetores para armazenar os coeficientes
    std::vector<double> a(N), b(N), c(N);

    // Preenche os vetores com valores de exemplo.
    // Metade terá raízes reais, a outra metade não.
    for (int i = 0; i < N; ++i) {
        a[i] = 1.0;
        if (i % 2 == 0) {
            // Equação com raízes reais: x^2 - 7x + 10 = 0 (raízes 5 e 2)
            b[i] = -7.0;
            c[i] = 10.0;
        } else {
            // Equação sem raízes reais: x^2 + 2x + 5 = 0 (delta < 0)
            b[i] = 2.0;
            c[i] = 5.0;
        }
    }

    // ===============================================================
    //               ÁREA PARA RESOLVER OS EXERCÍCIOS
    // ===============================================================

    // Adicione aqui o seu código OpenMP para cada exercício.


    // ===============================================================
    // Objetivo deste exercício: demonstrar #pragma omp ordered
    // Estratégia:
    // - Executamos um loop paralelo que calcula as raízes.
    // - Usamos a cláusula 'ordered' no pragma parallel for e '#pragma omp ordered'
    //   para imprimir os resultados na ordem crescente do índice i.

    const int SAMPLE = 20; // quantos resultados mostrar
    double inicio = omp_get_wtime();

    #pragma omp parallel for ordered
    for (int i = 0; i < N; ++i) {
        auto [x1, x2] = resolver_bhaskara(a[i], b[i], c[i]);

        // Apenas para demonstração: impressão ordenada dos primeiros SAMPLE
        if (i < SAMPLE) {
            #pragma omp ordered
            {
                if (std::isnan(x1)) {
                    std::cout << "Eq " << i << ": sem raizes reais.\n";
                } else {
                    std::cout << "Eq " << i << ": x1 = " << x1 << ", x2 = " << x2 << "\n";
                }
            }
        }
    }

    double fim = omp_get_wtime();
    std::cout << "\n(Exercício 4 - ordered) Tempo total: " << (fim - inicio) << " segundos\n";

    // Explicação:
    // A cláusula 'ordered' permite que, mesmo em um loop paralelo, trechos marcados
    // com '#pragma omp ordered' sejam executados na ordem sequencial dos índices.
    // Isso é útil para produzir saídas ordenadas sem serializar todo o loop.
    return 0;
}