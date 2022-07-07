/**
 * correlation.cu: This file is part of the PolyBench/GPU 1.0 test suite.
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
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../../common/polybenchUtilFuncts.h"

#define BENCHMARK_NAME "CORR"

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 1.05

#define GPU_DEVICE 0

/* Problem size */
#define SIZE 2048
#define M SIZE
#define N SIZE

/* Thread block dimensions for kernel 1*/
#define DIM_THREAD_BLOCK_KERNEL_1_X 256
#define DIM_THREAD_BLOCK_KERNEL_1_Y 1

/* Thread block dimensions for kernel 2*/
#define DIM_THREAD_BLOCK_KERNEL_2_X 256
#define DIM_THREAD_BLOCK_KERNEL_2_Y 1

/* Thread block dimensions for kernel 3*/
#define DIM_THREAD_BLOCK_KERNEL_3_X 32
#define DIM_THREAD_BLOCK_KERNEL_3_Y 8

/* Thread block dimensions for kernel 4*/
#define DIM_THREAD_BLOCK_KERNEL_4_X 256
#define DIM_THREAD_BLOCK_KERNEL_4_Y 1

#define sqrt_of_array_cell(x, j) sqrt(x[j])

#define FLOAT_N 3214212.01f
#define EPS 0.005f

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE *data) {
    int i, j;

							dummyMethod3();
    for (i = 0; i < (M + 1); i++) {
        for (j = 0; j < (N + 1); j++) {
            data[i * (N + 1) + j] = ((DATA_TYPE)i * j) / (M + 1);
        }
    }
							dummyMethod4();
}

void correlation(DATA_TYPE *data, DATA_TYPE *mean, DATA_TYPE *stddev,
                 DATA_TYPE *symmat) {
    int i, j, j1, j2;

    // Determine mean of column vectors of input data matrix
							dummyMethod3();
    for (j = 1; j < (M + 1); j++) {
        mean[j] = 0.0;

        for (i = 1; i < (N + 1); i++) {
            mean[j] += data[i * (M + 1) + j];
        }

        mean[j] /= (DATA_TYPE)FLOAT_N;
    }
							dummyMethod4();

    // Determine standard deviations of column vectors of data matrix.
							dummyMethod3();
    for (j = 1; j < (M + 1); j++) {
        stddev[j] = 0.0;

        for (i = 1; i < (N + 1); i++) {
            stddev[j] += (data[i * (M + 1) + j] - mean[j]) *
                         (data[i * (M + 1) + j] - mean[j]);
        }

        stddev[j] /= FLOAT_N;
        stddev[j] = sqrt_of_array_cell(stddev, j);
        stddev[j] = stddev[j] <= EPS ? 1.0 : stddev[j];
    }
							dummyMethod4();

    // Center and reduce the column vectors.
							dummyMethod3();
    for (i = 1; i < (N + 1); i++) {
        for (j = 1; j < (M + 1); j++) {
            data[i * (M + 1) + j] -= mean[j];
            data[i * (M + 1) + j] /= (sqrt(FLOAT_N) * stddev[j]);
        }
    }
							dummyMethod4();

    // Calculate the m * m correlation matrix.
							dummyMethod3();
    for (j1 = 1; j1 < M; j1++) {
        symmat[j1 * (M + 1) + j1] = 1.0;

        for (j2 = j1 + 1; j2 < (M + 1); j2++) {
            symmat[j1 * (M + 1) + j2] = 0.0;

            for (i = 1; i < (N + 1); i++) {
                symmat[j1 * (M + 1) + j2] +=
                    (data[i * (M + 1) + j1] * data[i * (M + 1) + j2]);
            }

            symmat[j2 * (M + 1) + j1] = symmat[j1 * (M + 1) + j2];
        }
    }
							dummyMethod4();

    symmat[M * (M + 1) + M] = 1.0;
}

void correlation_omp(DATA_TYPE *data, DATA_TYPE *mean, DATA_TYPE *stddev,
                     DATA_TYPE *symmat) {
    int i, j, j1, j2;

    // Determine mean of column vectors of input data matrix
							dummyMethod1();
#pragma omp parallel for private(j, i)
    for (j = 1; j < (M + 1); j++) {
        mean[j] = 0.0;

        for (i = 1; i < (N + 1); i++) {
            mean[j] += data[i * (M + 1) + j];
        }

        mean[j] /= (DATA_TYPE)FLOAT_N;
    }
							dummyMethod2();

    // Determine standard deviations of column vectors of data matrix.
							dummyMethod1();
#pragma omp parallel for private(j, i)
    for (j = 1; j < (M + 1); j++) {
        stddev[j] = 0.0;

        for (i = 1; i < (N + 1); i++) {
            stddev[j] += (data[i * (M + 1) + j] - mean[j]) *
                         (data[i * (M + 1) + j] - mean[j]);
        }

        stddev[j] /= FLOAT_N;
        stddev[j] = sqrt_of_array_cell(stddev, j);
        stddev[j] = stddev[j] <= EPS ? 1.0 : stddev[j];
    }
							dummyMethod2();

    // Center and reduce the column vectors.
							dummyMethod1();
#pragma omp parallel for collapse(2) private(i, j)
    for (i = 1; i < (N + 1); i++) {
        for (j = 1; j < (M + 1); j++) {
            data[i * (M + 1) + j] -= mean[j];
            data[i * (M + 1) + j] /= (sqrt(FLOAT_N) * stddev[j]);
        }
    }
							dummyMethod2();

    // Calculate the m * m correlation matrix.
							dummyMethod1();
#pragma omp parallel for private(j1, j2, i)
    for (j1 = 1; j1 < M; j1++) {
        symmat[j1 * (M + 1) + j1] = 1.0;

        for (j2 = j1 + 1; j2 < (M + 1); j2++) {
            symmat[j1 * (M + 1) + j2] = 0.0;

            for (i = 1; i < (N + 1); i++) {
                symmat[j1 * (M + 1) + j2] +=
                    (data[i * (M + 1) + j1] * data[i * (M + 1) + j2]);
            }

            symmat[j2 * (M + 1) + j1] = symmat[j1 * (M + 1) + j2];
        }
    }
							dummyMethod2();

    symmat[M * (M + 1) + M] = 1.0;
}

