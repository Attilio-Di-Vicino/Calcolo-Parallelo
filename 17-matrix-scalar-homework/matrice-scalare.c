/**
 * Prodotto matrice per scalare utilizzando la prima strategia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void printMatrix( int*, int, char[] );
int main() {

    int N;
    int scalar;
    int i, j;
    double startTime, endTime;
    
    printf( "Please, enter the size of matrix: " );
    scanf( "%d", &N );

    printf( "Please, enter the scalar: " );
    scanf( "%d", &scalar );
    
    // Allocazione dinamica della matrice
    int* matrix = ( int* ) calloc( N * N, sizeof( int* ) );
    
    // Inizializzazione della matrice
    for ( i = 0; i < N; i++ )
        for ( j = 0; j < N; j++ )
            matrix[ i * N + j ] = i * j;

    // Stampa della matrice
    printMatrix( matrix, N, "Before Matrix" );

	// Tempo iniziale 
	startTime = omp_get_wtime();

	#pragma omp parallel for shared(matrix,N) private(i,j) schedule(guided)
    for( i = 0; i < N; i++ )
        for( j = 0; j < N; j++ )
            matrix[ i * N + j ] = matrix[ i * N + j ] * scalar;
		
		
	// Tempo finale 
	endTime = omp_get_wtime();

	// Stampe
    printMatrix( matrix, N, "After Matrix" );

    printf( "\nTempo iniziale: %lf", startTime );
	printf( "\nTempo finale: %lf", endTime );
    printf( "\nTempo totale: %lf \n", endTime - startTime );
        
    return 0;
}

void printMatrix( int* matrix, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            int value = matrix[ i * N + j ];
            if ( value >= 10 && value < 100 )
                printf( "%d   ", value );
            else if ( value >= 100 )
                printf( "%d  ", value );
            else
                printf( "%d    ", value );
        }
        printf( "\n" );
    }       
}
