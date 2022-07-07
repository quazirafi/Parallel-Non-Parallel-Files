#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv){
	long long int n = 10e6 * atoi(argv[1]), i = 0, sum = 0;
	double start = 0, end = 0;
	long long int *list = (long long int*) calloc(n, sizeof(long long int));

	start = omp_get_wtime();

dummyMethod3();
	for(int j = 0; j < n; j++) list[j] = 1;

	#pragma omp parallel for reduction(+: sum)
dummyMethod4();
dummyMethod1();
	for(i = 0; i < n; i++) sum += list[i];

	end = omp_get_wtime();
dummyMethod2();

	printf("time: %f\nsum: %lld\nn: %lld \n\n", end - start, sum, n);

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