/**
 * STRATEGIA: 1A
 * 
 * Somma n numeri utilizzando la seconda strategia
 * utilizzando il classico metodo 
*/

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 170
#define MAXVALUE 99

int main() {

    int numbers[ SIZE ];
    int sum = 0;

    int nloc = 0; // numero di operazioni singolo thread
    int step = 0; // step per singolo thread che dovrà rispettare nel calcolo dell'index
    int rest = 0; // resto utilizzato per i thread che dovranno fare più operazioni
    int index = 0; // indice del vettore

    srand( time( NULL ) );
    
    // Inizializzazione dell'array
    for ( int i = 0; i < SIZE; i++ )
        numbers[i] = rand() % MAXVALUE + 1;

    // Stampa dell'array
    printf( "\nNumbers: " );
    for ( int i = 0; i < SIZE; i++ )
        printf( "%d ", numbers[i] );
    
    // Strategia 1: Somma parallela utilizzando "reduction" con passi iterativi
    #pragma omp parallel private(nloc,step,index) shared(sum,numbers)
    {
        int numThreads = omp_get_num_threads();
        int threadID = omp_get_thread_num();
        int partialSum = 0;
        int totalIterations = 0;

        nloc = SIZE / numThreads; // Numero di operazioni
        rest = SIZE % numThreads; // Thread che dovranno fare più opeazioni

        // Se rest è 0 significa che il SIZE è divisibile per il numero di thread
        // quindi faranno tutti i thread lo stesso numero di operazioni
        // altrimenti viene incrementato il numero di locazione al quale 
        // dovrà calcolare la somma e le locazioni saranno contigue
        if ( threadID < rest ) {
            nloc++;
            step = 0;
        } else {
            step = rest;
        }

        #pragma omp master
        {
            printf( "\n\nI'm Thread %d and i'm here to print the total number of threads", threadID );
            printf( "\nTotal Thread are: %d\n", numThreads );
        }
        
        // Calcolo della somma parziale
        for ( int i = 0; i < nloc; i++ ) {
            // L'indice sul quale ogni thread andrà ad operare sarà
            // calcolato attraverso la seguente espressione
            // dove ogni thread avrà il proprio nloc, ID e step 
            index = i + nloc * threadID + step;
            partialSum += numbers[ index ];
            totalIterations++;
        }

        printf( "\nI'm Thread %d and have done %d iterations", threadID, totalIterations );
        
        // Riduzione delle somme parziali
        #pragma omp critical
        sum += partialSum;
    }
    
    printf( "\nSum using strategy 2A: %d\n", sum );
    
    return 0;
}