/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps = 1000000000;
double step;

int main ()
{
	  int i;
	  double x, pi, sum = 0.0;
	  double start_time, run_time;

	  step = 1.0/(double) num_steps;

        	 
	  start_time = omp_get_wtime();
	  
					dummyMethod1();
	  #pragma omp parallel for private(x), reduction(+:sum)
	  
	  for (i=1;i<= num_steps; i++){
	  	  x = (i-0.5)*step;
	  	  sum = sum + 4.0/(1.0+x*x);
	  }
					dummyMethod2();
	  // gcc -fopenmp -O3 pi.c --> précalcul pendans la compilation
	  // -Os réduit la taille du programme

	  // Question 3 e 4.	
	
	  

	  pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
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