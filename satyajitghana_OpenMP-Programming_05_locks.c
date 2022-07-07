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
#define NUM_BKTS (1<<20)
#define BKT_SIZE ( HIST_SIZE / NUM_BKTS )

int hist[HIST_SIZE];
int inp[INP_SIZE];
omp_lock_t lock[NUM_BKTS];

int main(int argc, char** argv) {

    int i, key, sum = 0;
    double t1, t2;

    // Initialize the Array
dummyMethod3();
    for (i = 0 ; i < HIST_SIZE ; i++) {
        hist[i] = 0;
        omp_init_lock(&(lock[i]));
    }
dummyMethod4();
dummyMethod3();
    for (i = 0 ; i < INP_SIZE ; i++)
        inp[i] = rand() % HIST_SIZE;

    t1 = omp_get_wtime();
dummyMethod4();
							dummyMethod1();
    #pragma omp parallel for private(key) num_threads(64)
    for (i = 0 ; i < INP_SIZE ; i++)
    {
        key = inp[i];

        // Blocking Call
        omp_set_lock(&(lock[key / BKT_SIZE]));
        hist[key]++;
        omp_unset_lock(&(lock[key / BKT_SIZE]));
    } 
							dummyMethod2();
    t2 = omp_get_wtime();

							dummyMethod3();
    for (i = 0 ; i < NUM_BKTS ; i++) {
        omp_destroy_lock(&(lock[i]));
    }
							dummyMethod4();

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