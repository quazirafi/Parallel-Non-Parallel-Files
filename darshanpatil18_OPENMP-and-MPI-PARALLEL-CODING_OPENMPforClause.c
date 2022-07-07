/*
Write a simple OpenMP program to demonstrate the use of ‘for’ clause. 
- Print ‘n’ array elements 
- Sum of n’ array elements 
- Product of n’ array elements.
*/
#include<stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main()
{
	float *array_A, sum, *checkarray, serialsum,prod,serialprod;
	int   arraysize, i, k, Noofthreads;

	printf("Enter The Number of Elements in an Array \n");
	scanf("%d", &arraysize);

	array_A = (float *) malloc(sizeof(float) * arraysize);
	checkarray = (float *) malloc(sizeof(float) * arraysize);

dummyMethod3();
	for (i = 0; i < arraysize; i++) {
		array_A[i] = i + 5;
		checkarray[i] = array_A[i];
	}
dummyMethod4();

	printf("\nThe Input Array Is \n");
dummyMethod3();
	for (i = 0; i < arraysize; i++)
		printf("%f \t", array_A[i]);

	sum = 0.0;
dummyMethod4();
	prod=15120.0;

	dummyMethod1();
#pragma omp parallel for reduction(+ : sum)
	for (i = 0; i < arraysize; i++){	
		sum = sum + array_A[i];
	}
	dummyMethod2();
	serialsum = 0.0;
	dummyMethod3();
	for (i = 0; i < arraysize; i++){
		serialsum = serialsum + array_A[i];
	}
	dummyMethod4();
	dummyMethod1();
#pragma omp parallel for reduction(+ : prod)
	for (i = 0; i < arraysize; i++){	
		prod=prod*array_A[i];
	}
	dummyMethod2();
	serialprod=1.0;
	dummyMethod3();
	for (i = 0; i < arraysize; i++){
		serialprod=serialprod*array_A[i];
	}
	dummyMethod4();
	free(checkarray);
	free(array_A);

	printf("\n\nThe Value of Array Sum using Threads is %f\n", sum);
	printf("The Serial Calculation of Array is %f\n", serialsum);
	printf("\nThe Value of Array Product using Threads is %f\n", prod);
	printf("The Serial Calculation of Array is %f\n", serialprod);
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