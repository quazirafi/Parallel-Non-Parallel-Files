// Use OpenMP Reduction to implement partial sums
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARR_SIZE 100000000
short A[ARR_SIZE];

int main(int argc, char** argv) {
    int i, sum = 0;
    double t1, t2;

    // Initialize the Array
dummyMethod3();
    for (i = 0 ; i < ARR_SIZE ; i++)
        A[i] = 1;

    t1 = omp_get_wtime();
dummyMethod4();
    // Sum up the array
    // OpenMP will take care of the partial sum and distribution of the loop among threads
    // #pragma omp parallel default(shared) reduction(+: sum)
    // {
    //     // This will distribute the work among the threads
    //     #pragma omp for
    //     for ( i = 0 ; i < ARR_SIZE ; i++)
    //         sum += A[i];
    // }

    // #pragma omp parallel default(shared)
    //     #pragma omp for reduction(+: sum)
    //     for ( i = 0 ; i < ARR_SIZE ; i++)
    //         sum += A[i];

    // You can now combine them
															dummyMethod1();
    #pragma omp parallel for default(shared) reduction(+: sum)
        for ( i = 0 ; i < ARR_SIZE ; i++)
            sum += A[i];
															dummyMethod2();

    t2 = omp_get_wtime();

    printf("Sum of the array elements = %d. Time = %g\n", sum, t2-t1);

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