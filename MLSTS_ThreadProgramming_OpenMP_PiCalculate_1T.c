#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int num_steps=1000000;
double step, pi;

int main(){
	int i;
	double x, sum = 0.0;
	double st = omp_get_wtime();

	step = 1.0 / (double) num_steps;
dummyMethod1();
	#pragma omp parallel for num_threads(1) private(x) reduction(+:sum)
	for (i = 0; i < num_steps; i++){
		x = (i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}
dummyMethod2();
	pi = step * sum;
	double et = omp_get_wtime();
	printf("Pi = %.10f\n", pi);
	printf("Execution time: %f second.\n", (et-st));
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