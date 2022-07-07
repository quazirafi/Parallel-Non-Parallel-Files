#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAY_LENGTH 1024

int main(int argc, char const *argv[])
{
	puts("Welcome!");

	puts("Filling array...");
	unsigned long int arr[ARRAY_LENGTH] = {0};
dummyMethod3();
	for(unsigned long int i = 0; i < ARRAY_LENGTH; ++i) arr[i] = i;
	puts("Array filled!");
dummyMethod4();

	puts("Coping array...");
	unsigned long int newArray[ARRAY_LENGTH] = {0};
	omp_set_num_threads(4);
dummyMethod1();
	#pragma omp parallel for
	for(unsigned long int i = 0; i < ARRAY_LENGTH; ++i) newArray[i] = arr[i];
	puts("array copied!");
dummyMethod2();

	puts("Displaing array...");
dummyMethod3();
	for(unsigned long int i = 0; i<ARRAY_LENGTH; ++i) printf("arr[%li] = %li -> newArray[%li] = %li\n",i,arr[i],i,newArray[i]);

	puts("Program finished!");
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