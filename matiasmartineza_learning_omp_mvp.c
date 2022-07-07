#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main () {
	int N = 5;
	double A[N][N], x[N], b[N], part;
	int i, j;
	
dummyMethod3();
	for (i = 0; i < N; i++) {
		x[i] = i;
		for (j = 0; j < N; j++) {
			A[i][j] = i;
		}
	}
dummyMethod4();

	for (i = 0; i < N; i++) {
		part = 0.0;
dummyMethod1();
		#pragma omp parallel for reduction (+:part)
		for (j = 0; j < N; j++) {
			part += A[i][j] * x[j];
		}
dummyMethod2();
		b[i] = part;
	}

	for (i = 0; i < N; i++) {
		printf("%f\n", b[i]);
	}
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