#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAXVALUE 100

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
        a[i] = rand() % MAXVALUE + 1;
    
    for ( i = 0; i < N; i++ )
        b[i] = rand() % MAXVALUE + 1;

    // Stampa 
    printVector( a, N, "Vector A:" );
    printVector( b, N, "Vector B:" );
    
    // direttiva nella versione più semplice possibile
    /**
     * In questo caso si sta lavorando su due vettori per eseguire un prodotto scalare
     * di conseguenza inizialmente andremo a moltiplicare ogni elemento del primo vettore
     * con il corrispettivo elemento del secondo vettore, quindi analogamente alla somma 
     * di due vettori ( II Nucleo computazionale ), di conseguenza anche esso
     * è un algoritmo full parallel e non c'è collezione dei dati;
     * successivamente, andiamo ad eseguire la somma degli elementi
     * risultanti dal prodotto, come nella somma di N numeri ( I Nucleo computazionale ),
     * che sappiamo non essere un algorimto full parallel, di coseguenza dobbiamo adottare
     * una strategia conveniente che ci permette di gestire questa situazione.
     * In questo caso utilizziamo la seconda strategia attraverso la clausola reduction.
    */
    #pragma omp parallel for private(i) shared (a,b) reduction(+:result)
    for ( i = 0; i < N; i++ )
        result += a[i] * b[i];
    
    printf( "\nRisultato = %f\n",result );
    
    // una buona abitudine è liberare sempre la memoria allocata alla fine del codice!
    free(a);
    free(b);

    return 0;
}

void printVector( float* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%f ", a[i] );
    printf( "\n" );
}