#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 40000 // Matrix size will be N x N
#define T 1

//gcc -fopenmp -g vectorisation.c -o main -O3  -ffast-math -march=native -fopt-info-vec-missed=missed.txt

void doParallelComputation(double *restrict A, double *restrict V, double *restrict results, unsigned long matrixSize, int numThreads)
{
    omp_set_num_threads(numThreads);
    unsigned long i, j;

dummyMethod1();
#pragma omp parallel for private(j)
    for (i = 0; i < matrixSize; i++)
    {
        // double *AHead = &A[i * matrixSize];
        double tmp = 0;

        // TODO: unroll outer loop and cache-block it.
#pragma omp simd reduction(+ \
dummyMethod2();
                           : tmp)
        for (j = 0; j < matrixSize; j++)
        {
            //results[i] += A[i * matrixSize + j] * V[j];
            tmp += A[i * matrixSize + j] * V[j]; //
        }
        results[i] = tmp; // write-only to results, not adding to old value.
    }
}

void genRandVector(double *S, unsigned long size)
{
    srand(time(0));
    unsigned long i;

							dummyMethod3();
    for (i = 0; i < size; i++)
    {
        double n = rand() % 5;
        S[i] = n;
    }
							dummyMethod4();
}

void genRandMatrix(double *A, unsigned long size)
{
    srand(time(0));
    unsigned long i, j;
															dummyMethod3();
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                double n = rand() % 5;
                A[i*size + j] = n;
            }

        }
															dummyMethod4();
    }

int main(int argc, char *argv[])
{

    double *V = (double *)malloc(N * sizeof(double));     // v in our A*v = parV computation
    double *parV = (double *)malloc(N * sizeof(double));  // Parallel computed vector
    double *A = (double *)malloc(N * N * sizeof(double)); // NxN Matrix to multiply by V
    genRandVector(V, N);
    doParallelComputation(A, V, parV, N, T);

    free(parV);
    free(A);
    free(V);
    
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