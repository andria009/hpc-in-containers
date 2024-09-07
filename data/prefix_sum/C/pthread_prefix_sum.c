#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

// Structure to pass arguments to the thread
typedef struct {
    int *arr;
    int *prefix;
    int start;
    int end;
} ThreadData;

// Function executed by each thread
void* prefix_sum_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int* arr = data->arr;
    int* prefix = data->prefix;
    int start = data->start;
    int end = data->end;

    // Calculate prefix sum for the section assigned to the thread
    for (int i = start; i < end; i++) {
        if (i == 0) {
            prefix[i] = arr[i]; // First element
        } else {
            prefix[i] = prefix[i - 1] + arr[i]; // Calculate prefix sum
        }
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
    int n = atoi(argv[1]);

    // Validate input
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return -1;
    }

    // Dynamically allocate memory for the array and prefix sum
    int *arr = (int *)malloc(n * sizeof(int));
    int *prefix = (int *)malloc(n * sizeof(int));

    // Generate random numbers for the array
    srand(42);
    // printf("Random array:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    //     printf("%d ", arr[i]);
    }
    // printf("\n");

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int chunk_size = n / NUM_THREADS;

    // Create threads and divide tasks
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = arr;
        thread_data[i].prefix = prefix;
        thread_data[i].start = i * chunk_size;
        if (i == NUM_THREADS - 1) {
            thread_data[i].end = n; // The last thread handles the remaining elements
        } else {
            thread_data[i].end = (i + 1) * chunk_size;
        }

        // Create thread
        pthread_create(&threads[i], NULL, prefix_sum_thread, (void*)&thread_data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display the prefix sum result
    printf("Prefix Sum [last 10 elements]:\n");
    for (int i = n-10; i < n; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(arr);
    free(prefix);

    return 0;
}
