import java.util.Random;

public class ThreadPrefixSum {
    
    private static int[] arr;
    private static int[] prefix;
    private static int numThreads;

    // Thread class for computing a portion of the prefix sum
    static class PrefixSumThread extends Thread {
        private final int start;
        private final int end;

        public PrefixSumThread(int start, int end) {
            this.start = start;
            this.end = end;
        }

        @Override
        public void run() {
            for (int i = start; i <= end; i++) {
                // Synchronized block to ensure no race condition occurs when updating shared prefix array
                synchronized (prefix) {
                    if (i == 0) {
                        prefix[i] = arr[i];  // First element
                    } else {
                        prefix[i] = prefix[i - 1] + arr[i];
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Validate and parse command-line argument
        if (args.length != 1) {
            System.out.println("Usage: java ThreadPrefixSum <size_of_array>");
            return;
        }

        // Get the size of the array from the command-line argument
        int n = Integer.parseInt(args[0]);
        if (n <= 0) {
            System.out.println("Ukuran array harus positif.");
            return;
        }

        // Initialize the array and the prefix sum array
        arr = new int[n];
        prefix = new int[n];
        numThreads = 4; // Example thread count

        // Generate a random array
        Random rand = new Random();
        System.out.println("Array acak:");
        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt(100);  // Random number between 0 and 99
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        // Calculate the chunk size for each thread
        int chunkSize = n / numThreads;
        Thread[] threads = new Thread[numThreads];

        // Create threads and assign portions of the array to each thread
        for (int i = 0; i < numThreads; i++) {
            int start = i * chunkSize;
            int end = (i == numThreads - 1) ? n - 1 : (start + chunkSize - 1);
            threads[i] = new PrefixSumThread(start, end);
            threads[i].start();  // Start the thread
        }

        // Wait for all threads to finish
        for (int i = 0; i < numThreads; i++) {
            threads[i].join();
        }

        // Print the result of the prefix sum
        System.out.println("Prefix Sum:");
        for (int i = 0; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }
}
