/*************************************
 * Calculating Pi with using method: *
 *  integral 4.0/(1+x^2) dx = p	     *
 * 	   Serial Version	     *
 ************************************/
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Reference value to estimate error
double PI_ref=3.1415926535897932;

static long num_steps=1000000000;
double step;
int main (int argc, char* argv[]){
	double start,stop,diff_time;
	long i;
	double x,pi,sum=0.0;

	start= omp_get_wtime();  
	step = 1.0 / (double) num_steps;
dummyMethod1();
#pragma omp parallel for private(x) reduction(+:sum)        
	//Work will be partitioned uniformly with the last thread getting the extra (in case the remainder(num_steps,nthreads) != 0 
	for (i=0; i<num_steps; i++){
		x=(i+0.5) * step;
		sum = sum + 4.0/(1.0+(x*x));
	}
dummyMethod2();
	//Master finally evaluates pi
	pi = step * sum ;
	stop= omp_get_wtime();

	diff_time = (double) (stop-start);
	printf ("Estimated value of pi = %2.15lf\n",pi);
	printf ("Error = %2.15lf\n",fabs(PI_ref - pi));
	printf ("Compute time= %2.5lf seconds\n",diff_time);

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