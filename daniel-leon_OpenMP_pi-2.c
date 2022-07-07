#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 10000;

double step;

void main() {
	int i; 
	double x, pi;
	double sum = 0.0;
	step = 1.0/ (double) num_steps;
	#pragma omp parallel 
	{
		#pragma omp sections nowait
		{
			#pragma omp parallel num_threads(5)
dummyMethod1();
			#pragma omp parallel for
			for (i = 0; i < num_steps; i++) {
			x = (i + 0.5)*step;
dummyMethod2();
			sum = sum + 4.0/(1.0 + x*x);
			}

		printf("pi [%lf] step [%lf] sum[%lf]\n", pi, step,sum);
		}
		#pragma omp barrier
		pi = step * sum;
		printf("pi [%lf] step [%lf] sum[%lf]\n", pi, step,sum);
		//printf("MiId (%d)", id);
		
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