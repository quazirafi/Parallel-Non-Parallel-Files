#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define CHUNKSIZE 1000

static long num_steps = 10000;

double step;

void main() {
	int i,chunk;
	chunk = CHUNKSIZE; 
	double x, pi;
	double sum = 0.0;
	step = 1.0/(double) num_steps;
	
dummyMethod1();
	#pragma omp parallel for default(shared) private(i, x) \
	 schedule(static, chunk) reduction(+:sum)
		for (i = 0; i < num_steps; i++) {
			x = (i + 0.5)*step;
			sum = sum + 4.0/(1.0 + x*x);
		}
dummyMethod2();
	
	pi = step * sum;
	printf("pi [%lf] step [%lf] sum[%lf]\n", pi, step,sum);
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