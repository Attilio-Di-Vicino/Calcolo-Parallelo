#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void printVector( float*, int, char[] );
int main() {

    int i, N, t, nloc, rest, id, step;
    float sumtot, sum, *a;
    
    sumtot = 0;

    srand( time( NULL ) );
    
    printf( "\nInserire N:" );
    scanf( "%d", &N );

    a = ( float* ) calloc( N, sizeof( float ) );

    // lettura
    for ( i = 0; i < N; i++ )
        a[i] = rand() % 100 + 1;
    
    // Stampa 
    printVector( a, N, "Vector A:" );

    #pragma omp parallel private(sum,nloc,i,step,id) shared(sumtot,rest)
    { // se piu di un’istruzione
        
        t = omp_get_num_threads();
        id = omp_get_thread_num();
        nloc = N / t;
        rest = N % t;

        if ( id < rest ) {
            nloc++;
            step = 0;
        } else {
            step = rest;
        }

        printf( "sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc );
        sum = 0;
        
        for( i = 0; i < nloc; i++ )
        {
            sum = sum + a [ i + nloc * omp_get_thread_num() + step ];
        }

        // Avviene gia in sezione critica la seguente somma
        sumtot += sum;

    } //fine direttiva

    printf( "Somma totale: %f\n", sumtot );
}

void printVector( float* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%f ", a[i] );
    printf( "\n" );
}