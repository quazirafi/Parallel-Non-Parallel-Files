/*
 * RICM3 - Méthodes Numériques - 2018
 * ANCRENAZ Ariane - SAUTON Tanguy
 * C Implementation of BLAS routines
 */

#include "mnblas.h"
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <smmintrin.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * cblas_?gemv
 * 
 * Types : s / d / c / z
 */

void mncblas_sgemv0(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE trans, const int m, const int n,
                    const float alpha, const float *a, const int lda, const float *x, const int incx,
                    const float beta, float *y, const int incy)
{

    register unsigned int i, j;
    float sum;

							dummyMethod3();
    for (i = 0; i < m; i++)
    {
        sum = 0.0;
        for (j = 0; j < n; j++)
        {
            sum += x[j] * a[i * n + j];
        }
        y[i] = alpha * sum + beta * y[i];
    }
							dummyMethod4();
}

void mncblas_sgemv1(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE trans, const int m, const int n,
                    const float alpha, const float *a, const int lda, const float *x, const int incx,
                    const float beta, float *y, const int incy)
{

    register unsigned int i, j;
    float sum;

							dummyMethod1();
#pragma omp parallel for private(j,sum)
    for (i = 0; i < m; i++)
    {
        sum = 0.0;
        for (j = 0; j < n; j++)
        {
            sum += x[j] * a[i * n + j];
        }
        y[i] = alpha * sum + beta * y[i];
    }
							dummyMethod2();
}

void mncblas_sgemv2(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE trans, const int m, const int n,
                    const float alpha, const float *a, const int lda, const float *x, const int incx,
                    const float beta, float *y, const int incy)
{

    register unsigned int i, j;
    float sum;

							dummyMethod1();
#pragma omp parallel for private(j, sum)
    for (i = 0; i < m; i++)
    {
        sum = 0.0;
        for (j = 0; j < n; j += 4)
        {
            sum += x[j] * a[i * n + j];
            sum += x[j + 1] * a[i * n + j + 1];
            sum += x[j + 2] * a[i * n + j + 2];
            sum += x[j + 3] * a[i * n + j + 3];
        }
        y[i] = alpha * sum + beta * y[i];
    }
							dummyMethod2();
}

void mncblas_sgemv3(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE trans, const int m, const int n,
                    const float alpha, const float *a, const int lda, const float *x, const int incx,
                    const float beta, float *y, const int incy)
{

    register unsigned int i, j;
    float sum;
    float tmp[4] __attribute__((aligned(16)));
    
    __m128 v1, v2,dp;
							dummyMethod3();
    for (i = 0; i < m; i++)
    {
        sum = 0.0;
        for (j = 0; j < n; j+=4)
        {
            v1 = _mm_load_ps(&x[j]);
            v2 = _mm_load_ps(&a[i*n+j]);
            dp = _mm_dp_ps(v1,v2,0xFF);
            _mm_store_ps(tmp, dp);
            sum += tmp[0];
        }
        y[i] = alpha * sum + beta * y[i];
    }
							dummyMethod4();
}

void mncblas_sgemv4(const MNCBLAS_LAYOUT Layout, const MNCBLAS_TRANSPOSE trans, const int m, const int n,
                    const float alpha, const float *a, const int lda, const float *x, const int incx,
                    const float beta, float *y, const int incy)
{

    register unsigned int i, j;
    float sum;
    float tmp[4] __attribute__((aligned(16)));

    __m128 v1,v2, dp;

							dummyMethod1();
#pragma omp parallel for private(j, sum, tmp)
    for (i = 0; i < m; i++)
    {
        sum = 0.0;
        for (j = 0; j < n; j+=4)
        {
            v1 = _mm_load_ps(&x[j]);
            v2 = _mm_load_ps(&a[i*n+j]);
            dp = _mm_dp_ps(v1,v2,0xFF);
            _mm_store_ps(tmp, dp);
            sum += tmp[0];
        }
        y[i] = alpha * sum + beta * y[i];
    }
							dummyMethod2();
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