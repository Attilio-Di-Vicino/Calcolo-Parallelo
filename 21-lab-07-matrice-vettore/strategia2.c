/**
 * Algoritmo per il prodotto Matrice
 * per vettore in ambiente MIMD_SM
 * utilizzando la strategia 2 per blocchi colonna 
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 16
#define M 8
#define VECTORSIZE N
#define RESULTVECTORSIZE M
#define MAXVALUE 9

void allocationMatrixVector( int***, int**, int** );
void fillMatrixVector( int***, int**, int** );
void printMatrix( int**, char[] );
void printVector( int*, int, char[] );
void deallocationMatrixVector( int***, int**, int** );
int main() {
    int** matrix;
    int* vector;
    int* result;
    int i,j;

    srand( time( NULL ) );

    allocationMatrixVector( &matrix, &vector, &result );
    fillMatrixVector( &matrix, &vector, &result );

    printMatrix( matrix, "Matrix" );
    printVector( vector, VECTORSIZE, "Vector" );
    printVector( result, RESULTVECTORSIZE, "Result Vector before" );

    #pragma omp parallel for default(none) shared(matrix,vector,result) private(i,j)
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    printVector( result, RESULTVECTORSIZE, "Result Vector after" );
    deallocationMatrixVector( &matrix, &vector, &result );
    return 0;
}

void allocationMatrixVector( int*** matrix, int** vector, int** result ) {
    *matrix = ( int** ) calloc( M, sizeof( int* ) );
    for ( int i = 0; i < M; i++ )
        ( *matrix )[i] = ( int* ) calloc( N, sizeof( int ) );
    *vector = ( int* ) calloc( VECTORSIZE, sizeof( int ) );
    *result = ( int* ) calloc( RESULTVECTORSIZE, sizeof( int ) );
}

void fillMatrixVector( int*** matrix, int** vector, int** result ) {
    for ( int i = 0; i < M; i++ )
        for ( int j = 0; j < N; j++ )
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
    for ( int i = 0; i < VECTORSIZE; i++ )
        ( *vector )[i] = rand() % MAXVALUE + 1;
    for ( int i = 0; i < RESULTVECTORSIZE; i++ )
        ( *result )[i] = 0;
}

void printMatrix( int** matrix, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

void printVector( int* vector, int n, char name[] ) {
    printf( "\n%s: ", name );
    for ( int i = 0; i < n; i++ )
        printf( "%d ", vector[i] );
    printf( "\n" );
}

void deallocationMatrixVector( int*** matrix, int** vector, int** result ) {
    for ( int i = 0; i < M; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
    free( *vector );
    free( *result );
}