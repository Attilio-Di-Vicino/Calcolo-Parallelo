/**
 * Calcolo del Pi Greco π in Parallelo
*/

/**
 * OUTPUT:
 * 
 * Numero di intervalli: 100000000
 * Pi Greco π: 3.141592653589815764547666
 * 
 * NB: 24 numeri dopo la virgola
*/

#include <stdio.h>
#include <omp.h>

#define N 100000000

int main( int argc, char** argv ) {

	long int i;
	double x, dx, f, sum, pi;
	
	printf( "Numero di intervalli: %d\n", N );
    
    sum = 0.0;
	
	dx = 1.0 / ( double ) N;
	
	#pragma omp parallel for private(x,f,i) shared(dx) reduction(+:sum)
	for( i = 1; i <= N; i++ ) {
		x = dx * ( ( double ) ( i - 0.5 ) );
		f = 4.0 / ( 1.0 + x * x );
		sum += f;
	}
	
	pi = dx * sum;
	
	printf( "Pi Greco π: %.24f\n", pi );
		
    return 0;
}