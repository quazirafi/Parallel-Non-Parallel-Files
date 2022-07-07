#include "matvec.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef USE_INTEL_MKL
#include <mkl.h>
#endif

void matvec_cpu_omp_wrapper(omp_offloading_t *off, long n, long start_n, long length_n,REAL *a,REAL *x,REAL *y)
{
    int num_omp_threads = off->dev->num_cores;
    int i, j;

#ifdef USE_INTEL_MKL
     mkl_mic_disable();
     REAL alpha = 1;
     REAL beta = 0;
#endif

#ifdef USE_INTEL_MKL
#pragma omp parallel shared(y, x, a, start_n, length_n) private(i,j) num_threads(num_omp_threads)
     cblas_sgemv(CblasColMajor, CblasNoTrans, length_n , n, alpha, a, length_n, x, 1, beta, y, 1);
    //mkl_mic_enable();
#else
dummyMethod1();
#pragma omp parallel for simd shared(y, x, a, start_n, length_n) private(i,j) num_threads(num_omp_threads)
    for (i = start_n; i < start_n + length_n; i++) {
        for (j = 0; j < n; j++)
            y[i] += a[i*n + j] * x[j];
        //printf ("error part!!");
    }
dummyMethod2();
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