/**
 * syr2k.c: This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *           Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
 */

#include <assert.h>
#include <math.h>
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


// polybenchUtilFuncts.h
// Scott Grauer-Gray (sgrauerg@gmail.com)
// Functions used across hmpp codes

#ifndef POLYBENCH_UTIL_FUNCTS_H
#define POLYBENCH_UTIL_FUNCTS_H

// define a small float value
#define SMALL_FLOAT_VAL 0.00000001f

double rtclock() {
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday(&Tp, &Tzp);
    if (stat != 0)
        printf("Error return from gettimeofday: %d", stat);
    return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

float absVal(float a) {
    if (a < 0) {
        return (a * -1);
    } else {
        return a;
    }
}

float percentDiff(double val1, double val2) {
    if ((absVal(val1) < 0.01) && (absVal(val2) < 0.01)) {
        return 0.0f;
    }

    else {
        return 100.0f * (absVal(absVal(val1 - val2) / absVal(val1 + SMALL_FLOAT_VAL)));
    }
}

#endif // POLYBENCH_UTIL_FUNCTS_H

int main();

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.10

#ifdef _DEBUG_1
/* Problem size */
#define N 4096
#define M 4096

#elif _DEBUG_2
/* Problem size */
#define N 2048
#define M 2048

#else
/* Problem size */
#define N 1024
#define M 1024
#endif

#define GPU_DEVICE 1

/* Declared constant values for ALPHA and BETA (same as values in PolyBench 2.0) */
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

void GPU__syr2k(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C) {
    int i, j, k;

							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] *= BETA;
        }
    }
							dummyMethod4();

							dummyMethod1();
#pragma omp parallel for private(i, j, k) //collapse(3)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < M; k++) {
                C[i * N + j] += ALPHA * A[i * M + k] * B[j * M + k];
                C[i * N + j] += ALPHA * B[i * M + k] * A[j * M + k];
            }
        }
    }
							dummyMethod2();
    return;
}

void compareResults(DATA_TYPE *C, DATA_TYPE *C_Gpu) {
    int i, j, fail;
    fail = 0;

    // Compare C with D
							dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (percentDiff(C[i * N + j], C_Gpu[i * N + j]) > PERCENT_DIFF_ERROR_THRESHOLD) {
                fail++;
            }
        }
    }
							dummyMethod4();

    // print results
    printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

inline void update(DATA_TYPE *C_Gpu) { DATA_TYPE cc = C_Gpu[0]; }

int main() {
    double t_start, t_end;

    DATA_TYPE *A;
    DATA_TYPE *B;
    DATA_TYPE *C;
    DATA_TYPE *C_Gpu;

    A = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
    B = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
    C = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
    C_Gpu = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));

    printf("<< Symmetric rank-2k operations >>\n");
    printf("N: %d\n", N);
    printf("M: %d\n", M);

    init_arrays(A, B, C_Gpu);

    t_start = rtclock();
    GPU__syr2k(A, B, C_Gpu);

    update(C_Gpu);

    t_end = rtclock();
    printf("GPU Runtime(s): %0.6lf\n", t_end - t_start);

    // init_arrays(A, B, C);

    // t_start = rtclock();
    // syr2k(A, B, C);
    // t_end = rtclock();
    // printf("CPU Runtime: %0.6lfs\n", t_end - t_start);

    // compareResults(C, C_Gpu);

    free(A);
    free(B);
    free(C);
    free(C_Gpu);

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