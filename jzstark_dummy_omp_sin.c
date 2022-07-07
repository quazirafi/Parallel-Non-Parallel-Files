#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long N = 100000000;
#define NUM_THREADS 4

int main ()
{
    //float start_time, run_time;
    float *x = (float *) calloc(N, sizeof(float));
    float *y = (float *) calloc(N, sizeof(float));
    if (x == NULL || y == NULL) exit(1);
    memset(x, 1, sizeof(float) * N);

    //start_time = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
dummyMethod1();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i) {
        float foo = x[i];
        y[i] = sinf(cos(sin(cos(tan(log(sin(exp(sin(foo)))))))));
    }
dummyMethod2();
    //run_time = omp_get_wtime() - start_time;
    //printf("\n pi with %ld size is %lf in %lf seconds\n ", N, y[1], run_time);

    return 0;
}


// Compile: `gcc -fopenmp sin.c -lm`
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