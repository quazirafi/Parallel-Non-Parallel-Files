/**
 * gemm.cu: This file is part of the PolyBench/GPU 1.0 test suite.
 *
 *
 * Contact: Scott Grauer-Gray <sgrauerg@gmail.com>
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../../common/polybenchUtilFuncts.h"

#define BENCHMARK_NAME "GEMM"

#define GPU_DEVICE 0

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

/* Problem size */
#define SIZE 512
#define NI SIZE
#define NJ SIZE
#define NK SIZE

/* Thread block dimensions */
#define DIM_THREAD_BLOCK_X 32
#define DIM_THREAD_BLOCK_Y 8

/* Declared constant values for ALPHA and BETA (same as values in PolyBench 2.0)
 */
#define ALPHA 32412.0f
#define BETA 2123.0f

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void gemm(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j, k;

							dummyMethod3();
    for (i = 0; i < NI; i++) {
        for (j = 0; j < NJ; j++) {
            C[i * NJ + j] *= BETA;

            for (k = 0; k < NK; ++k) {
                C[i * NJ + j] += ALPHA * A[i * NK + k] * B[k * NJ + j];
            }
        }
    }
							dummyMethod4();
}

void gemm_omp(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j, k;

							dummyMethod1();
#pragma omp parallel for private (i, j, k) collapse(2)
    for (i = 0; i < NI; i++) {
        for (j = 0; j < NJ; j++) {
            C[i * NJ + j] *= BETA;

            for (k = 0; k < NK; ++k) {
                C[i * NJ + j] += ALPHA * A[i * NK + k] * B[k * NJ + j];
            }
        }
    }
							dummyMethod2();
}

void init(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j;

							dummyMethod3();
    for (i = 0; i < NI; i++) {
        for (j = 0; j < NK; j++) {
            A[i * NK + j] = ((DATA_TYPE)i * j) / NI;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < NK; i++) {
        for (j = 0; j < NJ; j++) {
            B[i * NJ + j] = ((DATA_TYPE)i * j + 1) / NJ;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < NI; i++) {
        for (j = 0; j < NJ; j++) {
            C[i * NJ + j] = ((DATA_TYPE)i * j + 2) / NJ;
        }
    }
							dummyMethod4();
}

void compareResults(DATA_TYPE *C, DATA_TYPE *C_outputFromOmp) {
    int i, j, fail;
    fail = 0;

    // Compare C1 and C2
							dummyMethod3();
    for (i = 0; i < NI; i++) {
        for (j = 0; j < NJ; j++) {
            if (percentDiff(C[i * NJ + j], C_outputFromOmp[i * NJ + j]) >
                PERCENT_DIFF_ERROR_THRESHOLD) {
                fail++;
            }
        }
    }
							dummyMethod4();

    // Print results
    printf(
        "Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: "
        "%d\n",
        PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

int main(int argc, char *argv[]) {
    fprintf(stdout, BENCHMARK_INFO_STR, BENCHMARK_NAME, NI);
    double t_start, t_end;

    DATA_TYPE *A;
    DATA_TYPE *B;
    DATA_TYPE *C;
    DATA_TYPE *C_outputFromOmp;

    A = (DATA_TYPE *)malloc(NI * NK * sizeof(DATA_TYPE));
    B = (DATA_TYPE *)malloc(NK * NJ * sizeof(DATA_TYPE));
    C = (DATA_TYPE *)malloc(NI * NJ * sizeof(DATA_TYPE));
    C_outputFromOmp = (DATA_TYPE *)malloc(NI * NJ * sizeof(DATA_TYPE));

    init(A, B, C_outputFromOmp);

    t_start = rtclock();
    gemm_omp(A, B, C_outputFromOmp);
    t_end = rtclock();
    fprintf(stdout, "OMP Runtime: %0.6lfs\n", t_end - t_start);

    init(A, B, C);
    t_start = rtclock();
    gemm(A, B, C);
    t_end = rtclock();
    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

    compareResults(C, C_outputFromOmp);

    free(A);
    free(B);
    free(C);
    free(C_outputFromOmp);

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