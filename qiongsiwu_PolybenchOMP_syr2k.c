/**
 * syr2k.cu: This file is part of the PolyBench/GPU 1.0 test suite.
 *
 *
 * Contact: Scott Grauer-Gray <sgrauerg@gmail.com>
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../../common/polybenchUtilFuncts.h"

#define BENCHMARK_NAME "SYR2K"

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

#define GPU_DEVICE 0

/* Problem size */
#define N 2048
#define M 2048

/* Thread block dimensions */
#define DIM_THREAD_BLOCK_X 32
#define DIM_THREAD_BLOCK_Y 8

/* Declared constant values for ALPHA and BETA (same as values in PolyBench 2.0)
 */
#define ALPHA 12435
#define BETA 4546

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j;

							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] = ((DATA_TYPE)i * j + 2) / N;
        }

        for (j = 0; j < M; j++) {
            A[i * N + j] = ((DATA_TYPE)i * j) / N;
            B[i * N + j] = ((DATA_TYPE)i * j + 1) / N;
        }
    }
							dummyMethod4();
}

void syr2k(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j, k;

							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] *= BETA;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < M; k++) {
                C[i * N + j] += ALPHA * A[i * M + k] * B[j * M + k];
                C[i * N + j] += ALPHA * B[i * M + k] * A[j * M + k];
            }
        }
    }
							dummyMethod4();
}

void syr2k_omp(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j, k;

							dummyMethod1();
#pragma omp parallel for private(i, j) 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] *= BETA;
        }
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for private(i, j, k) 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < M; k++) {
                C[i * N + j] += ALPHA * A[i * M + k] * B[j * M + k];
                C[i * N + j] += ALPHA * B[i * M + k] * A[j * M + k];
            }
        }
    }
							dummyMethod2();
}

void compareResults(DATA_TYPE *C, DATA_TYPE *C_outputFromOmp) {
    int i, j, fail;
    fail = 0;

    // Compare C with D
							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (percentDiff(C[i * N + j], C_outputFromOmp[i * N + j]) >
                PERCENT_DIFF_ERROR_THRESHOLD) {
                fail++;
            }
        }
    }
							dummyMethod4();

    // print results
    printf(
        "Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: "
        "%d\n",
        PERCENT_DIFF_ERROR_THRESHOLD, fail);
}


int main() {
    fprintf(stdout, BENCHMARK_INFO_STR, BENCHMARK_NAME, N);
    double t_start, t_end;

    DATA_TYPE *A;
    DATA_TYPE *B;
    DATA_TYPE *C;
    DATA_TYPE *C_outputFromOmp;

    A = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
    B = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
    C = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
    C_outputFromOmp = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));

    init_arrays(A, B, C_outputFromOmp);
    t_start = rtclock();
    syr2k_omp(A, B, C_outputFromOmp);
    t_end = rtclock();
    fprintf(stdout, "OMP Runtime: %0.6lfs\n", t_end - t_start);

    init_arrays(A, B, C);
    t_start = rtclock();
    syr2k(A, B, C);
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