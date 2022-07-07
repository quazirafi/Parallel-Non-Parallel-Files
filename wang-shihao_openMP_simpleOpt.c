#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	double start, end;
	start = omp_get_wtime();
	long count = 0;
	long i;
dummyMethod1();
#pragma omp parallel for schedule(auto) reduction(+:count) num_threads(100)
	for (i = 1; i <= 2147483647; i++)
		if (i % 2 != 0)	count++;
	end = omp_get_wtime();
dummyMethod2();
	printf("%f seconds, result is %li\n", end-start, count);
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