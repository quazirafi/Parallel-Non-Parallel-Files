//
// Created by Yonghong Yan on 1/7/16.
//
#include "sum.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef USE_INTEL_MKL
#include <mkl.h>
#endif

void sum_cpu_omp_wrapper(omp_offloading_t *off, long start_n, long length_n,  REAL *x, REAL *y, REAL *result) {
    int num_omp_threads = off->dev->num_cores;
    long i;

    REAL sum = 0.0;
dummyMethod1();
    #pragma omp parallel for simd shared(y, x, start_n, length_n) private(i) num_threads(num_omp_threads) reduction(+:sum)
    for (i=start_n; i<start_n + length_n; i++) {
        sum += y[i] * x[i];
//			printf("x[%d]: %f, y[%d]: %f\n", i, x[i], i, y[i]);
dummyMethod2();
    }
    *result = sum;
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