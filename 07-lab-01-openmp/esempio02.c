#include <omp.h>
#include <stdio.h>

int main() {

    int id_thread, num_threads;

    #pragma omp parallel private(id_thread), shared(num_threads)
    {
        id_thread = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        printf( "Hello from thread %d, nthreads %d\n", id_thread, num_threads );
    }
    
    return 0;
}