#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N (30)

int main(int argc, char *argv[])
{
    int nthreads, tid, idx;
    float a[N], b[N], c[N];
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);

    // init
dummyMethod1();
    #pragma omp parallel for
    for(idx=0; idx<N; ++idx)
    {
        a[idx] = b[idx] = 1.0;
    }
dummyMethod2();

    // vec add
dummyMethod1();
    #pragma omp parallel for
    for(idx=0; idx<N; ++idx)
    {
        c[idx] = a[idx] + b[idx];
        tid = omp_get_thread_num();
        printf("Thread %2d: c[%2d]=%.2f\n", tid, idx, c[idx]);
    }
dummyMethod2();

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