#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NUM_THREADS 2

long N = 100000;

void main(){
    int i;
    double pi = 0.0, sum = 0.0, x = 0.0;
    double step = 1.0/(double)N;
    omp_set_num_threads(NUM_THREADS);

dummyMethod1();
    #pragma omp parallel for reduction(+:sum) private(i)
    for (i = 1; i < N; i++){
        x = (i-0.5) * step;
        sum += 4.0/(1 + x*x);
    }
dummyMethod2();
    pi = sum * step;
    printf(" Result of pi=%lf\n", pi);
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