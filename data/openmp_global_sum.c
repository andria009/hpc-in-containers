#include <omp.h>
#include <stdio.h>

int main() {
    int n = 1000;
    int sum = 0;
    int array[n];

    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }

    printf("Sum = %d\n", sum);
    return 0;
}
