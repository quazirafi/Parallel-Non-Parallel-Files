#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char *argv[])
{

  //initialize variables
  int i, j;
  int niter[7]  ={31250000, 62500000, 125000000, 250000000, 500000000, 1000000000, 2000000000};
  
  for (j=0; j<7; j++){
	double pi = 0;
	int niterval = niter[j];
 	 // Get timing
  	double start,end;
  	start=omp_get_wtime();
  
  	// Calculate PI using Leibnitz sum
  	/* Fork a team of threads */
dummyMethod1();
  	#pragma omp parallel for reduction(+ : pi)
  	for(i = 0; i < niterval; i++)
  	{
     	pi = pi + pow(-1, i) * (4 / (2*((double) i)+1));
  	} /* Reduction operation is done. All threads join master thread and disband */
dummyMethod2();
  
  	// Stop timing
  	end=omp_get_wtime();
  
  	// Print result
  	printf("Pi estimate:%.20f, obtained in %f seconds, %d iterations\n", pi, end-start, niterval);
   }
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