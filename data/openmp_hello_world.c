#include <stdio.h>
#include <omp.h>
#include <unistd.h>  // for gethostname
#include <limits.h>  // for HOST_NAME_MAX

int main() {
    // Variable to store the hostname
    char hostname[HOST_NAME_MAX];
    
    // Get the hostname of the machine
    gethostname(hostname, HOST_NAME_MAX);
    
    // Parallel region starts here
    #pragma omp parallel
    {
        // Each thread will execute this code block
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        
        printf("Hello World from thread %d out of %d threads running on %s\n", thread_id, num_threads, hostname);
    }

    return 0;
}

