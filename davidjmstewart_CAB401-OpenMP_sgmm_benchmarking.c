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
#include "../../lib/CDUtils.h"


#define THREAD_RANGE 8 // Run for 1:THREAD_RANGE threads
#define NUM_AVERAGES 20 // take the average of 5 timings for each matrix size, and each number of threads
#define NUM_MATRIX_SIZES 8
// unsigned long matrixSizes[NUM_MATRIX_SIZES] = {51200};
const double EQUALITY_THRESHOLD = 0.1;
unsigned long matrixSizes[NUM_MATRIX_SIZES] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384};

double sequentialTimings[NUM_MATRIX_SIZES];
double parallelTimings[NUM_MATRIX_SIZES][THREAD_RANGE];

//gcc -fopenmp -g ./benchmarking/matrix_vector_multiplication/mvm_benchmarking.c -o ./benchmarking/matrix_vector_multiplication/mvm ./lib/CDUtils.o -lm -Wall -Wpedantic -Waggressive-loop-optimizations -O3 -march=native -fopt-info-vec-missed=v.txt
#pragma GCC target("avx") //Enable AVX

void doSequentialComputation(double *restrict B_g, double *restrict B, unsigned long currentMatrixSize, unsigned long originalMatrixSize, int *globalVertices)
{
    // printf("Global vertices %d\n", globalVertices[2]);
    //Copy the necessary rows and columns out of B and put them into B_g
							dummyMethod3();
    for (int i = 0; i < currentMatrixSize; i++)
    {
        for (int j = 0; j < currentMatrixSize; j++)
        {
            B_g[i * currentMatrixSize + j] = B[globalVertices[i] * originalMatrixSize + globalVertices[j]];
        }
    }
							dummyMethod4();
    int i, j, x, y;
    int n = currentMatrixSize;
    double *Bsum = (double *)malloc(currentMatrixSize * sizeof(double)); // Sum each row of B and put it in here

    double *Bhead;
    double tmp;

							dummyMethod3();
    for (i = 0; i < currentMatrixSize; i++)
    {
        Bhead = &B_g[i * currentMatrixSize];
        tmp = 0;
        for (j = 0; j < currentMatrixSize; j++)
        {
            tmp += Bhead[j];
        }
        Bsum[i] = tmp;
    }
							dummyMethod4();

    // #pragma omp parallel for private(j)
							dummyMethod3();
    for (i = 0; i < currentMatrixSize; i++)
    {
        B_g[i * currentMatrixSize + i] -= Bsum[i];
    }
							dummyMethod4();
}

void doParallelComputation(double *restrict B_g, double *restrict B, unsigned long currentMatrixSize, unsigned long originalMatrixSize, int *globalVertices, int numThreads)
{

    omp_set_num_threads(numThreads);
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < currentMatrixSize; i++)
    {
        double *B_gHead = &B_g[i * currentMatrixSize];
        int globalVertexIndex = globalVertices[i] * originalMatrixSize;

        for (int j = 0; j < currentMatrixSize; j++)
        {
            B_gHead[j] = B[globalVertexIndex + globalVertices[j]];
        }
    }
							dummyMethod2();
    int i, j, x, y;
    int n = currentMatrixSize;
    double *Bsum = (double *)malloc(currentMatrixSize * sizeof(double)); // Sum each row of B and put it in here


    // double tmp;
							dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < currentMatrixSize; i++)
    {
        double *Bhead;
        Bhead = &B_g[i * currentMatrixSize];
        double tmp = 0;
        // #pragma omp simd reduction(+ \
        //                         : tmp)
        for (int j = 0; j < currentMatrixSize; j++)
        {
            tmp += Bhead[j];
        }
        Bsum[i] = tmp;
        // printf("%.4f\n", Bsum[i]);
    }
							dummyMethod2();

							dummyMethod1();
    #pragma omp parallel for private(j)
    for (i = 0; i < currentMatrixSize; i++)
    {
        B_g[i * currentMatrixSize + i] -= Bsum[i];
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
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {

        unsigned long matrixSize = matrixSizes[m]; //


        double *A = (double *)malloc(matrixSize * matrixSize * sizeof(double)); // Matrix to multiply by V
        double *B = (double *)malloc(matrixSize * matrixSize * sizeof(double)); // Matrix to multiply by V
        double *seqB_g = (double *)malloc(matrixSize * matrixSize * sizeof(double)); // Store the subgraph modularity matrix computed sequentially here
        double *parB_g = (double *)malloc(matrixSize * matrixSize * sizeof(double)); // Store the subgraph modularity matrix computed in parallel
        int *globalVertices = (int *)malloc(matrixSize * sizeof(int));               // Store the subgraph modularity matrix computed in parallel

        double *D = (int *)malloc(matrixSize * sizeof(int)); // Matrix to multiply by V

        genAdjacencyMatrix(A, matrixSize);
        createDegreesVec(A, D, matrixSize, 1);

        createModularityMatrix(B, A, D, matrixSize, 16);

        createGlobalVertices(globalVertices, matrixSize, 1);
        for (int a = 0; a < NUM_AVERAGES; a++)
        {
            clock_gettime(CLOCK_MONOTONIC, &start);
            doSequentialComputation(seqB_g, B, matrixSize, matrixSize, globalVertices);
            // integerMatrixToFile(A, matrixSize, MATLAB);
            // matrixToFile(seqB_g, matrixSize, MATLAB);

            clock_gettime(CLOCK_MONOTONIC, &finish);
            elapsed = (finish.tv_sec - start.tv_sec);
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            sequentialTimings[m] += elapsed;

            for (int t = 1; t <= THREAD_RANGE; t++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start);

                doParallelComputation(parB_g, B, matrixSize, matrixSize, globalVertices, t);
                // integerMatrixToFile(A, matrixSize, MATLAB);
                // matrixToFile(parB_g, matrixSize, MATLAB);

                clock_gettime(CLOCK_MONOTONIC, &finish);
                elapsed = (finish.tv_sec - start.tv_sec);
                elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
                parallelTimings[m][t - 1] += elapsed;
                for (int i = 0; i < matrixSize; i++)
                {
                    for (int j = 0; j < matrixSize; j++)
                    {
                        // printf("[%d][%d]: Seq: %.9f \t Par; %.9f \n", i , j, seqB_g[i * matrixSize + j], parB_g[i * matrixSize + j]);
                        assert(fabs(seqB_g[i * matrixSize + j] - parB_g[i * matrixSize + j]) < EQUALITY_THRESHOLD);
                    }
                }
            }
        }
        free(seqB_g);
        free(parB_g);
        free(B);
        free(D);
        free(A);
    }
							dummyMethod4();

							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {
        sequentialTimings[m] /= NUM_AVERAGES;
        for (int t = 0; t < THREAD_RANGE; t++)
        {
            parallelTimings[m][t] /= NUM_AVERAGES;
        }
    }
							dummyMethod4();

    printf("Sequential:\n");
							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {
        printf("%lux%lu:\t", matrixSizes[m], matrixSizes[m]);

        printf("%.9f \n", sequentialTimings[m]);
    }
							dummyMethod4();

    printf("\nParallel:\n");
							dummyMethod3();
    for (int m = 0; m < NUM_MATRIX_SIZES; m++)
    {
        printf("%lux%lu:\t", matrixSizes[m], matrixSizes[m]);

        for (int t = 0; t < THREAD_RANGE; t++)
        {
            printf(" %.9f ", parallelTimings[m][t]);
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