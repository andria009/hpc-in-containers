import java.util.Random;

public class PrefixSum {

    // Function to calculate Prefix Sum
    public static void prefixSum(long[] arr, long[] prefix, int n) {
        prefix[0] = arr[0]; // Initialize the first element of the prefix sum

        // Calculate prefix sum for each element
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + arr[i]; // Each element is the cumulative sum of the previous elements
        }
    }

    public static void main(String[] args) {
        // Check if the array size argument is provided
        if (args.length != 1) {
            System.out.println("Usage: java PrefixSum <size_of_array>");
            return;
        }

        // Get the array size from execution arguments
        int n = Integer.parseInt(args[0]);

        // Validate input
        if (n <= 0) {
            System.out.println("Array size must be positive.");
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

        // Calculate prefix sum
        prefixSum(arr, prefix, n);

        // Display the prefix sum result (last 10 elements)
        System.out.println("Prefix Sum [last 10 elements]:");
        for (int i = n - 10; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }
}
