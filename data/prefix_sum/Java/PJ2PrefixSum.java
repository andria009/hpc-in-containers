import edu.rit.pj2.Loop;
import edu.rit.pj2.Task;
import java.util.Random;
import java.util.concurrent.atomic.AtomicLongArray;

public class PJ2PrefixSum extends Task {
    // Chunk size for parallel processing
    private static final int CHUNK_SIZE = 1000;

    public void main(String[] args) throws Exception {
        // Check if the array size argument is provided
        if (args.length != 1) {
            System.out.println("Usage: java pj2 PJ2PrefixSum <size_of_array>");
            terminate(1);
            return;
        }

        // Get the array size from execution arguments
        int n = Integer.parseInt(args[0]);

        // Validate input
        if (n <= 0) {
            System.out.println("Array size must be positive.");
            terminate(1);
            return;
        }

        long[] arr = new long[n];
        long[] prefix = new long[n];

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

        // Calculate prefix sum in parallel
        parallelPrefixSum(arr, prefix, n);

        // Display the prefix sum result (last 10 elements)
        System.out.println("Prefix Sum [last 10 elements]:");
        for (int i = n - 10; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }

    // Function to calculate Prefix Sum in parallel
    private void parallelPrefixSum(long[] arr, long[] prefix, int n) throws Exception {
        // Step 1: Calculate partial sums for each chunk
        final int numChunks = (n + CHUNK_SIZE - 1) / CHUNK_SIZE;
        final AtomicLongArray partialSums = new AtomicLongArray(numChunks);

        parallelFor(0, numChunks - 1).exec(new Loop() {
            public void run(int chunkIndex) {
                long sum = 0;
                int start = chunkIndex * CHUNK_SIZE;
                int end = Math.min(start + CHUNK_SIZE, n);
                for (int i = start; i < end; i++) {
                    sum += arr[i];
                }
                partialSums.set(chunkIndex, sum);
            }
        });

        // Step 2: Calculate prefix sums of partial sums
        for (int i = 1; i < numChunks; i++) {
            partialSums.set(i, partialSums.get(i) + partialSums.get(i - 1));
        }

        // Step 3: Calculate final prefix sums
        parallelFor(0, numChunks - 1).exec(new Loop() {
            public void run(int chunkIndex) {
                long basePrefixSum = chunkIndex > 0 ? partialSums.get(chunkIndex - 1) : 0;
                int start = chunkIndex * CHUNK_SIZE;
                int end = Math.min(start + CHUNK_SIZE, n);
                long sum = basePrefixSum;
                for (int i = start; i < end; i++) {
                    sum += arr[i];
                    prefix[i] = sum;
                }
            }
        });
    }

    protected static int coresRequired() {
        return Runtime.getRuntime().availableProcessors();
    }
}