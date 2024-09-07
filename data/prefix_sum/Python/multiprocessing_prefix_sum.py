import random
import sys
import multiprocessing as mp

# Function to calculate prefix sum in each chunk (section)
def prefix_sum_chunk(start, end, arr, prefix, lock):
    for i in range(start, end):
        with lock:
            if i == 0:
                prefix[i] = arr[i]  # First element
            else:
                prefix[i] = prefix[i - 1] + arr[i]

def main():
    # Check if the array size argument is provided
    if len(sys.argv) != 2:
        print("Usage: python prefix_sum_parallel.py <size_of_array>")
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

    # Create shared memory for the prefix array
    prefix = mp.Array('i', n)  # 'i' = integer
    lock = mp.Lock()  # Lock for synchronization

    # Determine the number of processes to use
    num_processes = mp.cpu_count()  # Number of cores on the CPU
    chunk_size = n // num_processes

    # Create and start processes
    processes = []
    for i in range(num_processes):
        start = i * chunk_size
        # If this is the last process, take the remaining elements
        end = n if i == num_processes - 1 else (i + 1) * chunk_size
        p = mp.Process(target=prefix_sum_chunk, args=(start, end, arr, prefix, lock))
        processes.append(p)
        p.start()

    # Wait for all processes to finish
    for p in processes:
        p.join()

    # Display the prefix sum result
    print("Prefix Sum:", list(prefix))

if __name__ == "__main__":
    main()
