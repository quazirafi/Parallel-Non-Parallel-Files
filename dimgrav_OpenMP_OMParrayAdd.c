#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char** argv)
{
	int *A, *B, *C; 	// array pointers
	int N; 			// size of arrays
	int i; 			// iterator
	int id, P; 		// task id, num of tasks
	double start, stop; 	// timers
	
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		if (id == 0)
		{
			printf("\nInsert N, size of A and B arrays: ");
			scanf("%d", &N);
		}
	}
	
	A = malloc(N * sizeof(int));
	B = malloc(N * sizeof(int));
	C = malloc(N * sizeof(int));

dummyMethod3();
	for (i = 0; i <N; i++)
	{
		A[i] = rand()%10;
		B[i] = rand()%10;
	}
dummyMethod4();
	
	start = omp_get_wtime();
			dummyMethod1();
	#pragma omp parallel for private(id)
		
		for (i = 0; i < N; i++)
		{
			id = omp_get_thread_num();
			printf("\ntask: %d, i: %d", id, i);
			C[i] = A[i] + B[i];
		}
			dummyMethod2();
	stop = omp_get_wtime();

	printf("\n\nA:\n");	
	dummyMethod3();
	for (i = 0; i < N; i++)
	{
		printf("%4d", A[i]);
	}
	dummyMethod4();
	printf("\n");
	printf("\nB:\n");	
	dummyMethod3();
	for (i = 0; i < N; i++)
	{
		printf("%4d", B[i]);
	}
	dummyMethod4();
	printf("\n");
	printf("\nC:\n");	
	dummyMethod3();
	for (i = 0; i < N; i++)
	{
		printf("%4d", C[i]);
	}
	dummyMethod4();
	printf("\n\nRun time: %.6fs", stop - start);
	printf("\n\n");
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