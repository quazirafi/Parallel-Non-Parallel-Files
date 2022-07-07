#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps= 100000;
double step;

int main()
{
	int i;
	double pi,sum=0.0;
	step= 1.0/(double)num_steps;
	double begin= omp_get_wtime();
dummyMethod1();
	#pragma omp parallel for reduction(+:sum) //schedule(runtime)	
	for(i=0;i<num_steps;i++){
		double x=(i+0.5)*step;
		double value=4.0/(1.0+x*x);
		sum+=value;
	}
dummyMethod2();
	double end= omp_get_wtime();
	pi=step*sum;
	printf("%f : Time taken= %f",pi, end-begin);
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