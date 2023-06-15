/**
 * STRATEGIA: 2B
 * 
 * Somma n numeri utilizzando la seconda strategia
 * ed utilizzando un metodo alternativo e più semplice da implementare
*/

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100
#define MAXVALUE 99

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
    #pragma omp parallel shared(sum,numbers)
    {
        int numThreads = omp_get_num_threads();
        int threadID = omp_get_thread_num();
        int partialSum = 0;
        int totalIterations = 0;

        #pragma omp master
        {
            printf( "\n\nI'm Thread %d and i'm here to print the total number of threads", threadID );
            printf( "\nTotal Thread are: %d\n", numThreads );
        }
        
        // Calcolo della somma parziale
        for ( int i = threadID; i < SIZE; i += numThreads ) {
            partialSum += numbers[i];
            totalIterations++;
        }

        printf( "\nI'm Thread %d and have done %d iterations", threadID, totalIterations );
        
        // Riduzione delle somme parziali
        #pragma omp critical
        sum += partialSum;
    }
    
    printf( "\nSum using strategy 2B: %d\n", sum );
    
    return 0;
}