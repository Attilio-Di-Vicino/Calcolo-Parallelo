/**
 * Implementare un codice parallelo per l’ambiente multicore che costruisca una matrice,
 * impiegando la 1 strategia per la distribuzione del dominio 2D 
 * (suddivisione del lavoro per righe)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 16
#define M 16

int main() {
    int** matrix;
    int i,j;

    matrix = ( int** ) calloc( N, sizeof( int* ) );

    #pragma omp parallel for shared(matrix) private(i)
    for ( i = 0; i < N; i++ )
        matrix[i] = ( int* ) calloc( M, sizeof( int ) );
    
    #pragma omp parallel for shared(matrix) private(i,j)
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < M; j++ ) {
            matrix[i][j] = omp_get_thread_num();
        }
    }

    printf( "\nMatrix:\n" );
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }

    return 0;
}