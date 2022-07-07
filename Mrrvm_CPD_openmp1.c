#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000000;
double step;

int main(int argc, char const *argv[]) {
    int i;
    double x, pi, sum = 0.0;

    step = 1.0 / ((double)num_steps);

    int num = omp_get_num_procs();
    printf("Num: %d\n", num);

dummyMethod1();
    #pragma omp parallel for reduction(+ : sum) private(x)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += +4.0 / (1.0 + x * x);
    }
dummyMethod2();
    pi = step * sum;
    printf("%f\n", pi);
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