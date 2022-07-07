#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM 1000000000

int a[NUM], b[NUM];

int main() {

	long n = NUM;

dummyMethod3();
	for (long i = 0; i < n; i++) {
		a[i] = rand()%10;
		b[i] = rand()%10;
	}
dummyMethod4();

	double t1 = omp_get_wtime();

	omp_set_num_threads(6);

dummyMethod1();
	#pragma omp parallel for schedule(static)
		for (int i = 0; i < n; i++) {
			a[i] = a[i] + b[i];
		}
dummyMethod2();

	double t2 = omp_get_wtime();

	printf("%f\n", t2-t1);

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