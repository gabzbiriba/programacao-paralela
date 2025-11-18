/*----------------------------------------

Exercício 3: O Token Circular (Comunicação em Anel)

----------------------------------------*/

#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);
    
    // Obtém o rank (identificador) do processo atual e o número total de processos
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verifica se temos pelo menos 2 processos para formar um anel
    if (size < 2) {
        if (rank == 0) {
            std::cerr << "Erro: Requer pelo menos 2 processos." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    // Variável que armazenará o token
    int token;
    
    // Calcula para qual processo enviar o token (próximo no anel)
    int destino = (rank + 1) % size;
    
    // Calcula de qual processo receber o token (anterior no anel)
    // Adicionamos 'size' antes do módulo para evitar números negativos
    int origem = (rank - 1 + size) % size;

    // O processo 0 tem comportamento especial: inicia e finaliza o anel
    if (rank == 0) {
        // Processo 0 cria o token com valor inicial 100
        token = 100;
        std::cout << "Processo " << rank << " inicia o anel com o token = " << token << std::endl;
        
        // Primeiro, envia o token para iniciar a circulação no anel
        MPI_Send(&token, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        
        // Depois, espera receber o token de volta após completar toda a volta
        MPI_Recv(&token, 1, MPI_INT, origem, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Imprime mensagem final quando o token retorna
        std::cout << "Processo " << rank << " recebeu o token de volta do processo " 
                  << origem << ". Anel completo." << std::endl;
                  
    } else {
        // Processos 1, 2, 3, ... (todos exceto o 0)
        // Primeiro recebem o token do processo anterior
        MPI_Recv(&token, 1, MPI_INT, origem, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Imprimem que receberam o token
        std::cout << "Processo " << rank << " recebeu o token = " << token << std::endl;
        
        // Depois enviam o token para o próximo processo no anel
        MPI_Send(&token, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}