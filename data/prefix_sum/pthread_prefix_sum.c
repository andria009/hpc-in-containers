#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

// Struktur untuk melewatkan argumen ke thread
typedef struct {
    int *arr;
    int *prefix;
    int start;
    int end;
} ThreadData;

// Fungsi yang dijalankan oleh setiap thread
void* prefix_sum_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int* arr = data->arr;
    int* prefix = data->prefix;
    int start = data->start;
    int end = data->end;

    // Menghitung prefix sum untuk bagian yang ditugaskan ke thread
    for (int i = start; i < end; i++) {
        if (i == 0) {
            prefix[i] = arr[i]; // Elemen pertama
        } else {
            prefix[i] = prefix[i - 1] + arr[i]; // Menghitung prefix sum
        }
    }

    pthread_exit(NULL);
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

    // Alokasi memori untuk array dan prefix sum secara dinamis
    int *arr = (int *)malloc(n * sizeof(int));
    int *prefix = (int *)malloc(n * sizeof(int));

    // Menghasilkan bilangan acak untuk array
    srand(42);
    // printf("Array acak:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Menghasilkan bilangan acak antara 0 hingga 99
    //     printf("%d ", arr[i]);
    }
    // printf("\n");

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int chunk_size = n / NUM_THREADS;

    // Membuat thread dan membagi tugas
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = arr;
        thread_data[i].prefix = prefix;
        thread_data[i].start = i * chunk_size;
        if (i == NUM_THREADS - 1) {
            thread_data[i].end = n; // Thread terakhir menangani sisa elemen
        } else {
            thread_data[i].end = (i + 1) * chunk_size;
        }

        // Membuat thread
        pthread_create(&threads[i], NULL, prefix_sum_thread, (void*)&thread_data[i]);
    }

    // Menunggu semua thread selesai
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Menampilkan hasil prefix sum
    printf("Prefix Sum [10 elemen terakhir]:\n");
    for (int i = n-10; i < n; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\n");

    // Membebaskan memori yang dialokasikan
    free(arr);
    free(prefix);

    return 0;
}
