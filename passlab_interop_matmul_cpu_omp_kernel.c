#include "omp.h"
#include "matmul.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef USE_INTEL_MKL
#include <mkl.h>
#endif

void matmul_cpu_omp_wrapper(omp_offloading_t *off, long i, long j,long k,float *A,float *B,float *C)
{
    int num_omp_threads = off->dev->num_cores;
    long ii, jj, kk;
    //	omp_set_num_threads(off->dev->num_cores);
    //printf("%d cores on dev: %s\n", off->dev->num_cores, off->dev->name);

#ifdef USE_INTEL_MKL
     mkl_mic_disable();
     REAL alpha = 1;
     REAL beta = 0;
#endif

#ifdef USE_INTEL_MKL
#pragma omp parallel shared(A, B, C, i,j,k) private(ii, jj, kk) num_threads(num_omp_threads)
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                i, j, k, alpha, A, k, B, j, beta, C, j);

    //mkl_mic_enable();
#else
							dummyMethod1();
#pragma omp parallel for shared(A, B, C, i,j,k) private(ii, jj, kk) num_threads(num_omp_threads)
    for (ii = 0; ii < i; ii++) {
        for (jj = 0; jj < j; jj++) {
            REAL sum = 0.0;
            for (kk = 0; kk < k; kk++) {
                sum += A[ii * k + kk] * B[kk * j + jj];
            }
            C[ii * j + jj] = sum;
        }
    }
							dummyMethod2();
#endif

#if 0
    #pragma omp parallel for shared(A, B, C, i,j,k) private(ii, jj, kk) num_threads(num_omp_threads)
    for (ii = 0; ii < i; ii++) {
        for (jj = 0; jj < j; jj++) {
            REAL sum = 0.0;
            for (kk = 0; kk < k; kk++) {
                sum += A[ii * k + kk] * B[kk * j + jj];
            }
            C[ii * j + jj] = sum;
        }
    }
#endif



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