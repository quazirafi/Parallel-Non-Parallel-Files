//
// Created by Yonghong Yan on 1/7/16.
//
#include "axpy.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef USE_INTEL_MKL
#include <mkl.h>
#endif

void axpy_cpu_omp_wrapper(omp_offloading_t *off, long start_n,  long length_n,REAL a,REAL *x,REAL *y) {
    int num_omp_threads = off->dev->num_cores;
    int i;

#ifdef USE_INTEL_MKL
mkl_mic_disable();
#endif

#ifdef USE_INTEL_MKL
    #pragma omp parallel shared(y, x, a, start_n, length_n) private(i) num_threads(num_omp_threads)
    cblas_saxpy(length_n-start_n, a, x, 1, y, 1);

    //mkl_mic_enable();
#else
dummyMethod1();
    #pragma omp parallel for simd shared(y, x, a, start_n, length_n) private(i) num_threads(num_omp_threads)
    for (i=start_n; i<start_n + length_n; i++) {
        y[i] += a*x[i];
//			printf("x[%d]: %f, y[%d]: %f\n", i, x[i], i, y[i]);
dummyMethod2();
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