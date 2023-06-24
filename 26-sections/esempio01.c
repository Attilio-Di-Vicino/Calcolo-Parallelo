#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {

    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        printf( "\nHello world ONE!" );

        #pragma omp section
        printf( "\nHello world TWO!" );

        #pragma omp section
        printf( "\nHello world THREE!" );
    }

    printf( "\n" );
    exit( EXIT_SUCCESS );
}