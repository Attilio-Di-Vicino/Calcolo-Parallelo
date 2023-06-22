#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

/**
 * Guardiamo insieme il seguente codice…
 * ad ogni iterazione i thread aspettano un numero di
 * secondi pari a l’indice dell’iterazione.
*/

int main() {

    int n_threads, i;

    #pragma omp parallel for private(i) schedule(static) num_threads(4)
    for ( i = 0; i < 16; i++ )
    {
        //aspetta un numero pari ad i secondi
        sleep(i);
        printf( "Il thread %d ha completato iterazione %d.\n", omp_get_thread_num() , i );
    }

    printf( "Tutti I thread hanno terminato!\n" );
    return 0;
}