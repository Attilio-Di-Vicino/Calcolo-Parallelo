/**
 * STRATEGIA: 2
 * 
 * Somma n numeri utilizzando la seconda strategia
*/

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100
#define MAXVALUE 1

int main() {

    int numbers[ SIZE ];
    int sum = 0;

    srand( time( NULL ) );
    
    // Inizializzazione dell'array
    for ( int i = 0; i < SIZE; i++ )
        numbers[i] = rand() % MAXVALUE + 1;

    // Stampa dell'array
    printf( "\nNumbers: " );
    for ( int i = 0; i < SIZE; i++ )
        printf( "%d ", numbers[i] );
    
    // Strategia 2: Somma parallela utilizzando "reduction" con passi iterativi
    #pragma omp parallel
    {
        int numThreads = omp_get_num_threads();
        int threadID = omp_get_thread_num();
        int localSum = 0;
        
        // Calcolo della somma parziale
        for ( int i = threadID; i < SIZE; i += numThreads ) {
            localSum += numbers[i];
        }
        
        // Riduzione delle somme parziali
        #pragma omp critical
        sum += localSum;
    }
    
    printf("\nSomma utilizzando la strategia 2: %d\n", sum);
    
    return 0;
}