/*-----------------------------------------------------

Exercício 5 — Programação Paralela (OpenMP)

Funções lock

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
    // Objetivo deste exercício: demonstrar o uso de locks (omp_init_lock, omp_set_lock, omp_unset_lock, omp_destroy_lock)
    // Estratégia:
    // - Usar duas variáveis de soma (pares e impares) protegidas por locks diferentes.

    long long soma_pares = 0;
    long long soma_impares = 0;

    omp_lock_t lock_pares, lock_impares;
    omp_init_lock(&lock_pares);
    omp_init_lock(&lock_impares);

    double inicio = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        // calcula uma contribuição simples: soma de índices que possuem raízes reais
        auto [x1, x2] = resolver_bhaskara(a[i], b[i], c[i]);
        if (!std::isnan(x1)) {
            if (i % 2 == 0) {
                omp_set_lock(&lock_pares);
                soma_pares += i; // exemplo de recurso que precisa de proteção
                omp_unset_lock(&lock_pares);
            } else {
                omp_set_lock(&lock_impares);
                soma_impares += i;
                omp_unset_lock(&lock_impares);
            }
        }
    }

    double fim = omp_get_wtime();

    std::cout << "\n(Exercício 5 - locks) Soma pares: " << soma_pares << "\n";
    std::cout << "(Exercício 5 - locks) Soma impares: " << soma_impares << "\n";
    std::cout << "(Exercício 5 - locks) Tempo total: " << (fim - inicio) << " segundos\n";

    omp_destroy_lock(&lock_pares);
    omp_destroy_lock(&lock_impares);

    // Explicação:
    // Locks oferecem controle explícito de sincronização. Cada recurso (soma_pares
    // e soma_impares) é protegido por seu próprio lock, permitindo que threads
    // atualizem recursos diferentes concorrentemente sem conflito.
    return 0;
}