void compareResults(DATA_TYPE *symmat, DATA_TYPE *symmat_outputFromOmp) {
    int i, j, fail;
    fail = 0;

							dummyMethod3();
    for (i = 1; i < (M + 1); i++) {
        for (j = 1; j < (N + 1); j++) {
            if (percentDiff(symmat[i * (N + 1) + j],
                            symmat_outputFromOmp[i * (N + 1) + j]) >
                PERCENT_DIFF_ERROR_THRESHOLD) {
                fail++;
                printf("i: %d j: %d\n1: %f 2: %f\n", i, j, symmat[i * N + j],
                       symmat_outputFromOmp[i * N + j]);
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

/*__global__ void mean_kernel(DATA_TYPE *mean, DATA_TYPE *data) {
    int j = blockIdx.x * blockDim.x + threadIdx.x + 1;

    if ((j >= 1) && (j < (M + 1))) {
        mean[j] = 0.0;

        int i;
        for (i = 1; i < (N + 1); i++) {
            mean[j] += data[i * (M + 1) + j];
        }

        mean[j] /= (DATA_TYPE)FLOAT_N;
    }
}

__global__ void std_kernel(DATA_TYPE *mean, DATA_TYPE *std, DATA_TYPE *data) {
    int j = blockIdx.x * blockDim.x + threadIdx.x + 1;

    if ((j >= 1) && (j < (M + 1))) {
        std[j] = 0.0;

        int i;
        for (i = 1; i < (N + 1); i++) {
            std[j] += (data[i * (M + 1) + j] - mean[j]) *
                      (data[i * (M + 1) + j] - mean[j]);
        }
        std[j] /= (FLOAT_N);
        std[j] = sqrt(std[j]);
        if (std[j] <= EPS) {
            std[j] = 1.0;
        }
    }
}

__global__ void reduce_kernel(DATA_TYPE *mean, DATA_TYPE *std,
                              DATA_TYPE *data) {
    int j = blockIdx.x * blockDim.x + threadIdx.x + 1;
    int i = blockIdx.y * blockDim.y + threadIdx.y + 1;

    if ((i >= 1) && (i < (N + 1)) && (j >= 1) && (j < (M + 1))) {
        data[i * (M + 1) + j] -= mean[j];
        data[i * (M + 1) + j] /= (sqrt(FLOAT_N) * std[j]);
    }
}

__global__ void corr_kernel(DATA_TYPE *symmat, DATA_TYPE *data) {
    int j1 = blockIdx.x * blockDim.x + threadIdx.x + 1;

    int i, j2;
    if ((j1 >= 1) && (j1 < M)) {
        symmat[j1 * (M + 1) + j1] = 1.0;

        for (j2 = (j1 + 1); j2 < (M + 1); j2++) {
            symmat[j1 * (M + 1) + j2] = 0.0;

            for (i = 1; i < (N + 1); i++) {
                symmat[j1 * (M + 1) + j2] +=
                    data[i * (M + 1) + j1] * data[i * (M + 1) + j2];
            }
            symmat[j2 * (M + 1) + j1] = symmat[j1 * (M + 1) + j2];
        }
    }
}*/

int main() {
    fprintf(stdout, BENCHMARK_INFO_STR, BENCHMARK_NAME, N);
    double t_start, t_end;

    DATA_TYPE *data;
    DATA_TYPE *mean;
    DATA_TYPE *stddev;
    DATA_TYPE *symmat;
    DATA_TYPE *symmat_outputFromOmp;

    data = (DATA_TYPE *)malloc((M + 1) * (N + 1) * sizeof(DATA_TYPE));
    mean = (DATA_TYPE *)malloc((M + 1) * sizeof(DATA_TYPE));
    stddev = (DATA_TYPE *)malloc((M + 1) * sizeof(DATA_TYPE));
    symmat = (DATA_TYPE *)malloc((M + 1) * (N + 1) * sizeof(DATA_TYPE));
    symmat_outputFromOmp =
        (DATA_TYPE *)malloc((M + 1) * (N + 1) * sizeof(DATA_TYPE));

    init_arrays(data);
    t_start = rtclock();
    correlation_omp(data, mean, stddev, symmat_outputFromOmp);
    t_end = rtclock();
    fprintf(stdout, "OMP Runtime: %0.6lfs\n", t_end - t_start);

    init_arrays(data);
    t_start = rtclock();
    correlation(data, mean, stddev, symmat);
    t_end = rtclock();

    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

    compareResults(symmat, symmat_outputFromOmp);

    free(data);
    free(mean);
    free(stddev);
    free(symmat);
    free(symmat_outputFromOmp);

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