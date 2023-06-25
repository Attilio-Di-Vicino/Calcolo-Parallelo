#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/**
 * E’ possibile migliorare le prestazioni utilizzando
 * l’opzione chunk con la modalità dynamic.
 * In questo modo, ad ogni thread sarà associato un numero prestabilito di 
 * iterazioni, quindi quando avrà terminato avrà assegnato un nuovo chunk.
*/

/**
 * Aumentando la dimensione del chunk lo 
 * scheduling tende alla modalità static;
 * mentre diminuendola lo scheduling tende al dynamic.
*/

#define N 1000
#define CHUNK 10

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
     * In questo esempio viene utilizzato lo scheduling "dynamic" con l'aggiunta di CHUNK
     * Vedi README.md
    */
    #pragma omp parallel for private(i) num_threads(4) schedule(dynamic, CHUNK)
    for ( i = 0; i < N; i++ ) {
        printf( "Il thread %d ha completato iterazione %d.\n", omp_get_thread_num( ) , i );
    }
    
    printf( "Tutti I thread hanno terminato!\n" );
    
    return 0;
}