/*
Estimate definite integral (or area under curve)
using trapezoidal rule

using 
    #pragma omp prallel for reduction
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double f(double x);    // Function we're integrating
double trap(double a, double b, int n, int thread_count);

// serial solution
double trap_serial(double a, double b, int n);

//--------------------------------
int main(int argc, char* argv[]) {
    double  a, b;                 // Left and right endpoints      
    int     n;                    // Total number of trapezoids    
    int     thread_count;

    thread_count = 4;
    a = 1;
    b = 5;
    n = 0.5e9;//100000000;

    if (argc > 1) {
        thread_count = atoi(argv[1]);
    }
    if (argc > 4) {
        a = atof(argv[2]);
        b = atof(argv[3]);
        n = atoi(argv[4]);
    }

    // time
    // returns elapsed wall clock time in seconds
    double t0 = omp_get_wtime();
    double res = trap_serial(a, b, n);
    double t1 = omp_get_wtime();

    printf("serial result = %.6f\n", res);
    printf("time = %.3f sec\n", t1 - t0);

    // time
    t0 = omp_get_wtime();
    clock_t c0 = clock();
    double global_result = trap(a, b, n, thread_count);
    t1 = omp_get_wtime();
    clock_t c1 = clock();

    printf("threads= %d n= %d trapezoids\n", thread_count, n);
    printf("the integral from %.2f to %.2f = %.6f\n", a, b, global_result);
    printf("time = %.3f sec\n", t1 - t0);
    
    printf("time = %.3f sec\n", (double)(c1-c0)/CLOCKS_PER_SEC);

    return 0;
}

//------------------
double f(double x) {
    return x * x;
}

// --- serial solution ------------------------
double trap_serial(double a, double b, int n) {
    double h = (b-a) / n;
    double res = (f(a) + f(b)) / 2;
    
							dummyMethod3();
    for (int i = 1; i <= n-1; i++) {
        res += f(a + i*h);
    }
							dummyMethod4();
    return res * h;
} 

//--------------------------------------------------------
double trap(double a, double b, int n, int thread_count) {
    double h = (b-a) / n; 
    double res = (f(a) + f(b)) / 2; 
    
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
        reduction(+: res)
    for (int i = 1; i <= n-1; i++) {
        res += f(a + i*h);
    }
							dummyMethod2();
    return res * h; 
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