#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

long num_steps = 100000;

double serialExecTime()
{
    double step;

    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;

    double start = omp_get_wtime();

dummyMethod3();
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
dummyMethod4();
    pi = step * sum;


    printf("Serial Execution Results: Pi = %lf\n", pi);

    double ans = omp_get_wtime() - start;

    return ans;
}

float partial_sum_calculate(int i, double step)
{
    double x, sum;
    x = (i + 0.5) * step;
    sum = 4.0 / (1.0 + x * x);

    return sum;
}

double parallelExecTime()
{
    float Sum;
    double step = 1.0 / (double)num_steps;

    double start = omp_get_wtime();

    // omp_set_num_threads(3);
    int nthrds, i;
							dummyMethod1();
#pragma omp parallel for reduction(+ : Sum)

    for (i = 0; i < num_steps; i++)
    {
        float partial_sum = partial_sum_calculate(i, step);
        Sum = Sum + partial_sum;
    }
							dummyMethod2();

    nthrds = omp_get_num_threads();
    

    //printf("Number of Threads: %d\nPi = %lf\n", nthrds, Sum * step);
    // printf("Total number of threads used: %d\n", nthrds);
    double ans = omp_get_wtime() - start;
    printf("Multi-threaded Result: Pi = %lf\n", Sum * step);
    return ans;
}

int main()
{
    printf("Time taken for Uni-Processor execution: %lf seconds\n", serialExecTime());

    printf("Time taken for Multi-Processor execution: %lf seconds\n", parallelExecTime());

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