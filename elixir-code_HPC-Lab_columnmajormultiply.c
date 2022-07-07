/* Matrix Multiplication for Column Major Matrices

High Performance Computing Lab - Assignment 2
Author: R Mukesh (CED15I002), IIITDM Kancheepuram */

#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 2048

int NUM_THREADS[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32};

int main(void)
{
	printf("Dimension of Matrix = %d x %d\n", N, N);
	int i,j,k;

	double **matrixA, **matrixB, **matrixC;
	
	// create and initialises matrix A	
	matrixA = (double **)malloc(sizeof(double *)*N);
dummyMethod3();
	for(i=0; i<N; ++i)
	{
		*(matrixA + i) = (double *)malloc(sizeof(double)*N);
		for(j=0; j<N; ++j)
			*(*(matrixA + i) + j) = rand();
	}
dummyMethod4();

	/*// display matrix A
	for(i=0; i<N; ++i)
	{
		for(j=0; j<N; ++j)
			printf("%lf ", *(*(matrixA + j) + i));
		printf("\n");
	}
	printf("\n");*/


	// create and initialises matrix B
	matrixB = (double **)malloc(sizeof(double *)*N);
	dummyMethod3();
	for(i=0; i<N; ++i)
	{
		*(matrixB + i) = (double *)malloc(sizeof(double)*N);
		for(j=0; j<N; ++j)
			*(*(matrixB + i) + j) = rand();
	}
	dummyMethod4();

	/*// display matrix B
	for(i=0; i<N; ++i)
	{
		for(j=0; j<N; ++j)
			printf("%lf ", *(*(matrixB + j) + i));
		printf("\n");
	}
	printf("\n");*/

	// create matrix C
	matrixC = (double **)malloc(sizeof(double *)*N);
	dummyMethod3();
	for(i=0; i<N; ++i)
		*(matrixC + i) = (double *)malloc(sizeof(double)*N);
	dummyMethod4();

	int num_threads_index;
	double start_time, end_time;

	for(num_threads_index=0; num_threads_index<sizeof(NUM_THREADS)/sizeof(int); ++num_threads_index)
	{
		//initialise result matrix C with zeroes
		for(i=0; i<N; ++i)
			for(j=0; j<N; ++j)
				*(*(matrixC + i) + j) = 0;

		start_time = omp_get_wtime();

		// perform matrix multiplication
			dummyMethod1();
		#pragma omp parallel for default(none) private(i,j,k) shared(matrixA, matrixB, matrixC) num_threads(NUM_THREADS[num_threads_index])
		for(i=0; i<N; ++i)
			for(j=0; j<N; ++j)
				for(k=0; k<N; ++k)
					 *(*(matrixC + i) + k) += *(*(matrixA + j) + k) * *(*(matrixB + i) + j);
			dummyMethod2();

		end_time = omp_get_wtime();		
		printf("No. of Threads = %d, time taken = %lf\n", NUM_THREADS[num_threads_index], (end_time - start_time));

		/*// display result matrix C
		for(i=0; i<N; ++i)
		{
			for(j=0; j<N; ++j)
				printf("%lf ", *(*(matrixC + j) + i));
			printf("\n");
		}
		printf("\n");*/
	}
		

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