import edu.rit.pj2.Task;
import edu.rit.pj2.Loop;

public class PJ2PrefixSum extends Task {

    public void main(String[] args) throws Exception {
        // Validate the input arguments
        if (args.length != 1) {
            System.out.println("Usage: java pj2 PJ2PrefixSum <size_of_array>");
            return;
        }

        // Parse the size of the array
        int n = Integer.parseInt(args[0]);
        if (n <= 0) {
            System.out.println("Array size must be positive.");
            return;
        }

        // Create an array and fill it with random values
        int[] arr = new int[n];
        int[] prefix = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = (int) (Math.random() * 100);
        }

        // Print the original array
        System.out.println("Array acak:");
        for (int i = 0; i < n; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        // Use PJ2 to parallelize the prefix sum calculation
        parallelFor(0, n - 1).exec(new Loop() {
            public void run(int i) {
                if (i == 0) {
                    prefix[i] = arr[i];
                } else {
                    prefix[i] = prefix[i - 1] + arr[i];
                }
            }
        });

        // Print the prefix sum
        System.out.println("Prefix Sum:");
        for (int i = 0; i < n; i++) {
            System.out.print(prefix[i] + " ");
        }
        System.out.println();
    }

    // Specify the number of threads for this task
    public int threads() {
        return 4;  // You can change this based on your system
    }
}

