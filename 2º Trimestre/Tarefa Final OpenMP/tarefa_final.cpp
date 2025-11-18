/*--------------------------------------------

Exercício Final: Análise de Dados com OpenMP

Implementar um programa em C/C++ para calcular o coeficiente de variação para uma distribuição de dados com intervalo de classe, 
utilizando OpenMP para paralelizar os cálculos e otimizar o desempenho.

--------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

// Função para criar os intervalos de classes e frequências
void gerarClasses(const vector<double>& dados, double intervalo,
                  vector<double>& pontosMedios, vector<int>& frequencias)
{
    double minVal = dados[0], maxVal = dados[0];

    for (double v : dados) {
        if (v < minVal) minVal = v;
        if (v > maxVal) maxVal = v;
    }

    int numClasses = ceil((maxVal - minVal) / intervalo);

    pontosMedios.resize(numClasses);
    frequencias.assign(numClasses, 0);

    // Calculando pontos médios
    for (int i = 0; i < numClasses; i++) {
        double limiteInferior = minVal + i * intervalo;
        double limiteSuperior = limiteInferior + intervalo;
        pontosMedios[i] = (limiteInferior + limiteSuperior) / 2.0;
    }

    // Frequência de cada classe
    for (double v : dados) {
        int idx = min((int)((v - minVal) / intervalo), numClasses - 1);
        frequencias[idx]++;
    }
}

// Média ponderada
double mediaPonderada(const vector<double>& xi, const vector<int>& fi, int N)
{
    double soma = 0;
    #pragma omp parallel for reduction(+:soma)
    for (int i = 0; i < xi.size(); i++)
        soma += xi[i] * fi[i];

    return soma / N;
}

// Desvio padrão populacional
double desvioPadrao(const vector<double>& xi, const vector<int>& fi,
                    double media, int N)
{
    double soma = 0;
    #pragma omp parallel for reduction(+:soma)
    for (int i = 0; i < xi.size(); i++)
        soma += fi[i] * pow(xi[i] - media, 2);

    return sqrt(soma / N);
}

int main() {
    ifstream arq("dados.txt");
    if (!arq.is_open()) {
        cout << "Erro: não foi possível abrir o arquivo dados.txt\n";
        return 1;
    }

    vector<double> altura, peso;

    double a, p;
    while (arq >> a >> p) {
        altura.push_back(a);
        peso.push_back(p);
    }

    int N = altura.size();
    cout << "Total de registros: " << N << "\n";

    // === Classes ===
    vector<double> xiAltura, xiPeso;
    vector<int> fiAltura, fiPeso;

    gerarClasses(altura, 8.0, xiAltura, fiAltura);
    gerarClasses(peso, 4.0, xiPeso, fiPeso);

    // === Cálculo paralelo ===
    double t0 = omp_get_wtime();

    double mediaAlt = mediaPonderada(xiAltura, fiAltura, N);
    double mediaPeso = mediaPonderada(xiPeso, fiPeso, N);

    double dpAlt = desvioPadrao(xiAltura, fiAltura, mediaAlt, N);
    double dpPeso = desvioPadrao(xiPeso, fiPeso, mediaPeso, N);

    double CV_altura = (dpAlt / mediaAlt) * 100.0;
    double CV_peso = (dpPeso / mediaPeso) * 100.0;

    double tParalelo = omp_get_wtime() - t0;

    // === Versão sequencial para comparação ===
    double t1 = omp_get_wtime();

    double somaAlt = 0, somaPeso = 0;

    for (int i = 0; i < xiAltura.size(); i++)
        somaAlt += xiAltura[i] * fiAltura[i];

    for (int i = 0; i < xiPeso.size(); i++)
        somaPeso += xiPeso[i] * fiPeso[i];

    double mediaAltSeq = somaAlt / N;
    double mediaPesoSeq = somaPeso / N;

    double somaAltDP = 0, somaPesoDP = 0;
    for (int i = 0; i < xiAltura.size(); i++)
        somaAltDP += fiAltura[i] * pow(xiAltura[i] - mediaAltSeq, 2);

    for (int i = 0; i < xiPeso.size(); i++)
        somaPesoDP += fiPeso[i] * pow(xiPeso[i] - mediaPesoSeq, 2);

    double dpAltSeq = sqrt(somaAltDP / N);
    double dpPesoSeq = sqrt(somaPesoDP / N);

    double tSequencial = omp_get_wtime() - t1;

    // === Resultados ===
    cout << "\n=== Resultados ===\n";
    cout << "CV Altura: " << CV_altura << "%\n";
    cout << "CV Peso: " << CV_peso << "%\n";

    cout << "\n=== Desempenho ===\n";
    cout << "Tempo paralelo:   " << tParalelo << " s\n";
    cout << "Tempo sequencial: " << tSequencial << " s\n";
    cout << "Speedup: " << tSequencial / tParalelo << "x\n";

    return 0;
}