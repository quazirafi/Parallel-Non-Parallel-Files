/*
 * RICM3 - Méthodes Numériques - 2018
 * ANCRENAZ Ariane - SAUTON Tanguy
 * C Implementation of BLAS routines
 */

#include "mnblas.h"
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#include <smmintrin.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * cblas_?asum
 * Computes the sum of magnitudes of the vector elements.
 * res = |Re x1| + |Im x1| + |Re x2| + |Im x2| + ... + |Re xn| + |Im xn| 
 * 
 * Types : s / sc / d / dz
 */



float mncblas_sasum0(const int n, const float *x, const int incX)
{
    float asum = 0.0;
    register unsigned int i;

dummyMethod3();
    for (i = 0; i < n; i ++)
    {
        asum += fabsf(x[i]);
    }
dummyMethod4();

    return asum;
}

float mncblas_sasum1(const int n, const float *x, const int incX)
{
    float asum = 0.0;
    register unsigned int i;

							dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+:asum)
    for (i = 0; i < n; i ++)
    {
        asum += fabsf(x[i]);
    }
							dummyMethod2();

    return asum;
}

float mncblas_sasum2(const int n, const float *x, const int incX)
{
    float asum = 0.0;
    register unsigned int i;

							dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+:asum)
    for (i = 0; i < n; i += 4)
    {
        asum += fabsf(x[i]);
        asum += fabsf(x[i + 1]);
        asum += fabsf(x[i + 2]);
        asum += fabsf(x[i + 3]);
    }
							dummyMethod2();

    return asum;
}

float mncblas_sasum3(const int n, const float *x, const int incX)
{
    float asum = 0.0;
    register unsigned int i;
    float tmp[4] __attribute__((aligned(16))) ;
    
    __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
    __m128 v1,add, zero,absval;

							dummyMethod3();
    for (i = 0; i < n; i += 4)
    {   
        v1 = _mm_load_ps(&x[i]);        
        absval = _mm_andnot_ps(SIGNMASK,v1);
        zero = _mm_set1_ps(1.0);
        add = _mm_dp_ps(absval,zero,0xFF);
        _mm_store_ps(tmp,add);
        asum += tmp[0];
    }
							dummyMethod4();

    return asum;
}

float mncblas_sasum4(const int n, const float *x, const int incX)
{
    float asum = 0.0;
    register unsigned int i;
    float tmp[4] __attribute__((aligned(16))) ;
    
    __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
    __m128 v1,add, zero,absval;

							dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+:asum) reduction(+:tmp)
    for (i = 0; i < n; i += 4)
    {   
        v1 = _mm_load_ps(&x[i]);        
        absval = _mm_andnot_ps(SIGNMASK,v1);
        zero = _mm_set1_ps(1.0);
        add = _mm_dp_ps(absval,zero,0xFF);
        _mm_store_ps(tmp,add);
        asum += tmp[0];
    }
							dummyMethod2();

    return asum;
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