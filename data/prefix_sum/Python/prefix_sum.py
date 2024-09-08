import sys
import random

def prefix_sum(arr):
    prefix = [0] * len(arr)
    prefix[0] = arr[0]  # Initialize the first element of the prefix sum
    # Calculate prefix sum for each element
    for i in range(1, len(arr)):
        prefix[i] = prefix[i - 1] + arr[i]  # Each element is the cumulative sum of the previous elements
    return prefix

def main():
    # Check if the array size argument is provided
    if len(sys.argv) != 2:
        print(f"Usage: python {sys.argv[0]} <size_of_array>")
        return -1

    # Get the array size from execution arguments
    try:
        n = int(sys.argv[1])
    except ValueError:
        print("Array size must be an integer.")
        return -1

    # Validate input
    if n <= 0:
        print("Array size must be positive.")
        return -1

    # Initialize random number generator
    random.seed(42)

    # Fill the array with random numbers between 0 and 99
    arr = [random.randint(0, 99) for _ in range(n)]

    # Display the last 10 elements of the random array
    print("Random array [last 10 elements]:")
    print(*arr[-10:])

    # Calculate prefix sum
    prefix = prefix_sum(arr)

    # Display the prefix sum result (last 10 elements)
    print("Prefix Sum [last 10 elements]:")
    print(*prefix[-10:])

    return 0

if __name__ == "__main__":
    sys.exit(main())