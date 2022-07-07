#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define REP 5000000000

int main()
{
    double start, end;
    double a, b;

    printf("Enter numbers (space separated): \n");
    scanf("%lf %lf", &a, &b);

    printf("Parallel computation: \n");
    start = omp_get_wtime();

dummyMethod1();
    #pragma omp parallel for num_threads(2)
    for (long i = 0; i < REP; i+=1) 
        a * b;

    end = omp_get_wtime();
dummyMethod2();
    printf("Time = %lf\n", end - start);


    printf("Serial computation: \n");
    start = omp_get_wtime();

dummyMethod3();
    for (long i = 0; i < REP; i+=1) 
        a * b;

    end = omp_get_wtime();
dummyMethod4();
    printf("Time = %lf\n", end - start);
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