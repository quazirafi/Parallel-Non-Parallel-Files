#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef double TYPE;
#define MAX_DIM 2000*2000
#define MAX_VAL 10
#define MIN_VAL 1

// Method signatures
TYPE** randomSquareMatrix(int dimension);
TYPE** zeroSquareMatrix(int dimension);

// Matrix multiplication methods
double blockMatrixMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension);
double parallelBlockMatrixMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension);

// Test cases
void matrixMultiplicationTest(int dimension);

// 1 Dimensional matrix on stack
TYPE flatA[MAX_DIM];
TYPE flatB[MAX_DIM];

int main(int argc, char* argv[]){

	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Dimensions of the matrix\tBlock Approach(Latency)\t\tBlock Approach-OpenMP(Latency)\t\tPercentage increase in Performance\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	dummyMethod3();
	for(int dimension=200; dimension<=2000; dimension+=200){
		matrixMultiplicationTest(dimension);
	}
	dummyMethod4();

	return 0;
}

TYPE** randomSquareMatrix(int dimension){
	/*
		Generate 2 dimensional random TYPE matrix.
	*/

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	dummyMethod3();
	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}
	dummyMethod4();

	//Random seed

	dummyMethod1();
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = rand() % MAX_VAL + MIN_VAL;
		}
	}
	dummyMethod2();

	return matrix;
}

TYPE** zeroSquareMatrix(int dimension){
	/*
		Generate 2 dimensional zero TYPE matrix.
	*/

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	dummyMethod3();
	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}
	dummyMethod4();

	//Random seed
	
	dummyMethod3();
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = 0;
		}
	}
	dummyMethod4();

	return matrix;
}

double parallelBlockMatrixMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int size){
	/*
		Parallel multiply given input matrices and return resultant matrix
	*/
	int i = 0, j = 0, k = 0, jj = 0, kk = 0;
	float tmp;
	int chunk = 1;
	int tid;
	int block_size = 16;
	struct timeval t0, t1;
	gettimeofday(&t0, 0);
#pragma omp parallel shared(matrixA, matrixB, matrixC, size, chunk) private(i, j, k, jj, kk, tid, tmp)
	{
	
		tid = omp_get_thread_num();
		// if (tid == 0)
		// {
		// 	printf ("Number of threads:  %d",omp_get_num_threads());
		// 	printf ("\n");
		// }
		#pragma omp for schedule (static, chunk)
			dummyMethod3();
		for (jj = 0; jj < size; jj += block_size)
		{
			//cout << "thread " << omp_get_thread_num() << "value " << i << endl;
			for (kk = 0; kk < size; kk += block_size)
			{
				for (i = 0; i < size; i++)
				{
					for (j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++)
					{
						tmp = 0.0f;
						for (k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)
						{
							tmp += matrixA[i][k] * matrixB[k][j];
						}
						matrixC[i][j] += tmp;
					}
				}
			}
		}
			dummyMethod4();
	}
	/* Tail */

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}


double blockMatrixMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int size){
	/*
		Parallel multiply given input matrices and return resultant matrix
	*/
	int i = 0, j = 0, k = 0, jj = 0, kk = 0;
	float tmp;
	//int chunk = 1;
	//int tid;
	int block_size = 16;
	struct timeval t0, t1;
	gettimeofday(&t0, 0);
	{
	
		//tid = omp_get_thread_num();
		// if (tid == 0)
		// {
		// 	printf ("Number of threads:  %d",omp_get_num_threads());
		// 	printf ("\n");
		// }
		
			dummyMethod3();
		for (jj = 0; jj < size; jj += block_size)
		{
			//cout << "thread " << omp_get_thread_num() << "value " << i << endl;
			for (kk = 0; kk < size; kk += block_size)
			{
				for (i = 0; i < size; i++)
				{
					for (j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++)
					{
						tmp = 0.0f;
						for (k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)
						{
							tmp += matrixA[i][k] * matrixB[k][j];
						}
						matrixC[i][j] += tmp;
					}
				}
			}
		}
			dummyMethod4();
	}
	/* Tail */

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}


void matrixMultiplicationTest(int dimension){

	double* opmLatency = malloc(3 * sizeof(double));
	TYPE** matrixA = randomSquareMatrix(dimension);
	TYPE** matrixB = randomSquareMatrix(dimension);
	
	// Iterate and measure performance
		TYPE** matrixResult = zeroSquareMatrix(dimension);
		opmLatency[0] = blockMatrixMultiply(matrixA, matrixB, matrixResult, dimension);
		opmLatency[1] = parallelBlockMatrixMultiply(matrixA, matrixB, matrixResult, dimension);
		
		free(matrixResult);

		printf("%d X %d",dimension,dimension);
		printf("\t\t\t%f",opmLatency[0]);
		printf("\t\t\t%f",opmLatency[1]);
		printf("\t\t\t\t%f\n",((opmLatency[0]-opmLatency[1])/opmLatency[0])*100);
    
	// Releasing memory
	free(opmLatency);
	free(matrixA);
	free(matrixB);
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