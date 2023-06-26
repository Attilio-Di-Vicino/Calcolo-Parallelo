/**
 * SBAGLIATO:
 * ALGORITMO NON FUNZIONANTE
*/
#include <stdio.h>
#include <omp.h>

#define N 10
#define BLOCK_SIZE 1

int main() {
    int matrix[N][N];
    int i, j;

    // Inizializzazione della matrice
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matrix[i][j] = i + j;
        }
    }

    int p = 0;

    // Parallelizzazione del calcolo
    #pragma omp parallel for private(i, j,p) shared(matrix) schedule(static, BLOCK_SIZE)
    for (i = 0; i < N; i++) {
        // Ogni thread elabora un blocco di righe
        int thread_id = omp_get_thread_num();
        int start_row = thread_id * BLOCK_SIZE;
        int end_row = (thread_id + 1) * BLOCK_SIZE;

        if ( p == 0 ){
            printf("\nThread: %d -> s: %d, e: %d", thread_id, start_row, end_row);
            p = 1;
        }

        for (j = start_row; j < end_row; j++) {
            // Elaborazione delle righe
            // Esempio: somma degli elementi di ogni riga
            int sum = 0;
            for (int k = 0; k < N; k++) {
                matrix[j][k] = thread_id;
            }
        }
    }

    printf( "\nM:\n" );
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf( "%d    ", matrix[i][j] );
        }
        printf( "\n" );
    }

    return 0;
}