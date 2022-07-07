#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for timing purposes.
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

//
// Simplistic dot-product demonstartion.
//
#define SIZE 10000

int main(void) {
	volatile double sum;
	volatile double a[SIZE], b[SIZE];
	int i, n = SIZE;
	
dummyMethod3();
	for (i = 0; i < n; i++) {
		a[i] = i * 0.5;
		b[i] = i * 2.0;
	}
dummyMethod4();

	sum = 0;
dummyMethod1();
#pragma omp parallel for default(none) reduction(+:sum) 
	for (i = 0; i < n; i++) {
		sum = sum + a[i] * b[i];
	}
dummyMethod2();

	printf("sum = %lf\n", sum);
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