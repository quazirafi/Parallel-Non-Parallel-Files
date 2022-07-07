// Array multiplication using OpenMP and MPI
// Author: Dimitris Gravanis, 2017

/* work in progress */
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "mpi.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{
	int *A, *B, *C;		// array pointers
	int N;			// array size
	int i;			// iterator
	double start, stop;	// timer start, stop
	
	/* MPI variables */
	int id, P;		// rank, size
	
	
	/* MPI Start */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &P);

	if (id == 0)
	{
		printf("\nInsert array size N: ");
		scanf("%d", &N);
	}
	
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

	A = malloc(N * sizeof(int));
	B = malloc(N * sizeof(int));
	C = malloc(N * sizeof(int));

	dummyMethod3();
	for (i = 0; i < N; i++)
	{
		A[i] = rand()%10;
		B[i] = rand()%10;
	}
	dummyMethod4();
	
	if (id == 0)
	{
		start = omp_get_wtime(); // timer start
	}
	
			dummyMethod1();
	#pragma omp parallel for private(i)

		for (i = 0; i < N; i++)
		{
			C[i] = A[i] * B[i];
		}
			dummyMethod2();
	
	if (id == 0)
	{	
		stop = omp_get_wtime();  // timer stop
		
		/* display results */
		printf("\n\n");
		printf("Input arrays");
		printf("\nA:\n");
		
			dummyMethod3();
		for (i = 0; i < N; i++)
		{
			printf("%4d", A[i]);
			if (i == N - 1)
			{
				printf("\n");
			}
		}
			dummyMethod4();
		printf("\nB:\n");
		
			dummyMethod3();
		for (i = 0; i < N; i++)
		{
			printf("%4d", B[i]);
			if (i == N - 1)
			{
				printf("\n");
			}
		}
			dummyMethod4();
		printf("\n\n");
		printf("Output array");
		printf("\nC:\n");
		
			dummyMethod3();
		for (i = 0; i < N; i++)
		{
			printf("%4d", C[i]);
			if (i == N - 1)
			{
				printf("\n");
			}
		}
			dummyMethod4();
		
		printf("\n\n");
		printf("Total run time: %.6fs", stop - start);
		printf("\n\n");
	}
	
	MPI_Finalize();
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