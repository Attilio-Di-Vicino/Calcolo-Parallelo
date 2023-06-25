#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

/**
 * E’ chiaro che lo scheduling NON è bene organizzato!
 * Proviamo a migliorare usando la modalità dynamic.
 * In questo modo ciascun thread ha una iterazione:
 * quando questo termina gli verrà assegnata la successiva iterazione.
*/

/**
 * La modalità dinamica è migliore quando le iterazioni possono richiedere 
 * tempi molto diversi. Tuttavia, esiste un’inevitabile sovraccarico nell’uso della 
 * pianificazione dinamica: 
 * dopo ogni iterazione, i thread devono arrestarsi e ricevere un nuovo valore 
 * della variabile del ciclo da utilizzare per la successiva iterazione.
 * Questo può provocare un evidente rallentamento.
*/

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
     * In questo esempio viene utilizzato lo scheduling "dynamic".
     * Vedi README.md
    */
    #pragma omp parallel for private(i) schedule(dynamic) num_threads(4)
    for ( i = 0; i < 16; i++ )
    {
        //aspetta un numero pari ad i secondi
        sleep(i);
        printf( "Il thread %d ha completato iterazione %d.\n", omp_get_thread_num() , i );
    }

    printf( "Tutti I thread hanno terminato!\n" );
    return 0;
}