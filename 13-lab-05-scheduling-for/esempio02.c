#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main() {
    
    int n_threads, id_thread, i;
    
    omp_set_num_threads(3);
    
    #pragma omp parallel for private(id_thread)
    for ( i = 0; i <= 4; i++ ) {
        id_thread = omp_get_thread_num();
        printf( "Iterazione %d del thread %d\n", i, id_thread );
    }
    
    return 0;
}