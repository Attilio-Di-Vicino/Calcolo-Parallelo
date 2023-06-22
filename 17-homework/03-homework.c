/**
 * Implementare un codice parallelo per l’ambiente multicore che costruisca una matrice,
 * impiegando la 3 strategia per la distribuzione del dominio 2D 
 * (suddivisione del lavoro per righeColonne)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 8
#define M 16
#define MAXVALUE 9

int main() {
    int** matrix;

    srand( time( NULL ) );

    matrix = ( int** ) calloc( M, sizeof( int* ) );

    #pragma omp parallel for shared(matrix)
    for ( int i = 0; i < M; i++ )
        matrix[i] = ( int* ) calloc( N, sizeof( int ) );
    
    #pragma omp parallel for shared(matrix)
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            printf( "\nThread %d inserisce nella riga %d, colonna %d", omp_get_thread_num(), j, i );
            matrix[i][j] = rand() % MAXVALUE + 1;
        }
    }

    printf( "\nMatrix:\n" );
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }

    return 0;
}