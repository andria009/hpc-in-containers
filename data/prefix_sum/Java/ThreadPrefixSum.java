import java.util.Random;

public class ThreadPrefixSum {

    private static int numThreads = 4;  // Set the number of threads to use
    private static long[] arr;
    private static long[] prefix;
    private static int n;

    // Thread class to calculate prefix sum for a chunk
    static class PrefixSumThread extends Thread {
        private int start, end;

        public PrefixSumThread(int start, int end) {
            this.start = start;
            this.end = end;
        }

        @Override
        public void run() {
            // Compute prefix sum for this thread's chunk
            for (int i = start; i < end; i++) {
                prefix[i] = prefix[i - 1] + arr[i];
            }
        }
    }

    // Function to calculate Prefix Sum using multiple threads
    public static void parallelPrefixSum() throws InterruptedException {
        // Start threads for each chunk of the array
        Thread[] threads = new Thread[numThreads];
        int chunkSize = (n + numThreads - 1) / numThreads; // Calculate chunk size

        // Start each thread for its respective portion of the array
        for (int i = 0; i < numThreads; i++) {
            int start = (i == 0) ? 1 : i * chunkSize;
            int end = Math.min((i + 1) * chunkSize, n);
            threads[i] = new PrefixSumThread(start, end);
            threads[i].start();
        }

        // Wait for all threads to finish
        for (Thread thread : threads) {
            thread.join();
        }

        // Correction phase: adjust each chunk's values based on the last value of the previous chunk
        for (int i = 1; i < numThreads; i++) {
            int start = i * chunkSize;
            long correction = prefix[start - 1];
            for (int j = start; j < Math.min((i + 1) * chunkSize, n); j++) {
                prefix[j] += correction;
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Check if the array size argument is provided
        if (args.length != 1) {
            System.out.println("Usage: java ThreadPrefixSum <size_of_array>");
            return;
        }

        // Get the array size from execution arguments
        n = Integer.parseInt(args[0]);

        // Validate input
        if (n <= 0) {
            System.out.println("Array size must be positive.");
            return;
        }

        arr = new long[n];
        prefix = new long[n];

        // Initialize random number generator
        Random rand = new Random(42);

        // Fill the array with random numbers between 0 and 99 and display the last 10 elements
        System.out.println("Random array [last 10 elements]:");
        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt(100); // Generate random numbers between 0 and 99
            if (i >= n - 10) {
                System.out.print(arr[i] + " ");
            }
        }
        System.out.println();

        // Initialize the first element of the prefix sum
        prefix[0] = arr[0];

        // Calculate prefix sum using multiple threads
        parallelPrefixSum();

        // Display the prefix sum result (last 10 elements)
        System.out.println("Prefix Sum [last 10 elements]:");
        for (int i = n - 10; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }
}
