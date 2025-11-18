/*----------------------------------------

Exercício 1: Ping-Pong Numérico

----------------------------------------*/

#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            std::cerr << "Erro: Este exercicio deve ser executado com exatamente 2 processos." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    const int NUM_TROCAS = 10;
    int valor = 0;

    // PROCESSO 0 -----------------------------------------------------
    if (rank == 0) {

        MPI_Send(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        for (int i = 0; i < NUM_TROCAS - 1; i++) {

            MPI_Recv(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            valor++;

            if (i == NUM_TROCAS - 2) {
                std::cout << "Processo 0 recebeu " << valor - 1
                          << ", finalizando." << std::endl;
            } else {
                std::cout << "Processo 0 recebeu " << valor - 1
                          << ", enviando " << valor << "." << std::endl;

                MPI_Send(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            }
        }

    }
    // PROCESSO 1 -----------------------------------------------------
    else if (rank == 1) {

        for (int i = 0; i < NUM_TROCAS - 1; i++) {

            MPI_Recv(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            valor++;

            std::cout << "Processo 1 recebeu " << valor - 1
                      << ", enviando " << valor << "." << std::endl;

            MPI_Send(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }

        MPI_Recv(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Finalize();
    return 0;
}