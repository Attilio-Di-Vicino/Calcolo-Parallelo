#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAXVALUE 1000

int main( int argc, char* argv[] ) {

    int i, j, N, M, alpha, beta, nThreads;
    double *A, *b , *a , *R;
    double p = 0.00f;
    double t0, t1, tempotot;
    int ops = 0; // contatore relativo al numero totale di operazioni eseguite

    srand( time( NULL ) );

    if ( argc != 6 ) {
        printf( "\nusage: %s <#nThreads> <#M> <#N> <alpha> <beta>\n", argv[0] );
        exit( EXIT_FAILURE );
    }

    nThreads = atoi( argv[1] );
    M = atoi( argv[2] );
    N = atoi( argv[3] );
    alpha = atoi( argv[4] );
    beta = atoi( argv[5] );

    // Controllo divisibilità
    if ( M % 2 != 0 ) {
        printf( "\nusage: %s <#nThreads> <#M even> <#N> <alpha> <beta>\n", argv[0] );
        exit( EXIT_FAILURE );
    }

    // Allocazioni dinamiche
    A = ( double* ) malloc( M * N * sizeof( double ) );
    b = ( double* ) malloc( N * sizeof( double ) );
    a = ( double* ) malloc( M * sizeof( double ) );
    R = ( double* ) calloc( M, sizeof( double ) );

    // Generazioni numeri pseudo-casuali
    for( i = 0; i < M; i++ ) {
        a[i] = ( double ) ( rand() % MAXVALUE + 1 ) / MAXVALUE;
        for( j = 0; j < N; j++ )
            A[ i * N + j ] = ( double ) ( rand() % MAXVALUE + 1 ) / MAXVALUE;
    }
    for( i = 0; i < N; i++ )
        b[i] = ( double ) ( rand() % MAXVALUE + 1 ) / MAXVALUE;

    t0 = omp_get_wtime();

    #pragma omp parallel for schedule(static) shared(N,M,A,b,a,R,alpha,beta) private(i,j) num_threads(nThreads)
    for ( i = 0; i < M; i++ ) {
        for ( j = 0; j < N; j++ ) {
            R[i] += alpha * A[ i * N + j ] * b[j];
            #pragma omp critical
            ops++;
        }
        R[i] += ( a[i] * beta );
    }

    #pragma omp parallel sections shared(N,M,A,b,a,R,alpha,beta) private(i,j) num_threads(2)
    {
        #pragma omp section
        {
            for ( i = 0; i < M; i++ ) {
                for ( j = 0; j < N; j++ ) {
                    R[i] += alpha * A[ i * N + j ] * b[j];
                    // #pragma omp critical
                    ops++;
                }
            }
        }

        #pragma omp section
        {
            for ( i = 0; i < M; i++ )
                R[i] += ( a[i] * beta );
        }
    }

    #pragma omp parallel for shared (R,M,a) private(i) reduction(*:p) num_threads(nThreads)
    for( i = 0; i < M; i++ ) 
        p *= R[i];

    t1 = omp_get_wtime();
    tempotot = t1 - t0;

    printf( "\nR: " );
    for( i = 0; i < M; i++ ) 
        printf( "%lf ", R[i] );
    printf( "\n" );

    printf( "\nOps: %d\n", ops );
    printf( "\nElapsed Time: %lf sec\n", tempotot );

    free(A);
    free(b);
    free(a);
    free(R);

    exit( EXIT_SUCCESS );
}