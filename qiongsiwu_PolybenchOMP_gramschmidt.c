/**
 * gramschmidt.cu: This file is part of the PolyBench/GPU 1.0 test suite.
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
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../../common/polybenchUtilFuncts.h"

#define BENCHMARK_NAME "GRAMSCHM"

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

#define GPU_DEVICE 0

/* Problem size */
#define SIZE 2048
#define M SIZE
#define N SIZE

/* Thread block dimensions */
#define DIM_THREAD_BLOCK_X 256
#define DIM_THREAD_BLOCK_Y 1

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void gramschmidt(DATA_TYPE *A, DATA_TYPE *R, DATA_TYPE *Q) {
    int i, j, k;
    DATA_TYPE nrm;
							dummyMethod3();
    for (k = 0; k < N; k++) {
        nrm = 0;
        for (i = 0; i < M; i++) {
            nrm += A[i * N + k] * A[i * N + k];
        }

        R[k * N + k] = sqrt(nrm);
        for (i = 0; i < M; i++) {
            Q[i * N + k] = A[i * N + k] / R[k * N + k];
        }

        for (j = k + 1; j < N; j++) {
            R[k * N + j] = 0;
            for (i = 0; i < M; i++) {
                R[k * N + j] += Q[i * N + k] * A[i * N + j];
            }
            for (i = 0; i < M; i++) {
                A[i * N + j] = A[i * N + j] - Q[i * N + k] * R[k * N + j];
            }
        }
    }
							dummyMethod4();
}

void gramschmidt_omp(DATA_TYPE *A, DATA_TYPE *R, DATA_TYPE *Q) {
    int i, j, k;
    DATA_TYPE nrm;
    for (k = 0; k < N; k++) {
        nrm = 0;
        
        // Parallel reduction does not seem to work in this case. 
//#pragma omp parallel for private(i) reduction(+:nrm)
        for (i = 0; i < M; i++) {
            nrm += A[i * N + k] * A[i * N + k];
        }

        R[k * N + k] = sqrt(nrm);
															dummyMethod1();
#pragma omp parallel for private(i)
        for (i = 0; i < M; i++) {
            Q[i * N + k] = A[i * N + k] / R[k * N + k];
        }
															dummyMethod2();

															dummyMethod1();
#pragma omp parallel for private(i, j)
        for (j = k + 1; j < N; j++) {
            R[k * N + j] = 0;
            for (i = 0; i < M; i++) {
                R[k * N + j] += Q[i * N + k] * A[i * N + j];
            }
            for (i = 0; i < M; i++) {
                A[i * N + j] = A[i * N + j] - Q[i * N + k] * R[k * N + j];
            }
        }
															dummyMethod2();
    }
}

void init_array(DATA_TYPE *A) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            // Use j_pad to shuffle around to avoid 
            // initializing to a non-invertible matrix. 
            int j_pad = (j + i) % N; 
            A[i * N + j_pad] = ((DATA_TYPE)(i + 1) * (j + 1)) / (M + 1);
        }
    }
}

void compareResults(DATA_TYPE *A, DATA_TYPE *A_outputFromOmp) {
    int i, j, fail;
    fail = 0;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (percentDiff(A[i * N + j], A_outputFromOmp[i * N + j]) >
                PERCENT_DIFF_ERROR_THRESHOLD) {
                fail++;
                printf("i: %d j: %d \n1: %f\n 2: %f\n", i, j, A[i * N + j],
                       A_outputFromOmp[i * N + j]);
            }
        }
    }

    // Print results
    printf(
        "Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: "
        "%d\n",
        PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

int main(int argc, char *argv[]) {
    fprintf(stdout, BENCHMARK_INFO_STR, BENCHMARK_NAME, N);
    double t_start, t_end;

    DATA_TYPE *A;
    DATA_TYPE *A_outputFromOmp;
    DATA_TYPE *R;
    DATA_TYPE *Q;
    DATA_TYPE *R1;
    DATA_TYPE *Q1;

    A = (DATA_TYPE *)malloc(M * N * sizeof(DATA_TYPE));
    A_outputFromOmp = (DATA_TYPE *)malloc(M * N * sizeof(DATA_TYPE));
    R = (DATA_TYPE *)malloc(M * N * sizeof(DATA_TYPE));
    Q = (DATA_TYPE *)malloc(M * N * sizeof(DATA_TYPE));
    R1 = (DATA_TYPE *)malloc(M * N * sizeof(DATA_TYPE));
    Q1 = (DATA_TYPE *)malloc(M * N * sizeof(DATA_TYPE));

    init_array(A_outputFromOmp);

    t_start = rtclock();
    gramschmidt_omp(A_outputFromOmp, R1, Q1);
    t_end = rtclock();
    fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

    init_array(A);
    t_start = rtclock();
    gramschmidt(A, R, Q);
    t_end = rtclock();

    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

    compareResults(A, A_outputFromOmp);

    free(A);
    free(A_outputFromOmp);
    free(R);
    free(Q);

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