#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 10000000;
double step;

int main()
{
    double start_time = omp_get_wtime();
    int i;
    double pi;
    double sum = 0.0;
    step = 1.0/(double) num_steps;
dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
dummyMethod2();
    pi = step * sum;
    printf("Pi is %lf\n", pi);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("The time eleapsed is %lf\n", elapsed_time);
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