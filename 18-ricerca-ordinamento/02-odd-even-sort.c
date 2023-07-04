#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10
#define MAXVALUE 100

void printVector( int*, int, char[] );
void oddEvenSort( int*, int);
int main() {
    
    int* vector;
    vector = ( int* ) malloc( SIZE * sizeof( int ) );
    srand( time( NULL ) );
    
    for ( int i = 0; i < SIZE; i++ )
        vector[i] = rand() % MAXVALUE + 1;
    
    printVector( vector, SIZE, "Vector before the sorting" );
    oddEvenSort( vector, SIZE );
    printVector( vector, SIZE, "Vector after the sorting" );
    
    printf( "\n" );
    return 0;
}

void printVector( int* vector, int N, char name[] ) {
    printf( "\n%s: ", name );
    for ( int i = 0; i < SIZE; i++ )
        printf( "%d ", vector[i] );
}

void oddEvenSort( int* a, int N ) {

    int sw = 1, start = 0, i = 0;
    int temp;
    while( sw || start ) {
        sw = 0;
        
        #pragma omp parallel for private( temp ) 
        for ( i = start ; i < N - 1 ; i += 2) {
            if ( a[i] > a[ i + 1 ] ) {
                temp = a[i] ;
                a[i] = a[ i + 1 ];
                a[ i + 1 ] = temp ;
                sw = 1 ;
            }
        }

        if ( start == 0 ) 
            start = 1 ;
        else 
            start = 0;
    }
}