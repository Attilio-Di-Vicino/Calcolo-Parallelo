/**
 * STRATEGIA: 1
 * 
 * Somma n numeri utilizzando la prima strategia
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
    
    /**
     * Strategia 1: Somma parallela utilizzando l'approccio di "reduction"
     * 
     * In questa strategia, utilizziamo la clausola 'reduction' con la variabile
     * condivisa 'sum' e l'operatore '+' per indicare che ogni thread calcola
     * la sua somma parziale e la aggiunge in modo sicuro alla variabile condivisa 'sum'.
     * 
     * La clausola 'reduction(+:sum)' specifica che 'sum' è una variabile di riduzione
     * e che l'operatore '+' deve essere utilizzato per aggregare correttamente i valori
     * parziali tra i thread.
     * 
     * Ogni thread calcola la sua somma parziale e la salva in una copia locale della
     * variabile 'sum'. Alla fine dell'esecuzione dei thread, il thread master
     * combina automaticamente le copie locali delle variabili 'sum' utilizzando
     * l'operatore '+', ottenendo così il risultato finale della somma totale.
     * 
     * Questo approccio garantisce che i calcoli paralleli siano eseguiti in modo corretto
     * e sicuro, con OpenMP che si occupa internamente della sincronizzazione e dell'aggregazione
     * dei valori parziali tra i thread.
     */
    #pragma omp parallel for shared(numbers) reduction(+:sum)
    for ( int i = 0; i < SIZE; i++ ) {
        sum += numbers[i];
    }
    
    printf( "\nSomma utilizzando la strategia 1: %d\n", sum );
    
    return 0;
}