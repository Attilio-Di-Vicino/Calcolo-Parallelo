#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void printVector( float*, int, char[] );
int main() {

    int i, N, t, nloc, indice, r, id, step;
    float *a, *b, *c;

    srand( time( NULL ) );

    printf( "\nInserire N:" );
    scanf( "%d", &N );

    // allocazione
    a = ( float * ) calloc( N, sizeof( float ) );
    b = ( float * ) calloc( N, sizeof( float ) );
    c = ( float * ) calloc( N, sizeof( float ) );

    // lettura
    for ( i = 0; i < N; i++ )
        a[i] = rand() % 100 + 1;

    for ( i = 0; i < N; i++ )
        b[i] = rand() % 100 + 1;

    // Stampa 
    printVector( a, N, "Vector A:" );
    printVector( b, N, "Vector B:" );

    #pragma omp parallel private(nloc, i, indice, id, step) shared(a, b, c, r)
    { // se piu di un’istruzione
        
        t = omp_get_num_threads();
        id = omp_get_thread_num();
        nloc = N / t;
        r = N % t;

        if ( id < r ) {
            nloc++;
            step = 0;
        } else {
            step = r;
        }

        printf( "sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc );
        for ( i = 0; i < nloc; i++ )
        {
            indice = i + nloc * omp_get_thread_num() + step;
            c[ indice ] = a[ indice ] + b[ indice ];
        }

    } // fine direttiva

    // stampa finale
    printVector( c, N, "Vector C:" );
    
    printf( "\n" );
    return 0;
}

void printVector( float* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%f ", a[i] );
    printf( "\n" );
}
