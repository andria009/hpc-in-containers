import random
import sys

# Fungsi untuk menghitung prefix sum
def prefix_sum(arr):
    prefix = [0] * len(arr)
    prefix[0] = arr[0]  # Elemen pertama

    # Menghitung prefix sum
    for i in range(1, len(arr)):
        prefix[i] = prefix[i - 1] + arr[i]

    return prefix

def main():
    # Mengecek apakah argumen ukuran array diberikan
    if len(sys.argv) != 2:
        print("Usage: python prefix_sum.py <size_of_array>")
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

    # Menghitung prefix sum
    result = prefix_sum(arr)
    print("Prefix Sum:", result)

if __name__ == "__main__":
    main()
