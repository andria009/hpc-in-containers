import java.util.Random;

public class PrefixSum {

    // Fungsi untuk menghitung prefix sum
    public static void prefixSum(int[] arr, int[] prefix) {
        prefix[0] = arr[0]; // Elemen pertama

        // Menghitung prefix sum
        for (int i = 1; i < arr.length; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }
    }

    public static void main(String[] args) {
        // Mengecek apakah argumen ukuran array diberikan
        if (args.length != 1) {
            System.out.println("Usage: java PrefixSum <size_of_array>");
            return;
        }

        // Mengambil ukuran array dari argumen eksekusi
        int n = Integer.parseInt(args[0]);

        // Validasi input
        if (n <= 0) {
            System.out.println("Ukuran array harus positif.");
            return;
        }

        // Membuat array acak
        int[] arr = new int[n];
        int[] prefix = new int[n];
        Random rand = new Random();

        // Mengisi array dengan bilangan acak dan menampilkannya
        System.out.println("Array acak:");
        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt(100); // Bilangan acak antara 0 hingga 99
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        // Menghitung prefix sum
        prefixSum(arr, prefix);

        // Menampilkan hasil prefix sum
        System.out.println("Prefix Sum:");
        for (int i = 0; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }
}
