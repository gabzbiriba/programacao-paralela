/*-----------------------------------------------------

Exercício 2 — Programação Paralela (OpenMP)

Crie uma entrada de dados onde o usuário decicirá a quantidade de equações a serem resolvidas.
Ao final, mostre o tempo gasto para resolver as equações, e o número de equações que possuem raízes reais e quantas não possuem.

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

    // Contadores para ilustrar quantas equações possuem raízes reais e quantas não possuem
    int com_raizes = 0;
    int sem_raizes = 0;

    // Início da execução - será usado para calcular o tempo
    double inicio = omp_get_wtime();

    // Seção paralela
    #pragma omp parallel for reduction(+:com_raizes, sem_raizes)
    for (int i = 0; i < N; ++i) {
        auto [x1, x2] = resolver_bhaskara(a[i], b[i], c[i]);

        #pragma omp atomic
        if (std::isnan(x1)) { // Incrementa de acordo com a quantidade de equações
            sem_raizes++;
        } else {
            com_raizes++;
        }
    }

    // Fim da execução - será usado para calcular o tempo
    double fim = omp_get_wtime();

    // Saídas para exibir os resultados
    std::cout << "\nResultados:\n";
    std::cout << "\nEquacoes com raizes reais: " << com_raizes << "\n";
    std::cout << "\nEquacoes sem raizes reais: " << sem_raizes << "\n";
    std::cout << "\nTempo total de execucao: " << (fim - inicio) << " segundos.\n";

    // ===============================================================

    return 0;
}