#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps=100000000;
double step;
double diff1,diff2 =0;

void main()
{
	diff1 = omp_get_wtime();
	int i=0;
	double x,pi,sum=0.0;
	step=1.0/num_steps;

#pragma omp parallel
{
dummyMethod1();
	#pragma omp parallel for reduction(+:sum)   //mayank, making  program parallel.
		for(i=0;i< num_steps ; i++)
			{
				x=(i+0.5)*step;     //ranga kutta methoos of integral calculation.
				sum = sum + 4.0/(1+x*x);
			}
}
dummyMethod2();
	pi=step*sum;
	diff2=omp_get_wtime();
	diff1=diff2-diff1;
	printf("Time: %f",diff1);
	printf("\n");
	printf("%f",pi);   //commented to stick to original program.
	printf("\n");
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