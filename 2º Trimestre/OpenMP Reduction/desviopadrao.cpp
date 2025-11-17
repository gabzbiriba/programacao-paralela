/*-----------------------------------------------------

Faça um programa que encontre o desvio padrão amostral. de um conjunto de valores de dois milhões de salários de uma bigtech fictícia espalhadas nas americas. 
Escolha o nome da sua bigtech, assim como, dos departamentos e cargos.

-----------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <chrono>
#include <omp.h>

using namespace std;

int main() {
    // Nome da empresa fictícia
    string empresa = "Tech Paralela";

    // Departamentos e cargos
    vector<string> departamentos = {"Engenharia", "Marketing", "Vendas", "RH", "Financeiro"};
    vector<string> cargos = {"Júnior", "Pleno", "Sênior", "Gerente", "Diretor"};

    const size_t N = 2000000; // 2 milhões de salários
    vector<double> salarios(N);

    // Gerador de números aleatórios
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(3000.0, 50000.0); // salários entre 3 mil e 50 mil

    // Geração dos salários (sequencial, pois não é gargalo principal)
    for (size_t i = 0; i < N; ++i) {
        salarios[i] = dist(gen);
    }

    auto inicio = chrono::high_resolution_clock::now();

    // ---------- Cálculo paralelo da média ----------
    double soma = 0.0;

    #pragma omp parallel for reduction(+:soma)
    for (long long i = 0; i < (long long)N; ++i) {
        soma += salarios[i];
    }

    double media = soma / N;

    // ---------- Cálculo paralelo da soma das diferenças ao quadrado ----------
    double soma_dif_quadrado = 0.0;

    #pragma omp parallel for reduction(+:soma_dif_quadrado)
    for (long long i = 0; i < (long long)N; ++i) {
        double dif = salarios[i] - media;
        soma_dif_quadrado += dif * dif;
    }

    double desvio_padrao = sqrt(soma_dif_quadrado / (N - 1));

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo = fim - inicio;

    // ---------- Exibição dos resultados ----------
    cout << "----------------------------------------\n";
    cout << "Empresa: " << empresa << "\n";
    cout << "Departamentos: ";
    for (auto &d : departamentos) cout << d << "  ";
    cout << "\nCargos: ";
    for (auto &c : cargos) cout << c << "  ";
    cout << "\n----------------------------------------\n";
    cout << "Número de salários analisados: " << N << endl;
    cout << "Média salarial: R$ " << media << endl;
    cout << "Desvio padrão amostral: R$ " << desvio_padrao << endl;
    cout << "Tempo de processamento paralelo: " << tempo.count() << " segundos\n";
    cout << "Threads utilizadas: " << omp_get_max_threads() << endl;
    cout << "----------------------------------------\n";

    return 0;
}
