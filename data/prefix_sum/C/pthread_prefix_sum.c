#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 4  // Define the number of threads to use

long *arr;      // Input array
long *prefix;   // Prefix sum array
int n;          // Size of the array
int num_threads; // Number of threads to use

// Structure to hold thread arguments
typedef struct {
    int thread_id;
    int start_idx;
    int end_idx;
} thread_data_t;

// Function for each thread to compute its partial prefix sum
void *partial_prefix_sum(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int start = data->start_idx;
    int end = data->end_idx;

    // Each thread computes the prefix sum for its assigned portion of the array
    for (int i = start; i < end; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Check if the array size argument is provided
    if (argc != 2) {
        printf("Usage: %s <size_of_array>\n", argv[0]);
        return -1;
    }

    // Get the array size from execution arguments
    n = atoi(argv[1]);

    // Validate input
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return -1;
    }

    // Determine the number of threads (at most MAX_THREADS)
    num_threads = (n < MAX_THREADS) ? n : MAX_THREADS;

    // Allocate memory for the array and prefix sum
    arr = (long *)malloc(n * sizeof(long));
    prefix = (long *)malloc(n * sizeof(long));

    // Initialize random number generator
    srand(42);

    // Fill the array with random numbers between 0 and 99
    printf("Random array [last 10 elements]:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
        if (i >= (n - 10)) {
            printf("%ld ", arr[i]);
        }
    }
    printf("\n");

    // Initialize prefix sum with the first element
    prefix[0] = arr[0];

    // Create threads for parallel prefix sum calculation
    pthread_t threads[MAX_THREADS];
    thread_data_t thread_data[MAX_THREADS];

    int chunk_size = n / num_threads;  // Calculate the size of each chunk

    // Create the threads and assign each a chunk to work on
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start_idx = (i == 0) ? 1 : i * chunk_size; // Start from 1 for the first thread
        thread_data[i].end_idx = (i == num_threads - 1) ? n : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, partial_prefix_sum, (void *)&thread_data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Adjust the prefix sums across chunks (adding the cumulative sum from previous chunks)
    for (int i = 1; i < num_threads; i++) {
        long adjustment = prefix[i * chunk_size - 1];  // Get the last element from the previous chunk
        for (int j = i * chunk_size; j < thread_data[i].end_idx; j++) {
            prefix[j] += adjustment;
        }
    }

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
