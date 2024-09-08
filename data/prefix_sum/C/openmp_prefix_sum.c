#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function to calculate Prefix Sum using OpenMP
void prefix_sum(long arr[], long prefix[], int n) {
    int num_threads;

    // Set the number of threads to 4
    omp_set_num_threads(4);
    
    // Copy the first element directly
    prefix[0] = arr[0];

    // Parallel prefix sum computation
    #pragma omp parallel
    {
        // Each thread calculates a portion of the prefix sum
        int tid = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        int chunk_size = (n + num_threads - 1) / num_threads;  // Divide work among threads

        // Get start and end indices for this thread
        int start = tid * chunk_size;
        int end = (start + chunk_size > n) ? n : start + chunk_size;

        if (start < n) {
            // Each thread computes its chunk's prefix sum
            for (int i = start; i < end; i++) {
                if (i == 0) {
                    prefix[i] = arr[i];
                } else {
                    prefix[i] = prefix[i - 1] + arr[i];
                }
            }
        }

        // Wait for all threads to finish their partial prefix sums
        #pragma omp barrier

        // Correction phase: Adjust each chunk by adding the last element from the previous chunk
        long correction = 0;
        for (int i = 0; i < tid; i++) {
            correction += prefix[(i + 1) * chunk_size - 1];
        }

        if (start < n && correction != 0) {
            for (int i = start; i < end; i++) {
                prefix[i] += correction;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the array size argument is provided
    if (argc != 2) {
        printf("Usage: %s <size_of_array>\n", argv[0]);
        return -1;
    }

    // Get the array size from execution arguments
    int n = atoi(argv[1]);

    // Validate input
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return -1;
    }

    long *arr = (long *)malloc(n * sizeof(long));
    long *prefix = (long *)malloc(n * sizeof(long));

    // Initialize random number generator
    srand(42);

    // Fill the array with random numbers between 0 and 99 and display the last 10 elements
    printf("Random array [last 10 elements]:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
        if (i >= (n - 10)) {
            printf("%ld ", arr[i]);
        }
    }
    printf("\n");

    // Calculate prefix sum using OpenMP
    prefix_sum(arr, prefix, n);

    // Display the prefix sum result (last 10 elements)
    printf("Prefix Sum [last 10 elements]:\n");
    for (int i = (n - 10); i < n; i++) {
        printf("%ld ", prefix[i]);
    }
    printf("\n");

    // Free allocated memory
    free(arr);
    free(prefix);

    return 0;
}
