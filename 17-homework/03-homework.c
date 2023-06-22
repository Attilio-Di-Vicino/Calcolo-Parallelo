/**
 * Implementare un codice parallelo per l’ambiente multicore che costruisca una matrice,
 * impiegando la 3 strategia per la distribuzione del dominio 2D 
 * (suddivisione del lavoro per righeColonne)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 16
#define M 16
#define MAXVALUE 9

int main() {
    int** matrix;
    int numThreads;
    int id;
    int startRow;
    int startCol;

    srand( time( NULL ) );

    matrix = ( int** ) calloc( N, sizeof( int* ) );

    #pragma omp parallel for shared(matrix)
    for ( int i = 0; i < N; i++ )
        matrix[i] = ( int* ) calloc( M, sizeof( int ) );
    
    // Da correggere
    #pragma omp parallel for shared(matrix)
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            matrix[i][j] = omp_get_thread_num();
        }
    }

    printf( "\nMatrix:\n" );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }

    return 0;
}