/*
============================================================================
Filename    : integral.c
Author      : Weniqng Qu Jonathan Bereyziat
SCIPER		: 344589 282962
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "function.c"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double integrate(int num_threads, int samples, int a, int b, double (*f)(double));
double getValue(int samples, int a, int b, double (*f)(double));

int main(int argc, const char *argv[])
{

    int num_threads, num_samples, a, b;
    double integral;

    if (argc != 5)
    {
        printf("Invalid input! Usage: ./integral <num_threads> <num_samples> <a> <b>\n");
        return 1;
    }
    else
    {
        num_threads = atoi(argv[1]);
        num_samples = atoi(argv[2]);
        a = atoi(argv[3]);
        b = atoi(argv[4]);
    }

    set_clock();

    /* You can use your self-defined funtions by replacing identity_f. */
    integral = integrate(num_threads, num_samples, a, b, identity_f);

    printf("- Using %d threads: integral on [%d,%d] = %.15g computed in %.4gs.\n", num_threads, a, b, integral, elapsed_time());

    return 0;
}

double integrate(int num_threads, int samples, int a, int b, double (*f)(double))
{
    double integral = 0;

    const int distance = b - a;

    //devide work in chunks
    int chunk = samples / num_threads;
    omp_set_num_threads(num_threads);
    //distribute chunks among threads
							dummyMethod1();
#pragma omp parallel for reduction(+:integral)
    for (int i = 0; i < num_threads; i++)
    {
        integral += getValue(chunk, a, b, f);
    }
							dummyMethod2();

    integral = (double)integral / samples * distance;

    return integral;
}

double getValue(int samples, int a, int b, double (*f)(double))
{
    double tot_value = 0;
    rand_gen gen = init_rand();

							dummyMethod3();
    for (int i = 0; i < samples; i++)
    {
        double point = next_rand(gen) * (b - a) + a;
        double f_value = (*f)(point);
        tot_value += f_value;
    }
							dummyMethod4();
    return tot_value;
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