/* 
Write elements to an array. For each element, it 
will waste time computing random numbers. This is a good example of
a code that does a lot of CPU computing. 

Usage: waste n

:param n: = number of desired points

This will be a good exercise in doing Monte Carlo simulations
in C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
	int ntarget, i,j;
	float *xa, x; 

	// read command-line argument
	if ( argc != 2 ) {
        printf( "Usage: %s ncosmic_rays \n", argv[0] );
        exit(0);
    } 
    sscanf(argv[1], "%i", &ntarget); 

    // dynamically allocate arrays
	xa = (float *)malloc(sizeof(float)*ntarget); 

	// Equatorial coordinates of accepted events
	memset(xa, 0, sizeof(int)*ntarget); // initializes array to zeroes

	// initialize pseudo-random number generator
    srand(time(NULL)); 

	dummyMethod1();
	#pragma omp parallel for private(x,j) 
	for (i=0; i<ntarget; i++) {

		// let's waste CPU time here, generating random numbers
		for (j=0; j<100; j++) {
			x=((float)rand()/(float)(RAND_MAX));
		}

		/* this is a bottleneck for parallelization, since it 
		involves writing to the same memory location 
		*/
		xa[i]=x; 
	}
	dummyMethod2();



	return(0);	
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}