/**
 * FULLPARALLEL:
 * 
 * Somma di due vettori di lunghezza N
*/

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "../dataTest/data.c"

#define SIZE 100
#define MAXVALUE 99
#define OVER -1

void printVector( const int vector[], const int size, const char* name ) {
    // Stampa dell'array
    printf( "\n%s: ", name );
    for ( int i = 0; i < size; i++ )
        printf( "%d ", vector[i] );
    printf( "\n" );
}

int main() {

    int vectorA[ SIZE ];
    int vectorB[ SIZE ];
    int vectorC[ SIZE ];

    srand( time( NULL ) );

    for ( int i = 0; i < SIZE; i++ ) {
        vectorA[i] = twoVectorTest.vectorA[i];
        vectorB[i] = twoVectorTest.vectorB[i];
        vectorC[i] = OVER;
    }

    printVector( vectorA, SIZE, "Vector A" );
    printVector( vectorB, SIZE, "Vector B" );
    printVector( vectorC, SIZE, "Vector C" );

    #pragma omp parallel for shared(vectorA,vectorB,vectorC)
    for ( int i = 0; i < SIZE; i++ )
        vectorC[i] = vectorA[i] + vectorB[i];

    printVector( vectorC, SIZE, "Computed Vector C" );
    printVector( twoVectorTest.vectorC, SIZE, "Result Vector C" );

    return 0;
}