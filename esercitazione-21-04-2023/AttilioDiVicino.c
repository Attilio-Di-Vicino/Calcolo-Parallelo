#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i, N;
	int sumtot = 0, *a, *b, *c, sum;
	double t1;
	double t2;
	
	printf( "Inserisci N: " );
	scanf( "%d", &N );
	
	
	// Allocazione dinamica
	a = ( int * ) calloc( N, sizeof( int ) );
	b = ( int * ) calloc( N, sizeof( int ) );
	c = ( int * ) calloc( N, sizeof( int ) );
	
	// Inizializzazione vettore a
	for( i = 0; i < N; i++ )
	{
		a[i] = i+1;
	}

	// Inizializzazione vettore b
	for( i = 0; i < N; i++ )
	{
		b[i] = i+1;
	}
	
	// Inizializzazione vettore c
	for( i = 0; i < N; i++ )
	{
		c[i] = 0;
	}
	
	// Prendiamo il tempo di inizio
	t1 = omp_get_wtime();
	
	/**
	* In questo costrutto  andiamo impostare le seguenti direttive al processore che sono
	*	- variabili private
	*	- variabili condivise
	*	- il tipo di scheduler 
	* Eseguiamo quindi il prodotto puntuale tra due vettori
	*/
	#pragma omp parallel for private(i) shared(a,b,c) schedule(static)	
	for ( i = 0; i < N; i++ )
	{
		c[i] = a[i] * b[i];
	}
	
	
	// Stampa di c
	for ( i = 0; i < N; i++ )
	{
		printf( " %d\n", c[i] );
	} 
	
	/**
	* In questo costrutto  andiamo impostare le seguenti direttive al processore che sono
	*	- variabili private
	*	- variabili condivise
	*	- il tipo di scheduler 
	* Dopo aver eseguito il prodotto puntuale andiamo a somma gli N elementi del vettore risultato ottenendo così uno scalare 
	*/
	sum = 0;
	#pragma omp parallel for private(i,sum) shared(sumtot) schedule(static)
	for( i = 0; i < N; i++ )
	{
		sum = c[i];
		#pragma omp atomic
		sumtot += sum;
	}
	
	// Prendiamo il tempo di fine
	t2 = omp_get_wtime();
	
	// Stampiamo il tempo e la durata dell'esecuzione
	printf( "\nStampa t1: %f", t1 );
	printf( "\nStampa t2: %f", t2 );
	printf( "\nTempo finale: %f", t2-t1 );
	
	// Stampa Prodotto Scalare
	printf( "\nSomma Totale: %d\n", sumtot );
	return 0;
}