/*
 * RICM3 - Méthodes Numériques - 2018
 * ANCRENAZ Ariane - SAUTON Tanguy
 * C Implementation of BLAS routines
 */

#include "mnblas.h"
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <smmintrin.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * cblas_?gemm
 * 
 * Types : s / d / c / z
 */

void mncblas_sgemm0(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE transa, const MNCBLAS_TRANSPOSE transb,
                    const int m, const int n, const int k, const float alpha, const float *a, const int lda,
                    const float *b, const int ldb, const float beta, float *c, const int ldc)
{
    int i, j, l;
    float sum;

							dummyMethod3();
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0.0;
            for (l = 0; l < k; l++)
            {
                sum += a[i * k + l] * b[l * n + j];
            }
            c[n * i + j] = alpha * sum + beta * c[n * i + j];
        }
    }
							dummyMethod4();
}

void mncblas_sgemm1(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE transa, const MNCBLAS_TRANSPOSE transb,
                    const int m, const int n, const int k, const float alpha, const float *a, const int lda,
                    const float *b, const int ldb, const float beta, float *c, const int ldc)
{
    int i, j, l;
    float sum;

							dummyMethod1();
#pragma omp parallel for private(j, l, sum)
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0.0;
            for (l = 0; l < k; l++)
            {
                sum += a[i * k + l] * b[l * n + j];
            }
            c[n * i + j] = alpha * sum + beta * c[n * i + j];
        }
    }
							dummyMethod2();
}

void mncblas_sgemm2(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE transa, const MNCBLAS_TRANSPOSE transb,
                    const int m, const int n, const int k, const float alpha, const float *a, const int lda,
                    const float *b, const int ldb, const float beta, float *c, const int ldc)
{
    int i, j, l;
    float sum;

							dummyMethod1();
#pragma omp parallel for private(j, l, sum)
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0.0;
            for (l = 0; l < k; l += 4)
            {
                sum += a[i * k + l] * b[l * n + j];
                sum += a[i * k + l + 1] * b[(l + 1) * n + j];
                sum += a[i * k + l + 2] * b[(l + 2) * n + j];
                sum += a[i * k + l + 3] * b[(l + 3) * n + j];
            }
            c[n * i + j] = alpha * sum + beta * c[n * i + j];
        }
    }
							dummyMethod2();
}

void mncblas_sgemm3(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE transa, const MNCBLAS_TRANSPOSE transb,
                    const int m, const int n, const int k, const float alpha, const float *a, const int lda,
                    const float *b, const int ldb, const float beta, float *c, const int ldc)
{
/*     register unsigned int i, j, l;
    float sum;
    float tmp[4] __attribute__((aligned(16)));

    __m128 v1,v2, dp;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0.0;
            for (l = 0; l < k; l += 4)
            {
                v1 = _mm_load_ps(&a[i*k+l]);
                v2 = _mm_load_ps(&b[l*n+j]);
                dp = _mm_dp_ps(v1,v2,0xFF);
                _mm_store_ps(tmp, dp);
                sum += tmp[0];
            }
            c[n * i + j] = alpha * sum + beta * c[n * i + j];
        }
    } */
}

void mncblas_sgemm4(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE transa, const MNCBLAS_TRANSPOSE transb,
                    const int m, const int n, const int k, const float alpha, const float *a, const int lda,
                    const float *b, const int ldb, const float beta, float *c, const int ldc)
{
/*     int i, j, l;
    float sum;
    float tmp[4] __attribute__((aligned(16)));

    __m128 v1,v2, dp;

#pragma omp parallel for private(j, l, sum, tmp)
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0.0;
            for (l = 0; l < k; l += 4)
            {
                v1 = _mm_load_ps(&a[i*k+l]);
                v2 = _mm_load_ps(&b[l*n+j]);
                dp = _mm_dp_ps(v1,v2,0xFF);
                _mm_store_ps(tmp, dp);
                sum += tmp[0];
            }
            c[n * i + j] = alpha * sum + beta * c[n * i + j];
        }
    } */
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