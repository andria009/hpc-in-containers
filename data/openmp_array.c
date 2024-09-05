#include <omp.h>
#include <stdio.h>

int main() {
    // Tahap 1: Menetapkan jumlah thread
    int num_threads = 4; // Jumlah thread yang digunakan
    omp_set_num_threads(num_threads); // Set jumlah thread

    // Tahap 2: Membuat array untuk digunakan sebagai data yang akan dihitung secara paralel
    int n = 10;
    int array[n];

    // Parallel region untuk melakukan perhitungan pada array dan menampilkan Hello World
    #pragma omp parallel
    {
        // Tahap 3: Menentukan variabel shared dan private
        int thread_id = omp_get_thread_num(); // Private variable
        int total_threads = omp_get_num_threads(); // Shared variable, sama untuk semua thread

        // Setiap thread menghitung sebagian dari array
        #pragma omp for
        for (int i = 0; i < n; i++) {
            array[i] = i * i; // Menghitung kuadrat dari indeks i
        }

        // Tahap 4: Menuliskan Hello World dengan menggunakan data dari array dan variabel shared dan private
        #pragma omp for
        for (int i = 0; i < n; i++) {
            printf("Hello from thread %d of %d: array[%d] = %d\n", thread_id, total_threads, i, array[i]);
        }

        // Tahap 5: Menggunakan critical section untuk menampilkan pesan sinkronisasi
        #pragma omp critical
        {
            printf("Thread %d is in the critical section\n", thread_id);
        }

        // Tahap 5: Barrier untuk memastikan semua thread selesai sebelum melanjutkan
        #pragma omp barrier
        if (thread_id == 0) {
            printf("All threads have completed their tasks.\n");
        }
    }

    return 0;
}

