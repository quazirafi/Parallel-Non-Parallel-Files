/**
 * syrk.cu: This file is part of the PolyBench/GPU 1.0 test suite.
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

#define BENCHMARK_NAME "SYRK"

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

#define GPU_DEVICE 0

/* Problem size */
#define N 1024
#define M 1024

/* Thread block dimensions */
#define DIM_THREAD_BLOCK_X 32
#define DIM_THREAD_BLOCK_Y 8

/* Declared constant values for alpha and beta (same as values in PolyBench 2.0)
 */
#define alpha 12435
#define beta 4546

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE* A, DATA_TYPE* C) {
    int i, j;

							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            A[i * M + j] = ((DATA_TYPE)i * j) / N;
        }

        for (j = 0; j < N; j++) {
            C[i * M + j] = ((DATA_TYPE)i * j + 2) / N;
        }
    }
							dummyMethod4();
}

void syrk(DATA_TYPE* A, DATA_TYPE* C) {
    int i, j, k;

    /*  C := alpha*A*A' + beta*C */
							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * M + j] *= beta;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < M; k++) {
                C[i * N + j] += alpha * A[i * M + k] * A[j * M + k];
            }
        }
    }
							dummyMethod4();
}

void syrk_omp(DATA_TYPE* A, DATA_TYPE* C) {
    int i, j, k;

    /*  C := alpha*A*A' + beta*C */
							dummyMethod1();
#pragma omp parallel for private(i, j) 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * M + j] *= beta;
        }
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for private(i, j, k) 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < M; k++) {
                C[i * N + j] += alpha * A[i * M + k] * A[j * M + k];
            }
        }
    }
							dummyMethod2();
}

void compareResults(DATA_TYPE* C, DATA_TYPE* C_outputFromOmp) {
    int i, j, fail;
    fail = 0;

    // Compare C with D
							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (percentDiff(C[i * M + j], C_outputFromOmp[i * M + j]) >
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

    DATA_TYPE* A;
    DATA_TYPE* A_omp;
    DATA_TYPE* C;
    DATA_TYPE* C_outputFromOmp;

    A = (DATA_TYPE*)malloc(N * M * sizeof(DATA_TYPE));
    A_omp = (DATA_TYPE*)malloc(N * M * sizeof(DATA_TYPE));
    C = (DATA_TYPE*)malloc(N * M * sizeof(DATA_TYPE));
    C_outputFromOmp = (DATA_TYPE*)malloc(N * M * sizeof(DATA_TYPE));

    init_arrays(A_omp, C_outputFromOmp);
    t_start = rtclock();
    syrk_omp(A_omp, C_outputFromOmp);
    t_end = rtclock();
    fprintf(stdout, "OMP Runtime: %0.6lfs\n", t_end - t_start);

    init_arrays(A, C);
    t_start = rtclock();
    syrk(A, C);
    t_end = rtclock();
    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

    compareResults(C, C_outputFromOmp);

    free(A);
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