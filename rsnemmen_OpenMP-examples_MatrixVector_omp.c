/*
Create a program that computes a simple matrix vector multiplication 
b=Ax, either in fortran or C/C++. Use OpenMP directives to make 
it run in parallel.

This is the parallel version.
*/

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
	float A[2][2] = {{1,2},{3,4}};
	float b[] = {8,10};
	float c[2];
	int i,j;

	// computes A*b
dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<2; i++) {
		c[i]=0;
		for (j=0;j<2;j++) {
			c[i]=c[i]+A[i][j]*b[j];
		}
	}
dummyMethod2();

	// prints result
dummyMethod3();
	for (i=0; i<2; i++) {
		printf("c[%i]=%f \n",i,c[i]);
	}
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