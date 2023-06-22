#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void printVector( float*, int, char[] );
int main() {
    int i,N;
    float *a, *b, result;

    srand( time( NULL ) );

    printf( "\nInserire N: " );
    scanf( "%d", &N );
    
    // allocazione
    a = ( float* ) calloc( N, sizeof( float ) );
    b = ( float* ) calloc( N, sizeof( float ) );
    
    // Riempimento
    for ( i = 0; i < N; i++ )
        a[i] = rand() % 100 + 1;
    
    for ( i = 0; i < N; i++ )
        b[i] = rand() % 100 + 1;

    // Stampa 
    printVector( a, N, "Vector A:" );
    printVector( b, N, "Vector B:" );
    
    // direttiva nella versione più semplice possibile
    #pragma omp parallel for private(i) shared (a,b) reduction(+:result)
    for ( i = 0; i < N; i++ )
        result += ( a[i] * b[i] );
    
    printf( "\nRisultato = %f\n",result );
    
    // una buona abitudine è liberare sempre la memoria allocata alla fine del codice!
    free(a);
    free(b);
}

void printVector( float* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%f ", a[i] );
    printf( "\n" );
}