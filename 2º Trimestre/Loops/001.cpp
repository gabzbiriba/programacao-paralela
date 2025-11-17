/*-----------------------------------------------------

Exercício 1 — “Hello World” Paralelo
a) Crie uma região paralela com #pragma omp parallel.
b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
c) Configure o programa para rodar com 4 threads.

-----------------------------------------------------*/

#include <iostream>  // Biblioteca para operações de entrada e saída (std::cout)
#include <omp.h>     // Biblioteca principal do OpenMP
#include <vector>    // Biblioteca para manipular vetores (std::vector)
#include <string>    // Biblioteca para trabalhar com strings (std::string)

int main () {

    // Define o número de threads que serão usadas (4 neste caso)
    omp_set_num_threads(4);

    // Cria um vetor de strings para armazenar as mensagens de cada thread
    std::vector<std::string> mensagens(4);

    // Criação de uma região paralela — todas as threads abaixo executam o bloco
    #pragma omp parallel
    {
        // Obtém o identificador único da thread atual (0, 1, 2 ou 3)
        int thread_id = omp_get_thread_num();

        // Obtém o número total de threads em execução
        int total_threads = omp_get_num_threads();

        // Cada thread monta sua própria mensagem no vetor
        mensagens[thread_id] = "Hello World! do thread " +
                               std::to_string(thread_id) +
                               " em um conjunto de " +
                               std::to_string(total_threads) + " threads.";
    }

    // Impressão das mensagens no terminal (feita de forma sequencial)
    for (auto &msg : mensagens)
        std::cout << msg << std::endl;

    return 0; // Fim do programa
}