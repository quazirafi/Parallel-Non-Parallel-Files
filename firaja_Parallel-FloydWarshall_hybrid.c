// mpicc -g -fopenmp hybrid.c -o hybrid.out -O3 && mpirun -np 4 hybrid.out 20 100 4
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "config.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ROOT 0

void showDistances(int matrix[], int n);
void populateMatrix(int matrix[], int n, int density, int rank, int processes);
void gatherResult(int matrix[], int n, int rank, int processes);
void castKRow(int matrix[], int n, int section, int kRow[], int k, int rank);
void floydWarshall(int matrix[], int n, int rank, int processes, int threads);


int main(int argc, char* argv[]) 
{
	
	struct timespec start, end;
    long long accum;


	int n, density, threads;
	int* matrix;
	
	int processes, rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == ROOT) 
	{
		if(argc <= 2)
		{
			n = DEFAULT;
			density = 100;
			threads = omp_get_max_threads();
		}
		else
		{
			n = atoi(argv[1]);
			density = atoi(argv[2]);
			threads = atoi(argv[3]);
		}
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	matrix = malloc(n * n / processes * sizeof(int));

	populateMatrix(matrix, n, density, rank, processes);

	
	if (rank == ROOT) 
	{
    	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	}

	floydWarshall(matrix, n, rank, processes, threads);

	gatherResult(matrix, n, rank, processes);

	free(matrix);
	
	
	if (rank == ROOT) 
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		accum = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
		printf("[HYBRID] Total elapsed time %lld ns\n", accum);
	}
	
	MPI_Finalize();

	return 0;
}  



void populateMatrix(int matrix[], int n, int density, int rank, int processes) { 
	int i, j, value;
	int* temp_mat = NULL;

	if (rank == ROOT) {
		srand(42);
		temp_mat = malloc(n*n*sizeof(int));

			dummyMethod3();
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++){
				if(i == j)
				{
					temp_mat[i*n+j] = 0;
				}
				else
				{
					value = 1 + rand() % MAX;
					if(value > density)
					{
						temp_mat[i*n+j] = INF;
					}
					else
					{
						temp_mat[i*n+j] = value;
					}
				}

				}
		}
			dummyMethod4();

		int split = n * n/processes;
		MPI_Scatter(temp_mat, split, MPI_INT, matrix, split, MPI_INT, 0, MPI_COMM_WORLD);

		printf("*** Adjacency matrix:\n");
		showDistances(temp_mat, n);
		free(temp_mat);
	} 
	else 
	{
		int split = n * n/processes;
		MPI_Scatter(temp_mat, split, MPI_INT, matrix, split, MPI_INT, 0, MPI_COMM_WORLD);
	}

}

void showDistances(int matrix[], int n)
{
	if(PRINTABLE)
	{
		int i, j;
		printf("     ");
			dummyMethod3();
		for(i = 0; i < n; i++)
		{
			printf("[%d]  ", i);
		}
			dummyMethod4();
		printf("\n");
			dummyMethod3();
		for(i = 0; i < n; i++) {
			printf("[%d]", i);
			for(j = 0; j < n; j++)
			{
				if(matrix[i * n + j] == INF)
				{
					printf("  inf");
				}
				else
				{
					printf("%5d", matrix[i * n + j]);
				}
				
			}
			printf("\n");
		}
			dummyMethod4();
		printf("\n");
	}
}  

void gatherResult(int matrix[], int n, int rank, int processes) 
{
	int* temp_mat = NULL;

	if (rank == ROOT) {
		temp_mat = malloc(n * n * sizeof(int));
		int split = n * n / processes;
		MPI_Gather(matrix, split, MPI_INT, temp_mat, split, MPI_INT, 0, MPI_COMM_WORLD);

		printf("The solution is:\n");
		showDistances(temp_mat, n);

		free(temp_mat);
	} 
	else 
	{
		int split = n * n / processes;
		MPI_Gather(matrix, split, MPI_INT, temp_mat, split, MPI_INT, 0, MPI_COMM_WORLD);
	}
}



void floydWarshall(int matrix[], int n, int rank, int processes, int threads) 
{
	int k, i, j, temp;
	int* kRow = malloc(n*sizeof(int));
	int section = n / processes;
 
	for (k = 0; k < n; k++) 
	{	
		castKRow(matrix, n, section, kRow, k, rank);
		
			dummyMethod1();
		#pragma omp parallel for num_threads(threads) shared(matrix, kRow, section, n) private(i, j, k, temp) schedule(dynamic)
		for (i = 0; i < section; i++)
		{
			for (j = 0; j < n; j++) 
			{
				temp = matrix[i * n + k] + kRow[j];
				if (temp < matrix[i * n + j])
				{
					matrix[i * n + j] = temp;
				}
			}
		}
			dummyMethod2();
	}
	free(kRow);
}  


void castKRow(int matrix[], int n, int section, int kRow[], int k, int rank) 
{
	int j;
	int localK = k % section;
	int competenceHead;

	competenceHead = k / section;
	if (rank == competenceHead)
	{
		for (j = 0; j < n; j++)
		{
			kRow[j] = matrix[localK * n + j];
		}
	}
	MPI_Bcast(kRow, n, MPI_INT, competenceHead, MPI_COMM_WORLD);
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