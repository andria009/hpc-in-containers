#include <mpi.h>
#include <omp.h>
#include <stdio.h>

void matrix_multiply(int* A, int* B, int* C, int N, int rank, int size) {
    int rows_per_process = N / size;
    int start_row = rank * rows_per_process;
    int end_row = (rank + 1) * rows_per_process;

    #pragma omp parallel for collapse(2)
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i*N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i*N + j] += A[i*N + k] * B[k*N + j];
            }
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int N = 100; // Size of the matrices
    int A[N*N], B[N*N], C[N*N];

    // Initialize matrices A and B
    if (world_rank == 0) {
        for (int i = 0; i < N*N; i++) {
            A[i] = i % 100;
            B[i] = i % 100;
        }
    }

    // Broadcast matrices to all processes
    MPI_Bcast(A, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform matrix multiplication
    matrix_multiply(A, B, C, N, world_rank, world_size);

    MPI_Finalize();
    return 0;
}
