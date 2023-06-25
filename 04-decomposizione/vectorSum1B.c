/**
 * STRATEGIA: 1B
 * 
 * Somma n numeri utilizzando la prima strategia
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
    int i;

    srand( time( NULL ) );
    
    // Inizializzazione dell'array
    for ( i = 0; i < SIZE; i++ )
        numbers[i] = rand() % MAXVALUE + 1;

    // Stampa dell'array
    printf( "\nNumbers: " );
    for ( i = 0; i < SIZE; i++ )
        printf( "%d ", numbers[i] );
    
    /**
     * Il nucleo computazionale in questo caso non è Full Parallel,
     * di conseguenza abbiamo bisogno di una strategia c'è ci permetta
     * di gestire la collezione dei dati.
     * In questo caso viene applicata la strategia 1, dove tutti i thread
     * hanno una memoria condivisa e in maniera sequenziale vanno ad aggiungere
     * la propria somma parziale precedentemente calcolata alla somma totale
     * la quale si trova in memoria condivisa, di conseduenza è soggetta a race condiction,
     * infatti tra le clause della direttiva sum è dichiarata shared, in questo modo
     * si protegge la variabile da eventuali problemi di race
    */
    #pragma omp parallel shared(sum,numbers) private(i)
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
        for ( i = threadID; i < SIZE; i += numThreads ) {
            partialSum += numbers[i];
            totalIterations++;
        }

        printf( "\nI'm Thread %d and have done %d iterations", threadID, totalIterations );
        
        sum += partialSum;
    }
    
    printf( "\nSum using strategy 2B: %d\n", sum );
    
    return 0;
}