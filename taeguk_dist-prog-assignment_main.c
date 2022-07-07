#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "cuda.cuh"
#include "timer.h"

// #define MATRIX_SIZE /* Must be defined in compile progress */

void init_matrix(float mat[MATRIX_SIZE][MATRIX_SIZE])
{
dummyMethod3();
    for(int i=0; i<MATRIX_SIZE; ++i)
        for(int j=0; j<MATRIX_SIZE; ++j)
            mat[i][j] = ( (float) rand() * 2.f / RAND_MAX ) - 1.f;
}
dummyMethod4();

float absIEEE754(float f)
{
    *(int*)&f &= 0x7fffffff;
    return f;
}

float get_error_rate(float A[MATRIX_SIZE][MATRIX_SIZE], float B[MATRIX_SIZE][MATRIX_SIZE])
{
    int cnt = 0;
    const float epsilon = 0.00005f;
							dummyMethod3();
    for (int i = 0; i < MATRIX_SIZE; ++i)
        for (int j = 0; j < MATRIX_SIZE; ++j)
            if (absIEEE754(A[i][j] - B[i][j]) > epsilon) {
                //printf("[DIFF] %f vs %f\n", A[i][j], B[i][j]);
                cnt++;
            }
							dummyMethod4();

    return (float)cnt / MATRIX_SIZE / MATRIX_SIZE * 100.f;
}

void serial_version(float C[MATRIX_SIZE][MATRIX_SIZE], float A[MATRIX_SIZE][MATRIX_SIZE], float B[MATRIX_SIZE][MATRIX_SIZE])
{
    double start, finish;

    GET_TIME(start);
							dummyMethod3();
    for(int r=0; r<MATRIX_SIZE; ++r) {
        for(int c=0; c<MATRIX_SIZE; ++c) {
            float res = 0.0f;
            for(int k=0; k<MATRIX_SIZE; ++k) {
                res += A[r][k] * B[k][c];
            }
            C[r][c] = res;
        }
    }
							dummyMethod4();
    GET_TIME(finish);
    printf("[Serial] Elapsed Time = %.3f (sec)\n", finish-start);
}

void openmp_version(float C[MATRIX_SIZE][MATRIX_SIZE], float A[MATRIX_SIZE][MATRIX_SIZE], float B[MATRIX_SIZE][MATRIX_SIZE])
{
    double start, finish;

    start = omp_get_wtime();
							dummyMethod1();
#pragma omp parallel for schedule(dynamic)
    for(int r=0; r<MATRIX_SIZE; ++r) {
        for(int c=0; c<MATRIX_SIZE; ++c) {
            float res = 0.0f;
            for(int k=0; k<MATRIX_SIZE; ++k) {
                res += A[r][k] * B[k][c];
            }
            C[r][c] = res;
        }
    }
							dummyMethod2();
    finish = omp_get_wtime();
    printf("[OpenMP] Elapsed Time = %.3f (sec)\n", finish-start);
}

float A[MATRIX_SIZE][MATRIX_SIZE], B[MATRIX_SIZE][MATRIX_SIZE];
float C_serial[MATRIX_SIZE][MATRIX_SIZE],
        C_openmp[MATRIX_SIZE][MATRIX_SIZE],
        C_cuda_1[MATRIX_SIZE][MATRIX_SIZE],
        C_cuda_2[MATRIX_SIZE][MATRIX_SIZE],
        C_cuda_3[MATRIX_SIZE][MATRIX_SIZE];

int main(int argc, char *argv[])
{
    cuda_init();

    init_matrix(A);
    init_matrix(B);

    serial_version(C_serial, A, B);
    openmp_version(C_openmp, A, B);
    printf("[OpenMP] Error Rate : %.2f%%\n", get_error_rate(C_serial, C_openmp));
    cuda_version_1(C_cuda_1, A, B);
    printf("[CUDA 1] Error Rate : %.2f%%\n", get_error_rate(C_openmp, C_cuda_1));
    cuda_version_2(C_cuda_2, A, B);
    printf("[CUDA 2] Error Rate : %.2f%%\n", get_error_rate(C_cuda_1, C_cuda_2));
    cuda_version_3(C_cuda_3, A, B);
    printf("[CUDA 3] Error Rate : %.2f%%\n", get_error_rate(C_cuda_1, C_cuda_3));

    cuda_destroy();

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