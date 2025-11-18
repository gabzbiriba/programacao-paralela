/*----------------------------------------

Exercício 2: Soma Paralela de Vetor (Mestre/Trabalhador)

----------------------------------------*/

#include <iostream>
#include <vector>
#include <numeric>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) std::cerr << "Erro: Requer pelo menos 2 processos." << std::endl;
        MPI_Finalize();
        return 1;
    }

    const int TAMANHO_TOTAL = 120;

    if (rank == 0) {
        // Processo Mestre
        if (TAMANHO_TOTAL % (size - 1) != 0) {
            std::cerr << "O tamanho do vetor nao e divisivel pelo numero de trabalhadores." << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        std::cout << "Mestre (P0): Dividindo o trabalho para " << (size - 1) << " trabalhadores." << std::endl;

        std::vector<int> vetor_mestre(TAMANHO_TOTAL, 1);
        int num_trabalhadores = size - 1;
        int tamanho_parte = TAMANHO_TOTAL / num_trabalhadores;

        // 1. Dividir e enviar o trabalho para cada trabalhador
        for (int trabalhador = 1; trabalhador < size; trabalhador++) {
            int indice_inicial = (trabalhador - 1) * tamanho_parte;
            MPI_Send(&vetor_mestre[indice_inicial], tamanho_parte, MPI_INT, 
                     trabalhador, 0, MPI_COMM_WORLD);
        }

        // 2. Receber os resultados dos trabalhadores
        int soma_total = 0;
        for (int trabalhador = 1; trabalhador < size; trabalhador++) {
            int soma_parcial;
            MPI_Recv(&soma_parcial, 1, MPI_INT, trabalhador, 0, 
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            soma_total += soma_parcial;
        }

        std::cout << "Mestre (P0): Recebi todas as somas parciais." << std::endl;
        std::cout << "Mestre (P0): A SOMA TOTAL E: " << soma_total << std::endl;

    } else {
        // Lógica dos Trabalhadores (Processos 1, 2, ...)
        
        // 1. Descobrir o tamanho da parte que vai receber
        int num_trabalhadores = size - 1;
        int tamanho_parte = TAMANHO_TOTAL / num_trabalhadores;
        
        // 2. Receber a sua parte do vetor
        std::vector<int> parte_vetor(tamanho_parte);
        MPI_Recv(parte_vetor.data(), tamanho_parte, MPI_INT, 0, 0, 
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // 3. Calcular a soma parcial
        int soma_parcial = std::accumulate(parte_vetor.begin(), parte_vetor.end(), 0);
        
        std::cout << "Trabalhador (P" << rank << "): Recebi minha parte, minha soma parcial e " 
                  << soma_parcial << "." << std::endl;

        // 4. Enviar a soma parcial de volta para o mestre
        MPI_Send(&soma_parcial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}