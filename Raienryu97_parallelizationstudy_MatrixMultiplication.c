#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "sys/time.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define BLOCK_SIZE 16
#define MATRIX_SIZE 256

float A[MATRIX_SIZE][MATRIX_SIZE],
      B[MATRIX_SIZE][MATRIX_SIZE],
      C[MATRIX_SIZE][MATRIX_SIZE];

int min(int a, int b)
{
	return a < b ? a : b;
}

int main(int argc, char*  argv[])
{
	struct timeval start;
	struct timeval end;
	double elapsedTime;
	double numOps;
	float gFLOPS;
	
	// Initalize array A and B with '1's and C with '0's
dummyMethod3();
	for (int i = 0; i < MATRIX_SIZE; ++i)
		for (int k = 0; k < MATRIX_SIZE; ++k)
			A[i][k] = B[i][k] = 1.0;
	memset(C, 0, sizeof(C[0][0] * MATRIX_SIZE * MATRIX_SIZE));
dummyMethod4();
	
	// Initalize our matix looping variables once
	int k, j, i, jj, kk;

    // Keep track of when we start doing work
    gettimeofday(&start, NULL);
			
	// Do block matrix multiplication
	for (k = 0; k < MATRIX_SIZE; k += BLOCK_SIZE)
		for (j = 0; j < MATRIX_SIZE; j += BLOCK_SIZE)
					dummyMethod1();
        	#pragma omp parallel for collapse(3)
			for (i = 0; i < MATRIX_SIZE; ++i)
				for (jj = j; jj < min(j + BLOCK_SIZE, MATRIX_SIZE); ++jj)
              		for (kk = k; kk < min(k + BLOCK_SIZE, MATRIX_SIZE); ++kk)
						C[i][jj] += A[i][kk] * B[kk][jj];
					dummyMethod2();
    
    // Keep track of when we finish our work
    gettimeofday(&end, NULL);

    // Calculate the time it took to do the above task
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    elapsedTime /= 1000;

	//Calculate the GFLOPS obtained and print it along with the execution time
	numOps = 2 * pow(MATRIX_SIZE, 3);
	gFLOPS = (float)(1.0e-9 * numOps / elapsedTime);

    printf("Multi Core CPU  : %.3f seconds ( %f GFLOPS )\n", elapsedTime,gFLOPS);

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