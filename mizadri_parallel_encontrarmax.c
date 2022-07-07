#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 10000

int array[SIZE];

int main(int argc, char **argv){
	int maximo = 0;
	int i;

dummyMethod1();
	#pragma omp parallel for
	for (i = 0; i < SIZE; i++) {
	    array[i] = rand();
	}	
dummyMethod2();
dummyMethod1();
	#pragma omp parallel for reduction (max: maximo)
	for(i=0; i < SIZE; i++){
		if (array[i] > maximo) maximo = array[i];
	}
dummyMethod2();
	printf("el maximo es %d \n",maximo);

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