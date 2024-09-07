import java.util.Random;

public class PrefixSum {

    // Function to calculate the prefix sum
    public static void prefixSum(int[] arr, int[] prefix) {
        prefix[0] = arr[0]; // First element

        // Calculating the prefix sum
        for (int i = 1; i < arr.length; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
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

        // Create a random array
        int[] arr = new int[n];
        int[] prefix = new int[n];
        Random rand = new Random();

        // Fill the array with random numbers and display it
        System.out.println("Random array:");
        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt(100); // Random numbers between 0 and 99
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        // Calculate the prefix sum
        prefixSum(arr, prefix);

        // Display the prefix sum result
        System.out.println("Prefix Sum:");
        for (int i = 0; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }
}
