#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "omp.h"
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 40000 // Matrix size will be N x N
#define T 1
#define THREAD_RANGE 8 // Run for 1:THREAD_RANGE threads
#define NUM_AVERAGES 500 // take the average of 5 timings for each matrix size, and each number of threads
#define NUM_MATRIX_SIZES 8
// unsigned long matrixSizes[NUM_MATRIX_SIZES] = {51200};

unsigned long matrixSizes[NUM_MATRIX_SIZES] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384};
// unsigned long matrixSizes[NUM_MATRIX_SIZES] = {100000, 200000, 500000, 1000000, 2000000, 3000000, 5000000, 10000000, 20000000, 50000000};

// unsigned long matrixSizes[NUM_MATRIX_SIZES] = { 51200 };

double sequentialTimings[NUM_MATRIX_SIZES];
double parallelTimings[NUM_MATRIX_SIZES][THREAD_RANGE];

//gcc -fopenmp -g dot_product_benchmarking.c -o dot  -Wall -Wpedantic -lm

double doSequentialComputation(double *D, double *A, unsigned long matrixSize)
{
    // double *V3 = (double *)malloc(2 * matrixSize * sizeof(double));


    unsigned long i;

    double result = 0.0;
							dummyMethod3();
    for (i = 0; i < matrixSize; i++)
            result += D[i] * A[i];
							dummyMethod4();

    return result;
}

double doParallelComputation(double *restrict D, double *restrict A, unsigned long matrixSize, int numThreads)
{
    omp_set_num_threads(numThreads);
    unsigned long i;
    double result = 0.0;

    #pragma omp simd reduction(+:result)
															dummyMethod3();
        for (i = 0; i < matrixSize; i++)
            result += D[i] * A[i];
															dummyMethod4();
    
    return result;

    /* COMPARE VS UNROLLED, NO THREADING WHICH IS FASTER
    omp_set_num_threads(numThreads);
    unsigned long i;
    double result = 0.0;
    double sum0, sum1, sum2, sum3, sum4, sum5, sum6, sum7;
    sum0 = sum1 = sum2 = sum3 = sum4 = sum5 = sum6 = sum7 = 0;

#pragma omp  for simd 
        for (i = 0; i < matrixSize; i+=4){
            result += D[i] * A[i] + D[i + 1] * A[i + 1] + D[i + 2] * A[i + 2] + D[i + 3] * A[i + 3];
        }

    return result;

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
        double n = rand() % 50;
        S[i] = n;
    }
							dummyMethod2();
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

        unsigned long matrixSize = matrixSizes[m]; //

        double *V1 = (double *)malloc(matrixSize * sizeof(double));
        double *V2 = (double *)malloc(matrixSize * sizeof(double));
        double serialDotProduct = 0;
        double parallelDotProduct = 0;

        genRandVector(V1, matrixSize);
        genRandVector(V2, matrixSize);

        for (int a = 0; a < NUM_AVERAGES; a++) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            serialDotProduct = doSequentialComputation(V1, V2, matrixSize);
            clock_gettime(CLOCK_MONOTONIC, &finish);
            elapsed = (finish.tv_sec - start.tv_sec);
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            sequentialTimings[m] += elapsed;
            for (int t = 1; t <= THREAD_RANGE; t++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start);

                parallelDotProduct = doParallelComputation(V1, V2, matrixSize, t);
                clock_gettime(CLOCK_MONOTONIC, &finish);
                elapsed = (finish.tv_sec - start.tv_sec);
                elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
                parallelTimings[m][t - 1] += elapsed;

                    assert(serialDotProduct == parallelDotProduct);
            
            }
        }
        free(V1);
        free(V2);
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