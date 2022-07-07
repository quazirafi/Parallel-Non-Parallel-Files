/*
 * RICM3 - Méthodes Numériques - 2018
 * ANCRENAZ Ariane - SAUTON Tanguy
 * C Implementation of BLAS routines
 */

#include "mnblas.h"
#include "omp.h"
#include <smmintrin.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * cblas_?dotc
 * Computes a dot product of a conjugated vector with another vector
 * res = SUM(i from 1 to n){ conjg(Xi) * Yi}
 *
 * Types : c / z
 */

void mncblas_cdotc_sub0(const int N, const void *X, const int incX,
                        const void *Y, const int incY, void *dotc)
{
  cplx_t *xx = (cplx_t *)X;
  cplx_t *yy = (cplx_t *)Y;

  register unsigned int i;
  float re = 0;
  float im = 0;

dummyMethod3();
  for (i = 0; i < N; i++)
  {
    re += xx[i].re * yy[i].re + xx[i].im * yy[i].im;
    im += xx[i].re * yy[i].im - xx[i].im * yy[i].re;
  }
dummyMethod4();

  ((cplx_t *)dotc)->re = re;
  ((cplx_t *)dotc)->im = im;
}

void mncblas_cdotc_sub1(const int N, const void *X, const int incX,
                        const void *Y, const int incY, void *dotc)
{
  cplx_t *xx = (cplx_t *)X;
  cplx_t *yy = (cplx_t *)Y;

  register unsigned int i;
  float re = 0;
  float im = 0;

			dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+                 \
                                                    : re) reduction(+ \
                                                                    : im)
  for (i = 0; i < N; i++)
  {
    re += xx[i].re * yy[i].re + xx[i].im * yy[i].im;
    im += xx[i].re * yy[i].im - xx[i].im * yy[i].re;
  }
			dummyMethod2();

  ((cplx_t *)dotc)->re = re;
  ((cplx_t *)dotc)->im = im;
}

void mncblas_cdotc_sub2(const int N, const void *X, const int incX,
                        const void *Y, const int incY, void *dotc)
{
  cplx_t *xx = (cplx_t *)X;
  cplx_t *yy = (cplx_t *)Y;

  register unsigned int i;

  float re = 0;
  float im = 0;

			dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+  : re) reduction(+ : im)
  for (i = 0; i < N; i += 4)
  {
    re += xx[i].re * yy[i].re + xx[i].im * yy[i].im;
    im += xx[i].re * yy[i].im - xx[i].im * yy[i].re;

    re += xx[i + 1].re * yy[i + 1].re + xx[i + 1].im * yy[i + 1].im;
    im += xx[i + 1].re * yy[i + 1].im - xx[i + 1].im * yy[i + 1].re;

    re += xx[i + 2].re * yy[i + 2].re + xx[i + 2].im * yy[i + 2].im;
    im += xx[i + 2].re * yy[i + 2].im - xx[i + 2].im * yy[i + 2].re;

    re += xx[i + 3].re * yy[i + 3].re + xx[i + 3].im * yy[i + 3].im;
    im += xx[i + 3].re * yy[i + 3].im - xx[i + 3].im * yy[i + 3].re;
  }
			dummyMethod2();

  ((cplx_t *)dotc)->re = re;
  ((cplx_t *)dotc)->im = im;
}

void mncblas_cdotc_sub3(const int N, const void *X, const int incX,
                        const void *Y, const int incY, void *dotc)
{
  cplx_t *xx = (cplx_t *)X;
  cplx_t *yy = (cplx_t *)Y;

  register unsigned int i;

  float re = 0;
  float im = 0;

  float tmp[4] __attribute__((aligned(16)));

  __m128 vx1, vx2;
  __m128 vy1, vy2;
  __m128 xre, xim;
  __m128 yre, yim;
  __m128 resre, resim;
  __m128 tmp1, tmp2;
			dummyMethod3();
  for (i = 0; i < N; i += 4)
  {
    vx1 = _mm_load_ps((float *)&xx[i]);
    vx2 = _mm_load_ps((float *)&xx[i + 2]);

    vy1 = _mm_load_ps((float *)&yy[i]);
    vy2 = _mm_load_ps((float *)&yy[i + 2]);

    xre = _mm_shuffle_ps(vx1, vx2, 0x88);
    xim = _mm_shuffle_ps(vx1, vx2, 0xDD);

    yre = _mm_shuffle_ps(vy1, vy2, 0x88);
    yim = _mm_shuffle_ps(vy1, vy2, 0xDD);

    tmp1 = _mm_mul_ps(xre, yre);
    tmp2 = _mm_mul_ps(xim, yim);
    resre = _mm_add_ps(tmp1, tmp2);

    tmp1 = _mm_mul_ps(xre, yim);
    tmp2 = _mm_mul_ps(xim, yre);
    resim = _mm_sub_ps(tmp1, tmp2);

    _mm_store_ps(tmp, resre);
    re += tmp[0] + tmp[1] + tmp[2] + tmp[3];
    _mm_store_ps(tmp, resim);
    im += tmp[0] + tmp[1] + tmp[2] + tmp[3];
  }
			dummyMethod4();

  ((cplx_t *)dotc)->re = re;
  ((cplx_t *)dotc)->im = im;
}

void mncblas_cdotc_sub4(const int N, const void *X, const int incX,
                        const void *Y, const int incY, void *dotc)
{
  cplx_t *xx = (cplx_t *)X;
  cplx_t *yy = (cplx_t *)Y;

  register unsigned int i;

  float re = 0;
  float im = 0;

  float tmp[4] __attribute__((aligned(16)));

  __m128 vx1, vx2;
  __m128 vy1, vy2;
  __m128 xre, xim;
  __m128 yre, yim;
  __m128 resre, resim;
  __m128 tmp1, tmp2;

			dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+  : re) reduction(+ : im) reduction (+:tmp)  
  for (i = 0; i < N; i += 4)
  {
    vx1 = _mm_load_ps((float *)&xx[i]);
    vx2 = _mm_load_ps((float *)&xx[i + 2]);

    vy1 = _mm_load_ps((float *)&yy[i]);
    vy2 = _mm_load_ps((float *)&yy[i + 2]);

    xre = _mm_shuffle_ps(vx1, vx2, 0x88);
    xim = _mm_shuffle_ps(vx1, vx2, 0xDD);

    yre = _mm_shuffle_ps(vy1, vy2, 0x88);
    yim = _mm_shuffle_ps(vy1, vy2, 0xDD);

    tmp1 = _mm_mul_ps(xre, yre);
    tmp2 = _mm_mul_ps(xim, yim);
    resre = _mm_add_ps(tmp1, tmp2);

    tmp1 = _mm_mul_ps(xre, yim);
    tmp2 = _mm_mul_ps(xim, yre);
    resim = _mm_sub_ps(tmp1, tmp2);

    _mm_store_ps(tmp, resre);
    re += tmp[0] + tmp[1] + tmp[2] + tmp[3];
    _mm_store_ps(tmp, resim);
    im += tmp[0] + tmp[1] + tmp[2] + tmp[3];
  }
			dummyMethod2();

  ((cplx_t *)dotc)->re = re;
  ((cplx_t *)dotc)->im = im;
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