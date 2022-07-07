#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000000;//100000000;
double step;


int main (){

	int i;
	double x,pi,sum=0.0;

	double start,end;

	printf("\nNumber of Steps : %d\n",num_steps);

	step = 1.0/(double) num_steps;

	start = omp_get_wtime();

dummyMethod1();
#pragma omp parallel for schedule(static,4)
	for (i=0;i<num_steps;i++){
		x=(i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);

	}
dummyMethod2();

	end = omp_get_wtime();

	pi=step*sum;

	printf("pi = %lf\n",pi);
	printf("Time : %lf msec\n",(end-start)*1000);


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