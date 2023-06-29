/**
 * NOME: Attilio Di Vicino
 * MATRICOLA: 0124002347
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Costante utilizzata per il riempimento
// della matrice con numeri casuali
#define MAXVALUE 9

void allocationMatrix( int***, int, int );
void fillMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
void deallocationMatrix( int***, int );
int main() {

    int i, j; // Indici
    double startTime, endTime;

    int** matrixA; // Matrice A
    int N, M; // Size della matrice

    // Come seme per la generazioni di numeri
    // pseudo-casuali utilizzo l'orario corrente
    srand( time( NULL ) );

    // Tempo di inizio
    startTime = omp_get_wtime();

    #pragma omp master
    {
        printf( "\nEnter row of matrix N: " );
        scanf( "%d", &N );
        printf( "\nEnter column of matrix N: " );
        scanf( "%d", &M );
        allocationMatrix( &matrixA, N, M );
        fillMatrix( &matrixA, N, M );
        printMatrix( matrixA, N, M, "Matrix A" );
        deallocationMatrix( &matrixA, N );
    }

    #pragma omp master
    {
        // Tempo di fine
        endTime = omp_get_wtime();
        // Il master thread doveva stampare il tempo di esecuzione
        printf( "\nTempo di esecuzione: %lf", endTime - startTime );
    }

    printf( "\n" );
    return 0;
}

/**
 * Procedura utilizzata per l'allocazione della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
*/
void allocationMatrix( int*** matrix, int N, int M ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
    for ( int i = 0; i < N; i++ )
        ( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );
}

/**
 * Procedura utilizzata per il riempimento della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
*/
void fillMatrix( int*** matrix, int N, int M ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
}

/**
 * Procedura utilizzata per la stampa della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
 * @param name nome della matrice
*/
void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

/**
 * Procedura utilizzata per la deallocazione della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
*/
void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
}