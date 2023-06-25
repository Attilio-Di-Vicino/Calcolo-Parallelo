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
    int i;

    srand( time( NULL ) );

    // In questo caso vengono utilizzati dei dati
    // i quali gia si conoscono i risultati
    for ( int i = 0; i < SIZE; i++ ) {
        vectorA[i] = twoVectorTest.vectorA[i];
        vectorB[i] = twoVectorTest.vectorB[i];
        vectorC[i] = OVER;
    }

    printVector( vectorA, SIZE, "Vector A" );
    printVector( vectorB, SIZE, "Vector B" );
    printVector( vectorC, SIZE, "Vector C" );

    /**
     * La somma di due vettori di lunghezza N è un nucleo computazionale
     * il quale viene definito Full Parallel, di conseguenza
     * non ci sono collezioni di dati.
     * Di seguito viene mostrato un blocco di codice parallelo
     * utilizzato la direttiva 'for', la quale ci permette di 
     * distribuire in automatico le celle del vettore ai thread.
    */
    #pragma omp parallel for shared(vectorA,vectorB,vectorC) private(i)
    for ( i = 0; i < SIZE; i++ )
        vectorC[i] = vectorA[i] + vectorB[i];

    printVector( vectorC, SIZE, "Computed Vector C" );
    printVector( twoVectorTest.vectorC, SIZE, "Result Vector C" );

    return 0;
}