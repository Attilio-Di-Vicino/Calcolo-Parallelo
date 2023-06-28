/**
 * Assegnata una matrice di dimensione N×N, estrarre in parallelo gli elementi
 * della diagonale principale e ricopiarli in un vettore, quindi calcolarne il
 * massimo, con una procedura parallela
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAXVALUE 100
#define OVER -1
#define MAX_NUM_THREADS 100

void allocationMatrixVector( int***, int**, int );
void fillMatrixVector( int***, int**, int );
void printMatrix( int**, int, char[] );
void printVector( int*, int, char[] );
void deallocationMatrixVector( int***, int**, int );
int main() {
    
    int N;
    int** matrix;
    int* vector;
    int maximum;
    int numThread;
    int i,j;

    srand( time( NULL ) );
    printf( "\nPlease, enter N: " );
    scanf( "%d", &N );
    printf( "\nN: %d", N );

    allocationMatrixVector( &matrix, &vector, N );
    fillMatrixVector( &matrix, &vector, N );
    printMatrix( matrix, N, "Matrix:" );
    printVector( vector, N, "Before Vector:" );

    if ( N > MAX_NUM_THREADS )
        numThread = MAX_NUM_THREADS;
    else 
        numThread = N;

    // Estrazione della diagonale
    #pragma omp parallel for schedule(static) private(i) shared(matrix,vector,N) num_threads(numThread)
    for ( i = 0; i < N; i++ ) {
        vector[i] = matrix[i][i];
    }

    printVector( vector, N, "After Vector:" );

    maximum = OVER;
    // Ricerca del massimo
    #pragma omp parallel for reduction(max:maximum) schedule(static) private(i) shared(vector,N) num_threads(numThread)
    for ( i = 0; i < N; i++ ) {
        if ( vector[i] > maximum )
            maximum = vector[i];
    }

    printf( "\nMaximum: %d", maximum );

    deallocationMatrixVector( &matrix, &vector, N );
    printf( "\n" );
    return 0;
}

void allocationMatrixVector( int*** matrix, int** vector, int N ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
    for ( int i = 0; i < N; i++ )
        ( *matrix )[i] = ( int* ) calloc( N, sizeof( int ) );
    *vector = ( int* ) calloc( N, sizeof( int ) );
}

void fillMatrixVector( int*** matrix, int** vector, int N ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < N; j++ )
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
    for ( int i = 0; i < N; i++ )
        ( *vector )[i] = OVER;
}

void printMatrix( int** matrix, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < N; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

void printVector( int* vector, int N, char name[] ) {
    printf( "\n%s: ", name );
    for ( int i = 0; i < N; i++ )
        printf( "%d ", vector[i] );
    printf( "\n" );
}

void deallocationMatrixVector( int*** matrix, int** vector, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
    free( *vector );
}