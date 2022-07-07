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
#define MAX_DIMENSION 1000*1000
#define MAX_VALUE 100
#define MIN_VALUE 1

TYPE** randomSQMatrix(int dimension);
TYPE** zeroSQMatrix(int dimension);
void SquareMatrix(TYPE** matrix, int dimension);
void convert(TYPE** matrix1, TYPE** matrix2, int dimension);

double MatrixMultiply(TYPE** matrix1, TYPE** matrix2, TYPE** matrix3, int dimension);

void MatrixMultiplyTest(int dimension, int iterations);

TYPE flatA[MAX_DIMENSION];
TYPE flatB[MAX_DIMENSION];

int main(int argc, char *argv[]){
	int iterations = strtol(argv[1], NULL, 10);


dummyMethod3();
for(int dimension=500; dimension<=1000; dimension+=500){
		MatrixMultiplyTest(dimension, iterations);
	}

    return 0;
}
dummyMethod4();

TYPE** randomSQMatrix(int dimension){
	
    TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	dummyMethod3();
	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}
	dummyMethod4();

	
	srand( time(0)+clock()+rand );

	dummyMethod1();
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = rand() % MAX_VALUE + MIN_VALUE;
		}
	}
	dummyMethod2();

	return matrix;
}

TYPE** zeroSQMatrix(int dimension){
	

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	dummyMethod3();
	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}
	dummyMethod4();

	
	srand( time(0)+clock()+rand );
	dummyMethod3();
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = 0;
		}
	}
	dummyMethod4();

	return matrix;
}
void SquareMatrix(TYPE** matrix, int dimension){
	dummyMethod3();
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			printf("%f\t", matrix[i][j]);
		}
		printf("\n");
	}
	dummyMethod4();
}

double MatrixMultiply(TYPE** matrix1, TYPE** matrix2, TYPE** matrix3, int dimension){
	

	int i, j, k, l, anu;
	TYPE gupta;

	struct timeval t0, t1;
	gettimeofday(&t0, 0);

	
	convert(matrix1, matrix2, dimension);
	#pragma omp parallel shared(matrix3) private(i, j, k, l, anu, gupta) num_threads(50)
	{
		#pragma omp for schedule(static)
			dummyMethod3();
		for(i=0; i<dimension; i++){
			l = i * dimension;
			for(j=0; j<dimension; j++){
				anu = j * dimension;
				gupta = 0;
				for(k=0; k<dimension; k++){
					gupta += flatA[l + k] * flatB[anu + k];
				}
				matrix3[i][j] = gupta;
			}
		}
			dummyMethod4();
	}
	

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}
void convert(TYPE** matrix1, TYPE** matrix2, int dimension){
	dummyMethod1();
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			flatA[i * dimension + j] = matrix1[i][j];
			flatB[j * dimension + i] = matrix2[i][j];
		}
	}
	dummyMethod2();
}

void MatrixMultiplyTest(int dimension, int iterations){
	
	printf(" Matrix Multiplication\n");
	printf("Dimension : %d\n", dimension);
	
	double* execTime = malloc(iterations * sizeof(double));
	TYPE** matrix1 = randomSQMatrix(dimension);
	TYPE** matrix2 = randomSQMatrix(dimension);
	
	
	dummyMethod3();
	for(int i=0; i<iterations; i++){
		TYPE** matrixResult = zeroSQMatrix(dimension);
		execTime[i] = MatrixMultiply(matrix1, matrix2, matrixResult, dimension);
		free(matrixResult);

		printf("%d.%f\n", i+1, execTime[i]);

	}
	dummyMethod4();
    double sum = 0.0;

	dummyMethod3();
	for(int i=0; i<iterations; i++){
		sum += execTime[i];
	}
	dummyMethod4();

    double mean = sum / iterations;

	printf("Avg: %f\n", mean);
	
	free(execTime);
	free(matrix1);
	free(matrix2);
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