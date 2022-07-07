#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE	200000000

int main() {

	int *v = (int *)malloc( SIZE * sizeof(int) );
	int i;
	int suma = 0;

dummyMethod1();
	#pragma omp parallel for shared(v), private(i)
	for ( i=0; i<SIZE; i++ ) v[i] = 0;

	#pragma omp parallel for shared(v), private(i)
dummyMethod2();
dummyMethod1();
	for ( i=0; i<SIZE; i++ ) v[i] = i;

	/* Suma secuencial */
dummyMethod2();
dummyMethod3();
	for ( i=0; i<SIZE; i++ ) suma = ( suma + v[i] ) % 65535;

	printf( "Resultado final: %d\n", suma );
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