/*-----------------------------------------------------

Exercício 3 — Programação Paralela (OpenMP)

#pragma omp barrier

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
        return {NAN, NAN}; // Não possui raízes reais
    }

    // Calcula as raízes da equação
    double x1 = (-b + std::sqrt(delta)) / (2 * a);
    double x2 = (-b - std::sqrt(delta)) / (2 * a);

    // Retorna as raízes
    return {x1, x2};
}

int main () {

    // Quantidade de equações a ser definida pelo usuário
    int N;

    // Saída para perguntar ao usuário
    std::cout << "Insira a quantidade de equacoes a serem resolvidas: ";
    std::cin >> N;

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
    // Objetivo deste exercício: demonstrar o uso de #pragma omp barrier
    // Estratégia:
    // 1) Cada thread calcula as raízes da sua equação.
    // 2) Usamos uma barrier para garantir que todas as threads terminaram
    //    antes de fazer a agregação/contagem final (etapa sequencial).

    int com_raizes = 0;

    double inicio = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        // Cada thread pode processar vários índices dependendo do schedule
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            auto [x1, x2] = resolver_bhaskara(a[i], b[i], c[i]);
            // salva apenas para demonstração (não necessário aqui)
            // Nada compartilhado é modificado nesta fase crítica.
        }

        // Ponto de sincronização: aguarda todas as threads terminarem o loop
        #pragma omp barrier

        // Após a barrier, apenas uma região faz a contagem agregada
        #pragma omp single
        {
            for (int i = 0; i < N; ++i) {
                auto [x1, x2] = resolver_bhaskara(a[i], b[i], c[i]);
                if (!std::isnan(x1)) com_raizes++;
            }
        }
    }

    double fim = omp_get_wtime();

    std::cout << "\nResultado (Exercício 3 - barrier):\n";
    std::cout << "Equacoes com raizes reais: " << com_raizes << "\n";
    std::cout << "Tempo total: " << (fim - inicio) << " segundos\n";

    // Explicação:
    // Neste exercício usamos #pragma omp barrier para garantir que todas as
    // threads concluam a fase de cálculo paralelo antes de realizar a
    // agregação sequencial dos resultados. A diretiva 'single' garante que
    // apenas uma thread execute a contagem agregada após a barrier.
    // ===============================================================

    return 0;
}