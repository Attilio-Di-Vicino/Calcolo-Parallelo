/**
* ESERCITAZIONE: 08/06/2023
* 
* Implementare un programma parallelo per l'ambiente multicore con np
* unità processanti che impieghi la libreria OpenMP. Il programma deve
* essere organizzato come segue:
*
* 1. il core master deve leggere una matrice A di dimensione NxM
*
* 2. i core devono organizzarsi per estrarre ognuno una sottomatrice,
*    decomponendo la matrice A per blocchi riga, e costruendo la trasposta
*    di tale sottomatrice, in una matrice Bloc
*
* 3. infine i core devono collaborare per sommare le sotto matrici estratte Bloc 
*    in un'unica matrice finale C
*
* 4. il core master stampa la matrice risutato e il tempo d'esecuzione
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXVALUE 9
#define N_BLOC M // le righe di Bloc saranno le colonne di A
#define M_BLOC N // le colonne di Bloc saranno le righe di A
#define NUMTHREADS NP // Numero dei thread utilizzati
#define OFFSET(b) b * ( N_BLOC / NUMTHREADS ) // Offset per accedere ai singoli Bloc
#define N_C ( M / NUMTHREADS ) + ( M % NUMTHREADS ) // Numero di righe della matrice C
#define M_C N // Numero di colonne della matrice C

void deallocationMatrix( int***, int );
void initMatrix( int***, int, int );
void allocationMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
int main() {

	int N, M, NP;
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
    double startTime = 0.0;
	double endTime = 0.0;

    int i, j, b;
	
	srand( time( NULL ) );

    printf( "\nInserisci il numero di thread: " );
	scanf( "%d", &NP );
	
	printf( "\nInserisci il numero di righe: " );
	scanf( "%d", &N );
	
	printf( "\nInserisci il numero di righe: " );
	scanf( "%d", &M );

    // Off viene utilizzato nel caso in cui 
    // le colonne di A non siano divisibili 
    // per il numero di thread utilizzati
    int off = M % NUMTHREADS;
	
	printf( "\nMatrix -> N: %d, M: %d", N, M );
    printf( "\nBloc -> N: %d, M: %d", N_BLOC, M_BLOC );
    printf( "\nNumero di thread utilizzati: %d\n", NUMTHREADS );
	
	// Allocazioni
    allocationMatrix( &matrix, N, M );
    allocationMatrix( &Bloc, N_BLOC, M_BLOC );
    allocationMatrix( &C, N_C, M_C );
	
	// Inizializzazioni	
	for ( int i = 0; i < N; i++ )
		for ( int j = 0; j < M; j++ )
			matrix[i][j] = rand() % MAXVALUE + 1;

    initMatrix( &Bloc, N_BLOC, M_BLOC );
    initMatrix( &C, N_C, M_C );

    // Prendiamo il tempo di inizio
	startTime = omp_get_wtime();

	// Calcolo della matrice trasposta 
	#pragma omp parallel for private(i,j) shared(Bloc,matrix) schedule(static) num_threads(NUMTHREADS)
	for ( i = 0; i < N; i++ ) {
		for ( j = 0; j < M; j++ ) {
			Bloc[j][i] = matrix[i][j];
		}
	}
	
    // Stampa della matrice
	#pragma omp master
    {
        printMatrix( matrix, N, M, "Matrix" );
    }

    // Stampa dei Bloc
    #pragma omp master
    {
        for ( b = 0; b < NUMTHREADS; b++ ) {
            printf( "\nBloc #%d\n", b );
            int S;
            if ( b == 0 )
                S = ( N_BLOC / NUMTHREADS ) + ( N_BLOC % NUMTHREADS );
            else
                S = N_BLOC / NUMTHREADS;
            for ( i = 0; i < S; i++ ) {
                for ( j = 0; j < M_BLOC; j++ )
                    printf( "%d\t", Bloc[ OFFSET(b) + i ][j] );
                printf( "\n" );
            }
        }
    }

    // Somma Bloc in C
    #pragma omp parallel for private(i,j,b) shared(Bloc,C,off) schedule(static) num_threads(NUMTHREADS)
    for ( i = 0; i < N_C - off; i++ ) {
		for ( j = 0; j < M_C; j++ ) {
            for ( b = 0; b < NUMTHREADS; b++ )
			    C[i][j] += Bloc[ OFFSET(b) + i ][j];
		}
	}

    // Somma Bloc in C
    #pragma omp parallel for private(i,j) shared(Bloc,C,off) schedule(static) num_threads(NUMTHREADS)
    for ( i = N_C - off; i < N_C; i++ ) {
		for ( j = 0; j < M_C; j++ ) {
			C[i][j] = Bloc[i][j];
		}
	}

    // Prendiamo il tempo di fine
	endTime = omp_get_wtime();

    // Stampo C ed i tempi
    #pragma omp master
    {
        printMatrix( C, N_C, M_C, "Matrice finale C" );
        printf( "\nTempo di inizio: %f", startTime );
        printf( "\nTempo di fine: %f", endTime );
        printf( "\nTempo finale: %f", endTime - startTime );
    }

    // Deallocazioni
    deallocationMatrix( &matrix, N );
    deallocationMatrix( &Bloc, N_BLOC );
    deallocationMatrix( &C, N_C );
	
	printf( "\n" );
	return 0;
}

void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d	", matrix[i][j] );
        printf( "\n" );
    }
}

void allocationMatrix( int*** matrix, int N, int M ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
	for ( int i = 0; i < N; i++ )
		( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );
}

void initMatrix( int*** matrix, int N, int M ) {
	for ( int i = 0; i < N; i++ )
		for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = 0;
}

void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix);
}