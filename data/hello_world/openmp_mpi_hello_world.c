#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <unistd.h>  // for gethostname
#include <limits.h>  // for HOST_NAME_MAX

int main(int argc, char** argv) {
    int mpi_rank, mpi_size, provided;
    char hostname[HOST_NAME_MAX];

    // Initialize MPI with thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    // Get the rank and size of the MPI processes
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    // Get the hostname of the machine
    gethostname(hostname, HOST_NAME_MAX);

    // Print information about the MPI process
    printf("Hello from MPI process %d out of %d processes running on %s\n", mpi_rank, mpi_size, hostname);

    // Parallel region starts here (OpenMP)
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        printf("  Hello from thread %d out of %d threads in MPI process %d on %s\n", thread_id, num_threads, mpi_rank, hostname);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

