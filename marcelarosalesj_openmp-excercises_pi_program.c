#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000;
double step;

void main() {
    int i;
    double x, pi, sum = 0.0;

    step = 1.0/(double)num_steps;

dummyMethod1();
    #pragma omp parallel for num_threads(4) private(i, x) reduction(+:sum)
    for (i=0; i< num_steps; i++) {
        x = (i+0.5)*step;
        sum = sum+4.0/(1.0+x*x);
    }
dummyMethod2();
    pi = step*sum;
    printf("PI is %f\n", pi);
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