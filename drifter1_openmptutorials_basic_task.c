#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10

int main(){

    int i;

    /* parallel for */
    printf("Parallel For:\n");
dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N; i++){
        printf("Thread %d runs iteration %d\n", omp_get_thread_num(), i);
    }
dummyMethod2();

    /* parallel for using tasks */
    printf("\nParallel For using Tasks:\n");
    #pragma omp parallel
    {
        # pragma omp single
dummyMethod3();
        for (i = 0; i < N; i++){
            #pragma omp task
            printf("Thread %d runs iteration %d\n", omp_get_thread_num(), i);
        }
dummyMethod4();
    }

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