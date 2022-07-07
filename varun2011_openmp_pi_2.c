#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main ()
{
	static long num_steps=100000;
	double pi=0,step,sum=0;
	step=1.0/(double)num_steps;
	printf("%f ",omp_get_wtime());
dummyMethod1();
	#pragma omp parallel for reduction(+:sum) schedule(runtime)
		for (int i=1;i<=num_steps;i++)
		{
			double x=(i+0.5)*step;
			sum+=4.0/(1.0+x*x);
	}
dummyMethod2();
	pi=sum*step;
	printf("%f ",omp_get_wtime());
	printf(" %f",pi);
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