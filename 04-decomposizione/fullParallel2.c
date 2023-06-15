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

    int nloc = 0;
    int step = 0;
    int rest = 0;
    int numThread = 0;
    int threadID = 0;
    int index = 0;

    srand( time( NULL ) );

    for ( int i = 0; i < SIZE; i++ ) {
        vectorA[i] = twoVectorTest.vectorA[i];
        vectorB[i] = twoVectorTest.vectorB[i];
        vectorC[i] = OVER;
    }

    printVector( vectorA, SIZE, "Vector A" );
    printVector( vectorB, SIZE, "Vector B" );
    printVector( vectorC, SIZE, "Vector C" );

    #pragma omp parallel shared(vectorA,vectorB,vectorC,numThread) private(nloc,rest,threadID,step,index)
    {
        numThread = omp_get_num_threads();
        threadID = omp_get_thread_num();
        nloc = SIZE / numThread;
        rest = SIZE % numThread;

        if ( threadID < rest ) {
            nloc++;
            step = 0;
        } else {
            step = rest;
        }

        for ( int i = 0; i < nloc; i++ ) {
            index = i + nloc * threadID + step;
            vectorC[ index ] = vectorA[ index ] + vectorB[ index ];
        }
    }

    printVector( vectorC, SIZE, "Computed Vector C" );
    printVector( twoVectorTest.vectorC, SIZE, "Result Vector C" );

    return 0;
}