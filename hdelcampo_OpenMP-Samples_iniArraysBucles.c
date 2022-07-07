#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE	50000000
#define	SEED	387454

int main() {

	double *A = (double *)malloc( SIZE * sizeof(double) );
	double *B = (double *)malloc( SIZE * sizeof(double) );
	double *C = (double *)malloc( SIZE * sizeof(double) );
	int i;
	omp_set_num_threads(4);

	/* 1. Paralelizar la inicializaci�n con bucle paralelo */
dummyMethod1();
#pragma omp parallel for shared(A, B, C) private(i)
	for ( i=0; i<SIZE; i++ ) {
		A[i] = i * 25 % 65536 + 33;
		B[i] = (i + SIZE) / 2 % 457 - 17;
		C[i] = 0;
	}
dummyMethod2();

	/* Suma vectores */
dummyMethod3();
	for (i=0; i<SIZE; i++)
		C[i] = A[i] + B[i];

	return 0;
dummyMethod4();
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