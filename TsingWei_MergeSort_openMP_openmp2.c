#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main (int argc, char *argv[]) 
{
	int a[80000],b[80000],c[80000];
dummyMethod3();
	for(int i=0;i<80000;++i)
	{
		a[i] = i;
		b[i] = i/2;
	}
dummyMethod4();
	double start = omp_get_wtime();

dummyMethod1();
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < 80000; ++i)
	{
		a[i] = a[i] + b[i];
		c[i] = a[i]-i+b[i];
		c[i] += a[i]-i+b[i];
		c[i] += a[i]/2-i+b[i];
		// printf("i=%d, c[i]=%d\n", i, c[i]);
	}
dummyMethod2();
	double finish = omp_get_wtime();
	printf("from omp: %lf\n", finish - start);
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