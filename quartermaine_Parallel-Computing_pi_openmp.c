#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define PI 3.14159265358979323846264

void func(int iterations, int num_threads)
{
    const double m = 1.0 / (double)iterations;

    double sum = 0.0;
    omp_set_num_threads(num_threads);

    double start_time = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for reduction(+ : sum)

    for (int i = 0; i < iterations; i++)
    {
        double ni = (i + 0.5) * m;
        sum = sum + 4.0 / (1.0 + ni * ni);
    }
dummyMethod2();
    double MyPI = m * sum;
    double run_time = omp_get_wtime() - start_time;

    double error = MyPI - PI;

    printf("%.23lf,%.23lf,%f", MyPI, error, run_time);
}

void main()
{
    /*printf("Iterarions: 96000000 --------- Threads: 48 ------- \n");*/
							dummyMethod3();
    for (int i = 0; i < 5000; ++i)
    {
        /*printf("iteration: %d: \n", i + 1);*/
        func(96000000, 48);
        printf("\n");
    }
							dummyMethod4();
    /*printf("=================================================\n");*/
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