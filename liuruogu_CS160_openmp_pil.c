#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NUM_THREADS 3

static long num_steps = 100000;
double step;
double omp_get_wtime(void);
double start;
double end;

void main() 
{
	int i; double x, pi, sum = 0.0;
	step = 1.0/(double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	start = omp_get_wtime();
dummyMethod1();
		#pragma omp parallel for private(x) reduction(+:sum)
		for(i=0;i<num_steps;i++)
		{
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
dummyMethod2();
	pi = step*sum;
	end = omp_get_wtime();
	printf("%f\n",pi);
	printf("Run in loop construction will take %f second\n",end-start);
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