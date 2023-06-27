/**
 * Implementare un codice parallelo per l’ambiente multicore che costruisca una matrice,
 * impiegando la 3 strategia per la distribuzione del dominio 2D 
 * (suddivisione del lavoro per righeColonne )
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define N 8
#define M 16
#define MAXVALUE 9
#define ROW ( N / ( numThreads / 2 ) )
#define COL ( M / ( numThreads / 2 ) )

int main() {
    int* matrix;
    int i,j;

    srand( time( NULL ) );

    matrix = ( int* ) malloc( N * M * sizeof( int ) );
    for ( i = 0; i < N * M; i++ )
        matrix[i] = -1;

    int numThreads = 4;

    // Funziona solo per 4 thread
    #pragma omp parallel num_threads(numThreads) shared(matrix) private(i,j)
    {
        int threadID = omp_get_thread_num();
        int rowStart = ( threadID / 2 ) * ROW;
        int colStart = ( threadID % 2 ) * COL;

        for ( i = rowStart; i < rowStart + ROW; i++ ) {
            for ( j = colStart; j < colStart + COL; j++ ) {
                matrix[ i * M + j ] = threadID;
            }
        }
    }

    printf( "\nMatrix:\n" );
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < M; j++ )
            printf( "%d    ", matrix[i * M + j] );
        printf( "\n" );
    }

    return 0;
}