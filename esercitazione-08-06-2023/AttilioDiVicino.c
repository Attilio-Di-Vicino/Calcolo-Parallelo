/**
* ESERCITAZIONE_AULA:
* 
* Implementare un programma parallelo per l'ambiente multicore con np
* unità processanti che impieghi la libreria OpenMP. Il programma deve
* essere organizzato come segue:
*
* * il core master deve leggere una matrice A di dimensione NxM
*
* * i core devono organizzarsi per estrarre ognuno una sottomatrice,
*   decomponendo la matrice A per blocchi riga, e costruendo la trasposta
*   di tale sottomatrice, in una matrice Bloc
*
* * infine i core devono collaborare per sommare le sotto matrici estratte Bloc 
*   in un'unica matrice finale C
*
* * il core master stampa la matrice risutato e il tempo d'esecuzione
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXVALUE 9
#define N_BLOC M // le righe di Bloc saranno le colonne di A
#define M_BLOC N // le colonne di Bloc saranno le righe di A
#define NUMTHREADS 8 // Numero dei thread utilizzati
#define OFFSET(b) b * ( N_BLOC / NUMTHREADS ) // Offset per accedere ai singoli Bloc
#define N_C M / NUMTHREADS // Numero di righe della matrice C
#define M_C N // Numero di colonne della matrice C

void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d	", matrix[i][j] );
        printf( "\n" );
    }
}

int main() {

	int N, M;
	int** matrix;

    /**
     * In questo caso dichiariamo Bloc un doppio puntatore
     * da considerare il fatto che Bloc sono più matrici,
     * quindi avremo tante matrici Bloc quanti sono np ( core )
     * la memoria delle matrici Bloc viene gestita in maniera contigua
    */
	int** Bloc;

    // Matrice risultante
    int** C;

    // Tempi
    double t1;
	double t2;

    int i, j, b;
	
	srand( time( NULL ) );
	
	printf( "\nInserisci il numero di righe: " );
	scanf( "%d", &N );
	
	printf( "\nInserisci il numero di righe: " );
	scanf( "%d", &M );
	
	printf( "\nMatrix -> N: %d, M: %d", N, M );
    printf( "\nBloc -> N: %d, M: %d", N_BLOC, M_BLOC );
    printf( "\nNumero di thread utilizzati %d\n", NUMTHREADS );
	
	// Allocazione matrice
	matrix = ( int** ) calloc( N, sizeof( int* ) );
	for ( int i = 0; i < N; i++ )
		matrix[i] = ( int* ) calloc( M, sizeof( int ) );
	
    // Allocazione matrici Bloc ( NB: sono più di una matrice )
	Bloc = ( int** ) calloc( N_BLOC, sizeof( int* ) );
	for ( int i = 0; i < N_BLOC; i++ )
		Bloc[i] = ( int* ) calloc( M_BLOC, sizeof( int ) );

    // Allocazione C
    C = ( int** ) calloc( N_C, sizeof( int* ) );
    for ( int i = 0; i < N_C; i++ )
        C[i] = ( int* ) calloc( M_C, sizeof( int ) );
	
	// Inizializzazione matrice	
	for ( int i = 0; i < N; i++ )
		for ( int j = 0; j < M; j++ )
			matrix[i][j] = rand() % MAXVALUE + 1;

    // Inizializzazione Bloc
	for ( int i = 0; i < N_BLOC; i++ )
		for ( int j = 0; j < M_BLOC; j++ )
			Bloc[i][j] = 0;

    // Inizializzazione C
	for ( int i = 0; i < N_C; i++ )
		for ( int j = 0; j < M_C; j++ )
			C[i][j] = 0;

	// Calcolo della matrice trasposta
	#pragma omp parallel for private(i,j) shared(Bloc,matrix) schedule(static) num_threads(NUMTHREADS)
	for ( i = 0; i < N; i++ ) {
		for ( j = 0; j < M; j++ ) {
			Bloc[j][i] = matrix[i][j];
		}
	}

    // Prendiamo il tempo di inizio
	t1 = omp_get_wtime();
	
    // Stampa della matrice
	#pragma omp master
    printMatrix( matrix, N, M, "Matrix" );
    // printMatrix( Bloc, N_BLOC, M_BLOC, "Trasposta" );

    // Stampa dei Bloc
    #pragma omp master
    for ( b = 0; b < NUMTHREADS; b++ ) {
        printf( "\nBloc #%d\n", b );
        for ( i = 0; i < N_BLOC / NUMTHREADS; i++ ) {
            for ( j = 0; j < M_BLOC; j++ )
                printf( "%d    ", Bloc[ OFFSET(b) + i ][j] );
            printf( "\n" );
        }
    }

    // Somma Bloc in C
    #pragma omp parallel for private(i,j,b) shared(Bloc,C) schedule(static) num_threads(NUMTHREADS)
    for ( i = 0; i < N_C; i++ ) {
		for ( j = 0; j < M_C; j++ ) {
            for ( b = 0; b < NUMTHREADS; b++ )
			    C[i][j] += Bloc[ OFFSET(b) + i ][j];
		}
	}

    // Prendiamo il tempo di fine
	t2 = omp_get_wtime();

    // Stampo C ed i tempi
    #pragma omp master
    printMatrix( C, N_C, M_C, "Matrice finale C" );
	printf( "\nStampa t1: %f", t1 );
	printf( "\nStampa t2: %f", t2 );
	printf( "\nTempo finale: %f", t2-t1 );
	
	printf( "\n" );
	return 0;
}