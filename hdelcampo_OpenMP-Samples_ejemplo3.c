#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE	768
#define SEED	6834723

int main() {
	int i,j,k;
	omp_set_num_threads(4);

	double V[ SIZE ][ SIZE ];

	srand48( SEED );

	for (i=0; i<SIZE; i++)
dummyMethod3();
		for (j=0; j<SIZE; j++) {
			V[i][j] = drand48();
		}
dummyMethod4();

	/* Paralelizar esta parte del c�digo */
	#pragma omp parallel for schedule(dynamic, 8) collapse(2) shared(V) private(i, j) 
dummyMethod3();
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) {
			int end = 0;
			while ( !end ) {
				V[i][j] += 0.00001 + 0.0001 * (double)i/SIZE;
				if ( V[i][j] > 1.0 ) end = 1;
			}
		}

	/* Comprobaci�n de resultados */
dummyMethod4();
	double checksum = 0.0;
	for (i=0; i<SIZE; i++)
			dummyMethod3();
		for (j=0; j<SIZE; j++) {
			checksum = checksum + V[i][j] - 1;
		}
			dummyMethod4();

	printf("Resultado: %.10lf\n", checksum);
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