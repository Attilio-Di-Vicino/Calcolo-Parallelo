/**
 * PROVA SCRITTA LABORATORIO TRACCIA 1: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. Ogni core deve generare una matrice A di dimensione N/np x M,
 *    mentre solo il core master deve leggere un vettore b di lunghezza M
 * 
 * 2. Tutti i core devono calcolare localmente il prodotto c = A x b
 * 
 * 3. Quindi, i core devono organizzarsi per determinare il massimo
 *    valore tra tutti gli elementi dei vettori locali c e il massimo 
 *    globale tra tutti i vettori locali c
 * 
 * 4. Infine, il core master deve stampare il valore massimo
 *    globale trovato ed il tempo d'esecuzione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAXVALUE 8

void fillMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
void printVector( int*, int, char[] );
void deallocationMatrix( int***, int );
int main() {

    int N, M; // Size of matrix
    int** A; // Matrix A
    int** C; // Matric C
    int* b;
    int np; // Core

    int i, j;
    double startTime, endTime;


    srand( time( NULL ) );

    printf( "\nEnter number of core: " );
    scanf( "%d", &np );

    startTime = omp_get_wtime();

    // 1
    #pragma omp parallel private(i,j) shared(A,N,M,b) num_threads(np)
    {
        #pragma omp master
        {
            printf( "\nEnter row of matrix N: " );
            scanf( "%d", &N );

            printf( "\nEnter column of matrix M: " );
            scanf( "%d", &M );

            A = ( int** ) calloc( N, sizeof( int* ) );
            C = ( int** ) calloc( np, sizeof( int* ) );
        }

        #pragma omp barrier

        // Ogni core deve generare una matrice A di dimensione N/np x M
        #pragma omp for
        for ( i = 0; i < N; i++ ) {
            A[i] = ( int* ) calloc( M, sizeof( int ) );
            C[i] = ( int* ) calloc( M, sizeof( int ) );
        }

        #pragma omp barrier
        
        #pragma omp master
        {
            // il core master deve leggere un vettore b di lunghezza M
            b = ( int* ) calloc( M, sizeof( int ) );
            for ( i = 0; i < M; i++ )
                b[i] = rand() % MAXVALUE + 1;
            
            fillMatrix( &A, N, M );
            printMatrix( A, N, M, "Matrix A" );
            printVector( b, M, "Vector B" );
        }        
    } 

    // 2
    #pragma omp parallel for private(i,j) shared(A,b,C) num_threads(np)
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < M; j++ ) {
            // Tutti i core devono calcolare localmente il prodotto c = A x b
            C[ omp_get_thread_num() ][j] += A[i][j] * b[j];
        }
    }

    // Verifica
    printMatrix( C, np, M, "Matrix C" );

    int maximum = 0;
    int localMax;
    int id;

    // 3
    #pragma omp parallel private(id,j,localMax) shared(maximum,C) num_threads(np)
    {
        localMax = 0;
        id = omp_get_thread_num();
        for ( j = 0; j < M; j++ )
            if ( localMax < C[ id ][j] )
                localMax = C[ id ][j];
        
        #pragma omp barrier

        if ( localMax > maximum )
            maximum = localMax;
    }

    // 4
    #pragma omp master
    {
        endTime = omp_get_wtime();
        // il core master deve stampare il valore massimo
        printf( "\nMaximum: %d", maximum );
        // Il master thread doveva stampare il tempo di esecuzione
        printf( "\nTempo di esecuzione: %lf", endTime - startTime );
    }

    // deallocationMatrix( &A, N );
    deallocationMatrix( &C, np );
    free( b );
    printf( "\n" );
    return 0;
}

void fillMatrix( int*** matrix, int N, int M ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
}

void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
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

void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
}