// Locks using buckets
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define INP_SIZE (1<<26)
#define HIST_SIZE (1<<20)

int hist[HIST_SIZE];
int inp[INP_SIZE];

int main(int argc, char** argv) {

    int i, key, sum = 0;
    double t1, t2;

    // Initialize the Array
dummyMethod3();
    for (i = 0 ; i < HIST_SIZE ; i++) {
        hist[i] = 0;
    }
dummyMethod4();
dummyMethod3();
    for (i = 0 ; i < INP_SIZE ; i++)
        inp[i] = rand() % HIST_SIZE;

    t1 = omp_get_wtime();
dummyMethod4();
    #pragma omp parallel for private(key) num_threads(64)
							dummyMethod3();
    for (i = 0 ; i < INP_SIZE ; i++)
    {
        key = inp[i];

        #pragma omp atomic // Mini Critical Section
        hist[key]++;

        // Its a critical section on the memory section
        // Basically two threads cannot modify the same memory location at the same time
    } 
							dummyMethod4();
    t2 = omp_get_wtime();

							dummyMethod1();
    #pragma omp parallel for reduction(+: sum)
    for (i = 0 ; i < HIST_SIZE ; i++)
        sum += hist[i];
							dummyMethod2();

    printf("Sum = %d, Time = %g\n", sum, t2-t1);

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