#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/**
 * La modalità guided ha una politica di pianificazione molto
 * simile alla modalità dynamic, tranne per il fatto che
 * la dimensione del chunk cambia durante l'esecuzione del programma.
*/

/**
 * Inizia con chunk di grandi dimensioni, ma adatta in autonomia la 
 * dimensione di chunk, rendendo questo valore più piccolo
 * se il carico di lavoro è sbilanciato.
*/

#define N 1000

int main() {

    int n_threads, i;
    
    #pragma omp parallel for private(i) num_threads(4) schedule(guided)
    for ( i = 0; i < N; i++ ) {
        printf( "Il thread %d ha completato iterazione %d.\n", omp_get_thread_num( ) , i );
    }
    
    printf( "Tutti I thread hanno terminato!\n" );
    
    return 0;
}