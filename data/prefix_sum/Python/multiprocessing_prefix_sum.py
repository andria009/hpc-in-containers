import sys
import random
import multiprocessing as mp

def compute_partial_prefix_sum(arr, start_idx, result):
    """
    Function to compute the prefix sum for a subarray.
    The result is stored in the shared list `result`.
    """
    prefix_sum = arr[0]
    result[start_idx] = prefix_sum

    for i in range(1, len(arr)):
        prefix_sum += arr[i]
        result[start_idx + i] = prefix_sum

def multiprocessing_prefix_sum(arr):
    n = len(arr)
    num_workers = mp.cpu_count()  # Number of processes to use
    chunk_size = (n + num_workers - 1) // num_workers  # Divide the array into chunks

    # Create a shared memory array to store the result
    manager = mp.Manager()
    result = manager.list([0] * n)

    # Create processes for each chunk
    processes = []
    for i in range(num_workers):
        start_idx = i * chunk_size
        end_idx = min((i + 1) * chunk_size, n)
        chunk = arr[start_idx:end_idx]
        p = mp.Process(target=compute_partial_prefix_sum, args=(chunk, start_idx, result))
        processes.append(p)
        p.start()

    # Wait for all processes to finish
    for p in processes:
        p.join()

    # Apply correction to the result array to ensure the prefix sum is correct across chunks
    for i in range(1, num_workers):
        start_idx = i * chunk_size
        if start_idx < n:
            correction = result[start_idx - 1]
            for j in range(start_idx, min((i + 1) * chunk_size, n)):
                result[j] += correction

    return list(result)

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

    # Calculate prefix sum using multiprocessing
    prefix = multiprocessing_prefix_sum(arr)

    # Display the prefix sum result (last 10 elements)
    print("Prefix Sum [last 10 elements]:")
    print(*prefix[-10:])

    return 0

if __name__ == "__main__":
    sys.exit(main())
