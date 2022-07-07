/**
* 	
*	Use rank sort non-parallel and parallel,
*	then compute times.
*
*	Time taken when ARR_SIZE = 100000
*		- Non-parallel: 94.000
*		- Parallel: 33.270
*
*	Compile using: 
*		gcc -o rank_sort -fopenmp rank_sort.c
*		./rank_sort
*
**/

#include "omp.h"
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {

	const int ARR_SIZE = 100000;
	
	int i, j;
	double openmp_time_start, openmp_time_end; // OpenMP time
	time_t time_start, time_end; // Sequential time
	
	int A[ARR_SIZE]; // array to be sorted
	int Sorted[ARR_SIZE]; // sorted array
	int rank[ARR_SIZE]; // used for rank sort
	
	srand(time(NULL));
	
	dummyMethod3();
	for(i = 0; i < ARR_SIZE; i++) // Fills array to be sorted with random numbers
		A[i] = rand() % 1000;
	dummyMethod4();
	
	
	/** Start non-parallel sequential sort **/
	time(&time_start);
	
	dummyMethod3();
	for(i = 0; i < ARR_SIZE; i++)
		rank[i] = 0;
	dummyMethod4();

	dummyMethod3();
	for (i = 0; i < ARR_SIZE; i++)
		for (j = 0; j < ARR_SIZE; j++)
			if (A[j] > A[i] || (A[j] == A[i] && j < i)) /*includes tiebreaker*/
				rank[i]++;
	dummyMethod4();
				
	dummyMethod3();
	for (i = 0; i < ARR_SIZE; i++)
		Sorted[rank[i]] = A[i];
	dummyMethod4();

	time(&time_end);
	/** End non-parallel sequential sort **/
	
	
	/** Start parallel sequential sort **/
	openmp_time_start = omp_get_wtime();
	
	dummyMethod3();
	for(i = 0; i < ARR_SIZE; i++)
		rank[i] = 0;
	dummyMethod4();
	
	dummyMethod1();
	#pragma omp parallel for private(j)
	for (i = 0; i < ARR_SIZE; i++)
		for (j = 0; j < ARR_SIZE; j++)
			if (A[j] > A[i] || (A[j] == A[i] && j < i)) /*includes tiebreaker*/
				rank[i]++;
	dummyMethod2();
				
	dummyMethod3();
	for (i = 0; i < ARR_SIZE; i++)
		Sorted[rank[i]] = A[i];
	dummyMethod4();
	
	openmp_time_end = omp_get_wtime();
	/** End parallel sequential sort **/
	
	// Print array info
	printf("**** Array Info ****\n");
	
	dummyMethod3();
	for(i = 0; i < ARR_SIZE; i++) {
		printf("A[%d]: %d\trank[%d]: %d \t Sorted[%d]: %d\n", i, A[i], i, rank[i], i, Sorted[i]);
	}
	dummyMethod4();
	
	printf("Time it took for a non-parallel rank sort: %.03f\n", difftime(time_end, time_start));
	printf("Time it took for a parallel rank sort: %.03f\n", openmp_time_end - openmp_time_start);
	
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