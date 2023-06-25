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
    
    /**
     * la direttiva for ci permette di distribuire in maniera automatica
     * "Tecnica ad alto livello" il numero delle locazioni sul quale
     * ogni thread deve lavorare, quindi senza farlo manualmente.
     * 
     * Nel momento in cui ci avvaliamo di tecniche ad alto livello come
     * la direttiva for, sappiamo che le locazione vengono distribuite in maniera
     * automatica ai rispettivi thread, utilizzando altre direttive come schedule
     * possiamo andare a comunicare anche in che modo vogliamo distribuire le locazioni
     * 
     * In questo esempio viene utilizzato lo scheduling "guided"
     * Vedi README.md
    */
    #pragma omp parallel for private(i) num_threads(4) schedule(guided)
    for ( i = 0; i < N; i++ ) {
        printf( "Il thread %d ha completato iterazione %d.\n", omp_get_thread_num( ) , i );
    }
    
    printf( "Tutti I thread hanno terminato!\n" );
    
    return 0;
}