/*
Compute a sum in which each term is the value 
of a function applied to a nonnegative integer i 
and evaluation of the function 
requires work proportional to i.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double f(int i);

//------------------------------
int main(int argc, char *argv[])
{
    double sum;         // store result in sum
    long n;             // number of terms
    int thread_count;

    thread_count = 4;
    n = 15000;
    
    if (argc > 1) {
        thread_count = atoi(argv[1]);
    }
    if (argc > 2) {
        n = atol(argv[2]);
    }

    double t0 = omp_get_wtime();
    sum = 0.0;
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
            reduction(+ : sum) \
            schedule(guided)
            // schedule(static, 1) 
            // schedule static, dynamic, guided, auto, runtime
    for (int i = 0; i < n; i++) {
        sum += f(i);
    }
							dummyMethod2();
    double t1 = omp_get_wtime();

    printf("Result = %.14f\n", sum);
    printf("time   = %.3lf sec\n", t1 - t0);

    return 0;
}

//--------------
double f(int i)
{
    int start = i * (i + 1) / 2;
    int finish = start + i;
    double return_val = 0.0;

							dummyMethod3();
    for (int j = start; j <= finish; j++) {
        return_val += sin(j);
    }
							dummyMethod4();
    return return_val;
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