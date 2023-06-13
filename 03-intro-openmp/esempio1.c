/**
 * ESEMPIO: 1
 * 
 * Struttura generica del codice
*/

#include <omp.h>

void main() {

    // Variabili generali
    int a,b,c;

    // { Parte sequenziale eseguita dal thread master }

    // Inizio della regione parallela:
    // si genera un team di thread e si specifica lo scopo delle variabili
    #pragma omp parallel private( a, b ) shared( c )
    {
        // Sezione parallela eseguita da tutti i thread
        // { Codice parallelo }
        // Tutti i thread confluiscono nel master thread
    }

    // Ripresa del codice sequenziale
}