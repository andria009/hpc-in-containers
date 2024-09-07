import random
import sys
import multiprocessing as mp

# Fungsi untuk menghitung prefix sum di setiap chunk (bagian)
def prefix_sum_chunk(start, end, arr, prefix, lock):
    for i in range(start, end):
        with lock:
            if i == 0:
                prefix[i] = arr[i]  # Elemen pertama
            else:
                prefix[i] = prefix[i - 1] + arr[i]

def main():
    # Mengecek apakah argumen ukuran array diberikan
    if len(sys.argv) != 2:
        print("Usage: python prefix_sum_parallel.py <size_of_array>")
        return

    try:
        # Mendapatkan ukuran array dari argumen input
        n = int(sys.argv[1])
    except ValueError:
        print("Ukuran array harus angka.")
        return

    if n <= 0:
        print("Ukuran array harus positif.")
        return

    # Menghasilkan array acak
    arr = [random.randint(0, 99) for _ in range(n)]
    print("Array acak:", arr)

    # Membuat shared memory untuk array prefix
    prefix = mp.Array('i', n)  # 'i' = integer
    lock = mp.Lock()  # Lock untuk sinkronisasi

    # Menentukan jumlah proses yang akan digunakan
    num_processes = mp.cpu_count()  # Jumlah core pada CPU
    chunk_size = n // num_processes

    # Membuat dan memulai proses
    processes = []
    for i in range(num_processes):
        start = i * chunk_size
        # Jika ini proses terakhir, ambil sisa elemen
        end = n if i == num_processes - 1 else (i + 1) * chunk_size
        p = mp.Process(target=prefix_sum_chunk, args=(start, end, arr, prefix, lock))
        processes.append(p)
        p.start()

    # Menunggu semua proses selesai
    for p in processes:
        p.join()

    # Menampilkan hasil prefix sum
    print("Prefix Sum:", list(prefix))

if __name__ == "__main__":
    main()
