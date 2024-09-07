#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate Prefix Sum
void prefix_sum(int arr[], long prefix[], int n) {
    prefix[0] = arr[0]; // Initialize the first element of the prefix sum

    // Calculate prefix sum for each element
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i]; // Each element is the cumulative sum of the previous elements
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

    int arr[n];
    long prefix[n];

    // Initialize random number generator
    srand(42);

    // // Fill the array with random numbers and display it
    // printf("Random array:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    //     printf("%d ", arr[i]);
    }
    // printf("\n");

    // Calculate prefix sum
    prefix_sum(arr, prefix, n);

    // Display the prefix sum result
    printf("Prefix Sum [last 10 elements]:\n");
    for (int i = n-10; i < n; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\n");

    return 0;
}
