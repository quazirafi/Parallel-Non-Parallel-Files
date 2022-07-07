#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define CHUNKSIZE 100

static long num_steps = 100000000;

void main()
{
    double x, pi;
    double sum = 0.0;
    double step = 1.0/(double) num_steps;
    int i, chunk;
    chunk = CHUNKSIZE;
    clock_t start = clock();
dummyMethod1();
    #pragma omp parallel for private(x) schedule(static, chunk) reduction(+:sum)
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0/(1.0 + x*x);
    }
dummyMethod2();

    pi = step * sum;
    clock_t end = clock();

    printf("elapsed time %f\n", (float)(end - start) / CLOCKS_PER_SEC);
    printf("pi [%lf] step [%lf] sum[%lf]\n", pi, step, sum);
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