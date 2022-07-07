#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 8

/*Integration serial version*/
double Integration_gold(int nSteps)
{
    double start = omp_get_wtime();
    double result = 0, x = 0;
    int i;
    double delta = 1 / (double) nSteps;
dummyMethod3();
    for( i = 0; i < nSteps; i++){
        x = (i + 0.5) * delta;
        result += 4.0 / (1 + x * x);
    }
dummyMethod4();
    printf("Integration_gold time:%f\n", omp_get_wtime() - start);
    return result * delta;
}

double Integration_MP(int nSteps)
{
    double start = omp_get_wtime();
    double result = 0;
    int i;
    double delta = 1 / (double) nSteps;
    #pragma omp parallel
    { 
            double x;
															dummyMethod1();
        #pragma omp parallel for reduction (+:result)
        for( i = 0; i < nSteps; i++){
            x = (i + 0.5) * delta;
            result += 4.0 / (1 + x * x);
        }
															dummyMethod2();
    }

    printf("Integration_MP time:%f\n", omp_get_wtime() - start);
    return result * delta;
}

int main()
{
    int nSteps = 100000000;
    printf("Gold result: %f\n", Integration_gold(nSteps));
    printf("OpenMP result: %f\n", Integration_MP(nSteps));
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