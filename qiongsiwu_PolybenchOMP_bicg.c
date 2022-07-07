/**
 * bicg.cu: This file is part of the PolyBench/GPU 1.0 test suite.
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
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../../common/polybenchUtilFuncts.h"

#define BENCHMARK_NAME "BICG"

// Error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.5

#define GPU_DEVICE 0

/* Problem size. */
#define SIZE 16384  // 4096

#define NX SIZE
#define NY SIZE

/* Thread block dimensions */
#define DIM_THREAD_BLOCK_X 256
#define DIM_THREAD_BLOCK_Y 1

#ifndef M_PI
#define M_PI 3.14159
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE* A, DATA_TYPE* p, DATA_TYPE* r) {
    int i, j;

							dummyMethod3();
    for (i = 0; i < NX; i++) {
        r[i] = i * M_PI;

        for (j = 0; j < NY; j++) {
            A[i * NY + j] = ((DATA_TYPE)i * j) / NX;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < NY; i++) {
        p[i] = i * M_PI;
    }
							dummyMethod4();
}

void compareResults(DATA_TYPE* s, DATA_TYPE* s_outputFromOmp, DATA_TYPE* q,
                    DATA_TYPE* q_outputFromOmp) {
    int i, fail;
    fail = 0;

    // Compare s with s_cuda
							dummyMethod3();
    for (i = 0; i < NX; i++) {
        if (percentDiff(q[i], q_outputFromOmp[i]) >
            PERCENT_DIFF_ERROR_THRESHOLD) {
            fail++;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < NY; i++) {
        if (percentDiff(s[i], s_outputFromOmp[i]) >
            PERCENT_DIFF_ERROR_THRESHOLD) {
            fail++;
        }
    }
							dummyMethod4();

    // print results
    printf(
        "Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: "
        "%d\n",
        PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

// Distributed (split) from initial loop and permuted into reverse order to
// allow parallelism...
/*__global__ void bicg_kernel1(DATA_TYPE* A, DATA_TYPE* r, DATA_TYPE* s) {
    int j = blockIdx.x * blockDim.x + threadIdx.x;

    if (j < NY) {
        s[j] = 0.0f;

        int i;
        for (i = 0; i < NX; i++) {
            s[j] += A[i * NY + j] * r[i];
        }
    }
}*/

// Distributed (split) from initial loop to allow parallelism
/*__global__ void bicg_kernel2(DATA_TYPE* A, DATA_TYPE* p, DATA_TYPE* q) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < NX) {
        q[i] = 0.0f;

        int j;
        for (j = 0; j < NY; j++) {
            q[i] += A[i * NY + j] * p[j];
        }
    }
}*/

void bicg_cpu(DATA_TYPE* A, DATA_TYPE* r, DATA_TYPE* s, DATA_TYPE* p,
              DATA_TYPE* q) {
    int i, j;

							dummyMethod3();
    for (i = 0; i < NY; i++) {
        s[i] = 0.0;
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < NX; i++) {
        q[i] = 0.0;
        for (j = 0; j < NY; j++) {
            s[j] = s[j] + r[i] * A[i * NY + j];
            q[i] = q[i] + A[i * NY + j] * p[j];
        }
    }
							dummyMethod4();
}

void bicg_omp(DATA_TYPE* A, DATA_TYPE* r, DATA_TYPE* s, DATA_TYPE* p,
              DATA_TYPE* q) {
    int i, j;

							dummyMethod3();
    for (j = 0; j < NY; j++) {
        s[j] = 0; 
    }
							dummyMethod4();

    // The loop below has better locality access for A but the outer loop
    // cannot be parallalized because it causes race condition on s[j]
    for (i = 0; i < NX; i++) {
															dummyMethod1();
#pragma omp parallel for private(j)
        for (j = 0; j < NY; j++) {
            s[j] = s[j] + r[i] * A[i * NY + j]; 
        }
															dummyMethod2();
    }

    // The loop below does not suffer from race conditions but has terrible
    // access pattern. 
/*#pragma omp parallel for private(j)
    for (j = 0; j < NY; j++) {
        for (i = 0; i < NX; i++) {
            s[j] = s[j] + r[i] * A[i * NY + j]; 
        }
    }*/


							dummyMethod1();
#pragma omp parallel for private(i, j)
    for (i = 0; i < NX; i++) {
        q[i] = 0.0;
        for (j = 0; j < NY; j++) {
            q[i] = q[i] + A[i * NY + j] * p[j];
        }
    }
							dummyMethod2();
}

int main(int argc, char** argv) {
    fprintf(stdout, BENCHMARK_INFO_STR, BENCHMARK_NAME, NX);
    double t_start, t_end;

    DATA_TYPE* A;
    DATA_TYPE* r;
    DATA_TYPE* s;
    DATA_TYPE* p;
    DATA_TYPE* q;
    DATA_TYPE* s_outputFromOmp;
    DATA_TYPE* q_outputFromOmp;

    A = (DATA_TYPE*)malloc(NX * NY * sizeof(DATA_TYPE));
    r = (DATA_TYPE*)malloc(NX * sizeof(DATA_TYPE));
    s = (DATA_TYPE*)malloc(NY * sizeof(DATA_TYPE));
    p = (DATA_TYPE*)malloc(NY * sizeof(DATA_TYPE));
    q = (DATA_TYPE*)malloc(NX * sizeof(DATA_TYPE));
    s_outputFromOmp = (DATA_TYPE*)malloc(NY * sizeof(DATA_TYPE));
    q_outputFromOmp = (DATA_TYPE*)malloc(NX * sizeof(DATA_TYPE));

    init_array(A, p, r);

    t_start = rtclock();
    bicg_omp(A, r, s_outputFromOmp, p, q_outputFromOmp);
    t_end = rtclock();
    fprintf(stdout, "OMP Runtime: %0.6lfs\n", t_end - t_start);

    t_start = rtclock();
    bicg_cpu(A, r, s, p, q);
    t_end = rtclock();

    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

    compareResults(s, s_outputFromOmp, q, q_outputFromOmp);

    free(A);
    free(r);
    free(s);
    free(p);
    free(q);
    free(s_outputFromOmp);
    free(q_outputFromOmp);

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