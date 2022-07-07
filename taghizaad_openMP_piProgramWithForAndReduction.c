#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000000;
double step;
#define NUM_THREADS 2

void main() {
    int i;
    double pi, sum = 0.0;
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    double startTime = omp_get_wtime(); //time in seconds since a fixed point in the past
#pragma omp parallel
    {
        double x;
        /*
         * by default the loop  index variable i will be local for each thread
         * so I didn't have to create a copy i for each thread. But if you do,
         * that's perfectly OK. But you don't need to
         * */
dummyMethod1();
        #pragma omp parallel for reduction (+:sum)
        for (i = 0; i < num_steps; i++) {
            x = (i + .5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
dummyMethod2();
    }
    pi = step * sum;
    double endTime = omp_get_wtime();
    printf("pi value is: %f\n", pi);
    printf("time consumed: %f", endTime - startTime);
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