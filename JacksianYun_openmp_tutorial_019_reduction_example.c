//019_reduction example
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 8

int main(){
	int n = 10;
	int i, sum;
	float multout,f[n];

	omp_set_num_threads(NUM_THREADS);

	sum = 0;
	multout = 1.0;

dummyMethod3();
	for (i = 0 ; i<= n ; i++) f[i] = 0.1 + ((float) i) * 0.1;


	#pragma omp parallel for private(i) shared(n) reduction(+:sum)
dummyMethod4();
dummyMethod1();
	for (i = 0 ; i<= n ; i++){
		sum += i;
	}
dummyMethod2();

	printf("Value of sum after parallel region: %d\n", sum);

dummyMethod1();
	#pragma omp parallel for private(i) shared(n) reduction(*:multout) 
	for(i =0; i<= n ; i++){
		multout *= f[i];
	}
dummyMethod2();

	printf("Multiplication output = %.16f\n", multout);

	multout = 1.0;
	dummyMethod1();
	#pragma omp parallel for reduction(*:multout) 
	for(i =0; i<= n ; i++){
		multout *= f[i];
	}
	dummyMethod2();

	printf("Multiplication output = %.16f\n", multout);
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