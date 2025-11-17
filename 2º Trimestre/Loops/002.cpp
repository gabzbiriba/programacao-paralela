/*-----------------------------------------------------

Exercício 2 — Paralelizando um for simples
a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
b) Escreva um loop sequencial que soma todos os elementos.
c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
d) Compare os resultados e explique por que a diretiva reduction é necessária.

-----------------------------------------------------*/

#include <iostream> // Biblioteca padrão de entrada e saída
#include <omp.h>    // Biblioteca do OpenMP

int main() {
    const int N = 100; // Tamanho do vetor
    int v[N];          // Declaração do vetor
    int soma_seq = 0;  // Variável para soma sequencial
    int soma_par = 0;  // Variável para soma paralela

    // Inicializa o vetor com o valor 1
    for (int i = 0; i < N; i++) {
        v[i] = 1;
    }

    // Loop sequencial — executado por uma única thread
    for (int i = 0; i < N; i++) {
        soma_seq += v[i];
    }

    // Loop paralelo com diretiva reduction
    // A cláusula reduction(+:soma_par) cria cópias locais de soma_par para cada thread
    // No final, todas as cópias são somadas e o resultado é acumulado na variável original
    #pragma omp parallel for reduction(+:soma_par)
    for (int i = 0; i < N; i++) {
        soma_par += v[i];
    }

    // Se não houvesse "reduction", haveria condição de corrida,
    // pois várias threads modificariam soma_par simultaneamente.

    // Exibe os resultados no terminal
    std::cout << "Soma sequencial: " << soma_seq << std::endl;
    std::cout << "Soma paralela:   " << soma_par << std::endl;

    return 0;
}