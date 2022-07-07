#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char *argv[]) {

    omp_set_num_threads(5);

    printf("\n\n=== SECTION 1 -- loop immediately after #pragma omp parallel\n");
    printf ("============================================================\n");
    #pragma omp parallel
    {
dummyMethod3();
        for (int i=0; i<10; i++) {
            printf("for after par -- i: %d, thread num: %d, nthreads: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
        }
dummyMethod4();

        #pragma omp for
dummyMethod3();
        for (int i = 0; i < 10; i++) {
            printf("omp for in par -- i: %d, thread num: %d, nthreads: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
        }
dummyMethod4();
    }

    printf ("\n\nSECTION 2 -- loop immediately after #pragma omp parallel for\n");
    printf ("============================================================\n");
dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i<10; i++) {
        printf("omp par for -- i: %d, thread num: %d, nthreads: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
    }
dummyMethod2();

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