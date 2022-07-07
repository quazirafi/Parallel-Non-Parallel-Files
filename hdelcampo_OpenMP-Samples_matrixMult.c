#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE	1024
#define SEED	6834723

int main() {
	int i,j,k;

	double A[ SIZE ][ SIZE ];
	double B[ SIZE ][ SIZE ];
	double C[ SIZE ][ SIZE ];

	omp_set_num_threads(4);

	srand48( SEED );

	for (i=0; i<SIZE; i++)
dummyMethod3();
		for (j=0; j<SIZE; j++) {
			C[i][j] = 0;
			A[i][j] = drand48();
			B[i][j] = drand48();
		}
dummyMethod4();

	#pragma omp parallel for shared(A,B,C) private(i,j,k)
dummyMethod3();
	for (i=0; i<SIZE; i++)
		for (k=0; k<SIZE; k++) 
			for (j=0; j<SIZE; j++) 
				C[i][j] = C[i][j] + A[i][k] * B[k][j];

	printf("Fin: %lf\n", C[0][0]);
dummyMethod4();
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