/**
 * PROVA SCRITTA LABORATORIO TRACCIA 2: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. il master thread deve generare una matrice A,
 *    e leggere uno scalare alpha
 * 
 * 2. i core thread devono effettuare l’operazione B = A + alpha
 * 
 * 3. i core thread devono effettuare la trasposta di B
 * 
 * 4. i core thread dovevano stampare la loro porzione
 *    (quella che hanno trasposto) e il master thread
 *    doveva stampare il tempo di esecuzione
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAXVALUE 8
#define C_ROW M
#define C_COL N

void allocationMatrix( int***, int, int );
void fillMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
void deallocationMatrix( int***, int );
int main() {

    int N, M; // Size of matrix
    
    int alpha; // Scalar
    int** A; // Matrix A
    int** B; // Matrix B Matrix x alpha
    int** C; // Matric C trasposta

    int i, j;
    double startTime, endTime;


    srand( time( NULL ) );

    startTime = omp_get_wtime();

    // 1
    #pragma omp master
    {
        // Il Matser thread genera la matrice A e la matrice B
        printf( "\nEnter row of matrix N: " );
        scanf( "%d", &N );
        printf( "\nEnter column of matrix N: " );
        scanf( "%d", &M );
        printf( "\nEnter scalar alpha: " );
        scanf( "%d", &alpha );
        allocationMatrix( &A, N, M );
        allocationMatrix( &B, N, M );
        allocationMatrix( &C, C_ROW, C_COL );
        fillMatrix( &A, N, M );
        // Legge(?) uno scalare alpha
        printf( "\nAlpha: %d", alpha );
        printMatrix( A, N, M, "Matrix A" );
    }

    // 2
    #pragma omp parallel for private(i,j) shared(N,M,A,alpha,B)
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < M; j++ ) {
            // i core thread devono effettuare l’operazione B = A + alpha
            B[i][j] = A[i][j] + alpha;
        }
    }

    // 3
    #pragma omp parallel for private(i,j) shared(N,M,C,B)
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < M; j++ ) {
            // i core thread devono effettuare la trasposta di B
            C[j][i] = B[i][j];
        }
    }

    // Verifica
    printMatrix( C, C_ROW, C_COL, "Matrix C" );

    // 4
    printf( "\nC:" );
    #pragma omp parallel private(i,j) shared(C,N,M)
    {
        #pragma omp for
        for ( i = 0; i < N; i++ ) {
            printf( "\nThread %d trasponde: ", omp_get_thread_num() );
            for ( j = 0; j < M; j++ ) {
                // i core thread dovevano stampare la loro porzione
                printf( "%d ", C[j][i] );
            }
            printf( "\n" );
        }

        #pragma omp master
        {
            endTime = omp_get_wtime();
            // Il master thread doveva stampare il tempo di esecuzione
            printf( "\nTempo di esecuzione: %lf", endTime - startTime );
        }
    }

    deallocationMatrix( &A, N );
    deallocationMatrix( &B, N );
    deallocationMatrix( &C, C_ROW );
    printf( "\n" );
    return 0;
}

void allocationMatrix( int*** matrix, int N, int M ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
    for ( int i = 0; i < N; i++ )
        ( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );
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

void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
}