#include "omp.h"
#include <stdio.h>
#include <math.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ArraySize 32678
float Array[ArraySize];

float Ranf(float min, float max) {

	return min + (((float) rand() * (max-min))/ (float) (RAND_MAX));
}

int main( int argc, char *argv[ ] ) {

	int i,j;
	double prod;
	omp_set_num_threads( NUMT );

dummyMethod3();
	for (i=0; i< ArraySize-1 ;i++) {

		Array[i] = Ranf( -1.f, 1.f );
	}
dummyMethod4();
	double time0= omp_get_wtime( );
dummyMethod1();
#pragma omp parallel for shared(Array) private(prod) schedule(TYPE,CHUNK)	
	for (i=0; i< ArraySize-1 ;i++) {
		prod=1.0;
		for(j=0; j<=i ;j++) {

			prod*=Array[j];
		}
		
	}	
dummyMethod2();
	double time1=omp_get_wtime( );

	//printf("Execution time for = %lf\n",time1-time0);
	long int numMuled = (long int)ArraySize * (long int)(ArraySize+1) / 2;
	printf("MegaMults/sec = %10.2lf\n",(double)numMuled/(time1-time0)/1000000.);

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