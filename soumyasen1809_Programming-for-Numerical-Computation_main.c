#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double factorial (int n)
{
    double val = 1;
dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        val = val*(i+1);
    }
dummyMethod4();

    return val;
}

int main()
{
    double a = 0.1;
    int n_iters = 10000;
    double sum = 0;
    int num_threads;

    // Parallel implementation

    double start_parallel_time = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for reduction (+:sum)
    for (int i = 0; i < n_iters; i++)
    {
        num_threads = omp_get_num_threads();
        sum = sum + pow(a,i)/factorial(i);
    }
dummyMethod2();
    double end_parallel_time = omp_get_wtime();

    printf("e^%f is %f using %d threads in %f time\n", a,sum, num_threads, end_parallel_time-start_parallel_time);

    // Serial implementation for comparison

    double start_serial_time = omp_get_wtime();
    #pragma omp master
							dummyMethod3();
    for (int i = 0; i < n_iters; i++)
    {
        num_threads = omp_get_num_threads();
        sum = sum + pow(a,i)/factorial(i);
    }
							dummyMethod4();
    double end_serial_time = omp_get_wtime();

    printf("e^%f is %f using %d threads in %f time\n", a,sum, num_threads, end_serial_time-start_serial_time);

    double speedup = (end_serial_time-start_serial_time)/(end_parallel_time-start_parallel_time);
    printf("Speedup is %f\n", speedup);

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