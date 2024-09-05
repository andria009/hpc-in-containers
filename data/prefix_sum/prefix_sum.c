#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fungsi untuk menghitung Prefix Sum
void prefix_sum(int arr[], long prefix[], int n) {
    prefix[0] = arr[0]; // Inisialisasi elemen pertama dari prefix sum

    // Menghitung prefix sum untuk setiap elemen
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i]; // Setiap elemen adalah jumlah kumulatif elemen sebelumnya
    }
}

int main(int argc, char *argv[]) {
    // Mengecek apakah argumen ukuran array diberikan
    if (argc != 2) {
        printf("Usage: %s <size_of_array>\n", argv[0]);
        return -1;
    }

    // Mengambil ukuran array dari argumen eksekusi
    int n = atoi(argv[1]);

    // Validasi input
    if (n <= 0) {
        printf("Ukuran array harus positif.\n");
        return -1;
    }

    int arr[n];
    long prefix[n];

    // Inisialisasi random number generator
    srand(42);

    // // Mengisi array dengan bilangan acak dan menampilkannya
    // printf("Array acak:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Menghasilkan bilangan acak antara 0 hingga 99
    //     printf("%d ", arr[i]);
    }
    // printf("\n");

    // Menghitung prefix sum
    prefix_sum(arr, prefix, n);

    // Menampilkan hasil prefix sum
    printf("Prefix Sum [10 elemen terakhir]:\n");
    for (int i = n-10; i < n; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\n");

    return 0;
}

