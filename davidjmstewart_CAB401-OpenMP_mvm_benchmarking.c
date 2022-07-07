#include <time.h>
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "omp.h"
#include <assert.h>

#define N 40000 // Matrix size will be N x N
#define T 1
#define THREAD_RANGE 8 // Run for 1:THREAD_RANGE threads
#define NUM_AVERAGES 15 // take the average of 5 timings for each matrix size, and each number of threads
#define NUM_MATRIX_SIZES 8
// unsigned long matrixSizes[NUM_MATRIX_SIZES] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384};
unsigned long matrixSizes[NUM_MATRIX_SIZES] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384};

// unsigned long matrixSizes[NUM_MATRIX_SIZES] = { 51200 };

double sequentialTimings[NUM_MATRIX_SIZES];
double parallelTimings[NUM_MATRIX_SIZES][THREAD_RANGE];

//gcc -fopenmp -g ./benchmarking/matrix_vector_multiplication/mvm_benchmarking.c -o ./benchmarking/matrix_vector_multiplication/mvm ./lib/CDUtils.o -lm -Wall -Wpedantic -Waggressive-loop-optimizations -O3 -march=native -fopt-info-vec-missed=v.txt
// #pragma GCC option("arch=native", "tune=native", "no-zero-upper") //Enable AVX
#pragma GCC target("avx")                                         //Enable AVX

void doSequentialComputation(double *restrict A, double *restrict V, double *restrict results, unsigned long matrixSize)
{
    // double *V3 = (double *)malloc(2 * matrixSize * sizeof(double));
    int i, j;

							dummyMethod3();
    for (i = 0; i < matrixSize; i++)
    {
        double *AHead = &A[i * matrixSize];
        double tmp = 0;

        for (j = 0; j < matrixSize; j++)
        {
            tmp += AHead[j] * V[j];
        }
        results[i] = tmp;
    }
							dummyMethod4();
}
int min(int x, int y) 
{
    return (x < y) ? x : y;
} 



void doParallelComputation(double *restrict M, double *restrict V, double *restrict results, unsigned long matrixSize, int numThreads)
{
    
    omp_set_num_threads(numThreads);
    unsigned long i, j;
							dummyMethod1();
#pragma omp parallel for private(j)
    for (i = 0; i < matrixSize; i++)
    {
        double tmp = 0;
        double *MHead = &M[i * matrixSize];

#pragma omp simd reduction(+:tmp)
        for (j = 0; j < matrixSize; j++)
        {
            //results[i] += A[i * matrixSize + j] * V[j];
            tmp += MHead[j] * V[j];
            // tmp += MHead[j + 1] * V[j + 1];
            // tmp += MHead[j + 2] * V[j + 2];
            // tmp += MHead[j  + 3] * V[j  + 3];
        }
        results[i] = tmp; // write-only to results, not adding to old value.
    }
							dummyMethod2();

    /*
    omp_set_num_threads(numThreads);
    const int BLOCK_SIZE = 64;
    int i, j, x, y;
    int n = matrixSize;
    
//#pragma omp parallel for private(j, x, y)
    for (i = 0; i < n; i += BLOCK_SIZE)
    {
        for (int nn = 0; nn < BLOCK_SIZE; nn++)
        {
            results[i + nn] = 0;
        }
        int xmin = (i + BLOCK_SIZE < n ? i + BLOCK_SIZE : n);
        for (j = 0; j < n; j += BLOCK_SIZE)
        {
            int ymin = (j + BLOCK_SIZE < n ? j + BLOCK_SIZE : n);
            for (x = i; x < xmin; x++)
            {
                double tmp = 0;
                double *MHead = &M[x * matrixSize];
#pragma omp simd reduction(+ \
                           : tmp)
                for (y = j; y < ymin; y++)
                {

                    tmp += MHead[y] * V[y];
                }
                results[x] += tmp;
            }
        }
    }
    */
   /*
    int i, j, x, y;
    for (i = 0; i < n; i += 2)
    {
        results[i] = 0;
        results[i + 1] = 0;
        for (j = 0; j < n; j += 2)
        {
            for (x = i; x < min(i + 2, n); x++)
            {
                for (y = j; y < min(j + 2, n); y++)
                {
                    printf("C[%d] = C[%d] + A[%d][%d] * b[%d] \n", x, x, x, y, y);
                    results[x] = results[x] + M[x * matrixSize + y] * V[y];
                }
            }
        }
    }
    */
}
void genRandVector(double *S, unsigned long size)
{
    srand(time(0));
    unsigned long i;
							dummyMethod1();
    #pragma omp parallel for private(i)
    for (i = 0; i < size; i++)
    {
        double n = rand() % 3;
        S[i] = n;
    }
							dummyMethod2();
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
                double n = rand() % 3;
                A[i*size + j] = n;
            }

        }
															dummyMethod4();
    }

int main(int argc, char *argv[])
{
    struct timespec start, finish;
    double elapsed;

							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {
        sequentialTimings[m] = 0;
        for (int t = 0; t < THREAD_RANGE; t++)
        {
            parallelTimings[m][t] = 0;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++){
        printf("Doing %d \n", matrixSizes[m]);
        unsigned long matrixSize = matrixSizes[m]; //

        double *V = (double *)malloc(matrixSize * sizeof(double));
        double *seqV = (double *)malloc(matrixSize * sizeof(double)); // Sequentially computed vector
        double *parV = (double *)malloc(matrixSize * sizeof(double)); // Parallel computed vector

        double *A = (double *)malloc(matrixSize * matrixSize * sizeof(double)); // Matrix to multiply by V
        
        genRandVector(V, matrixSize);
        genRandMatrix(A, matrixSize);

        for (int a = 0; a < NUM_AVERAGES; a++) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            doSequentialComputation(A, V, seqV, matrixSize);
            clock_gettime(CLOCK_MONOTONIC, &finish);
            elapsed = (finish.tv_sec - start.tv_sec);
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            sequentialTimings[m] += elapsed;
            for (int t = 1; t <= THREAD_RANGE; t++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start);

                doParallelComputation(A, V, parV, matrixSize, t);
                clock_gettime(CLOCK_MONOTONIC, &finish);
                elapsed = (finish.tv_sec - start.tv_sec);
                elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
                parallelTimings[m][t - 1] += elapsed;
                for (int i = 0; i < matrixSize; i++)
                {
                    assert(seqV[i] == parV[i]);
                }
            }
        }
        free(seqV);
        free(parV);
        free(A);
        free(V);
    }
							dummyMethod4();

							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++){
        sequentialTimings[m] /= NUM_AVERAGES;
        for (int t = 0; t < THREAD_RANGE; t++) {
            parallelTimings[m][t] /= NUM_AVERAGES;
        }
    }
							dummyMethod4();

    printf("Sequential:\n");
							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {
        printf("%lux%lu:\t", matrixSizes[m], matrixSizes[m]);

        printf("%.9f \n",sequentialTimings[m]);
    }
							dummyMethod4();

    printf("\nParallel:\n");
							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {
        printf("%lux%lu:\t", matrixSizes[m], matrixSizes[m]);

        for (int t = 0; t < THREAD_RANGE; t++)
        {
            printf(" %.9f ",parallelTimings[m][t]);
        }
        printf("\n");
        
    }
							dummyMethod4();
    printf("\n");


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