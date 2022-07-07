#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long samples = 100000000;

int main (int argc, char *argv[])
{
	if ( argc == 1 ) 
	{
		puts("Usage: ./pi_mc <integer>");
		exit(99);
	}
	long i;  long hits = 0;
	double pi, x, y, test, moment;
	double r = 1.0;   // radius of circle. Side of square is 2*r 
	
	moment = omp_get_wtime();
        unsigned seed = atoi(argv[1])* (unsigned)time(NULL);
	 
dummyMethod1();
#pragma omp parallel for private(x, y, test) firstprivate(seed) reduction(+:hits) schedule(static, 2000)
	for(i=0;i<samples; i++)
	{
		x = ( (double)rand_r(&seed))/( (double)RAND_MAX);
		y = ( (double)rand_r(&seed))/( (double)RAND_MAX);

		test = x*x + y*y;

		if (test <= r*r) hits++;
	}
dummyMethod2();

	pi = 4.0 * ((double)hits/(double)samples);

	printf("\n %ld trials, pi is %f \n",samples, pi);
	printf(" in %f seconds\n", omp_get_wtime()-moment);
	return 0;
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