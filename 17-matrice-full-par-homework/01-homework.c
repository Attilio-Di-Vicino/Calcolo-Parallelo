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
#define MAXVALUE 9

int main() {
    int** matrix;

    srand( time( NULL ) );

    matrix = ( int** ) calloc( N, sizeof( int* ) );

    #pragma omp parallel for shared(matrix)
    for ( int i = 0; i < N; i++ )
        matrix[i] = ( int* ) calloc( M, sizeof( int ) );
    
    #pragma omp parallel for shared(matrix)
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            printf( "\nThread %d inserisce nella riga %d, colonna %d", omp_get_thread_num(), i, j );
            matrix[i][j] = rand() % MAXVALUE + 1;
        }
    }

    printf( "\nMatrix:\n" );
    for ( int i = 0; i < N; i++ ){
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }

    return 0;
}