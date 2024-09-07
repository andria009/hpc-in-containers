#include <omp.h>
#include <stdio.h>

int main() {
    // 1: Define number of threads
    int num_threads = 4; // Number of using threads
    omp_set_num_threads(num_threads); // Set number of threads

    // 2: Create an empty array to count in parallel 
    int n = 10;
    int array[n];

    // Parallel region to count array and print Hello World
    #pragma omp parallel
    {
        // 3: Define shared and private variables
        int thread_id = omp_get_thread_num(); // Private variable, specific for each thread
        int total_threads = omp_get_num_threads(); // Shared variable, for all threads

        // Each thread counts part of the array
        #pragma omp for
        for (int i = 0; i < n; i++) {
            array[i] = i * i; // Count quadrat of the index i
        }

        // 4: Print Hello World using data from array with shared and private variables
        #pragma omp for
        for (int i = 0; i < n; i++) {
            printf("Hello from thread %d of %d: array[%d] = %d\n", thread_id, total_threads, i, array[i]);
        }

        // 5: Using critical section to print synchronization message
        #pragma omp critical
        {
            printf("Thread %d is in the critical section\n", thread_id);
        }

        // 5: Barrier to make sure that all threads have completed before continuing
        #pragma omp barrier
        if (thread_id == 0) {
            printf("All threads have completed their tasks.\n");
        }
    }

    return 0;
}

