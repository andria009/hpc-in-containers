import random
import sys

# Function to calculate prefix sum
def prefix_sum(arr):
    prefix = [0] * len(arr)
    prefix[0] = arr[0]  # First element

    # Calculate prefix sum
    for i in range(1, len(arr)):
        prefix[i] = prefix[i - 1] + arr[i]

    return prefix

def main():
    # Check if the array size argument is provided
    if len(sys.argv) != 2:
        print("Usage: python prefix_sum.py <size_of_array>")
        return

    try:
        # Get array size from input argument
        n = int(sys.argv[1])
    except ValueError:
        print("Array size must be a number.")
        return

    if n <= 0:
        print("Array size must be positive.")
        return

    # Generate a random array
    arr = [random.randint(0, 99) for _ in range(n)]
    print("Random array:", arr)

    # Calculate prefix sum
    result = prefix_sum(arr)
    print("Prefix Sum:", result)

if __name__ == "__main__":
    main()
