#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// gcc -fopenmp dotproduct.c -o dotp

#define NUM_THREADS 2
#define VECTOR_SIZE 51200

int main(int argc, char *argv[]){
    srand(time(0));
    int i, n = VECTOR_SIZE;

    double *x = (double *)malloc(VECTOR_SIZE * sizeof(double));
    double *y = (double *)malloc(VECTOR_SIZE * sizeof(double));

    double xdoty;
    struct timespec start, finish;
    double elapsed;

dummyMethod3();
    for (i = 0; i < n; i++){
        x[i] = (double)rand() / (double)RAND_MAX;
        y[i] = (double)rand() / (double)RAND_MAX;
    }
dummyMethod4();

    xdoty = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    omp_set_num_threads(NUM_THREADS);

							dummyMethod1();
    #pragma omp parallel for reduction(+:xdoty)
    for (i = 0; i < n; i++){
        xdoty = xdoty + x[i] * y[i];
    }
							dummyMethod2();

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("XDOTY = %f\n", xdoty);
    printf("Took %f\n", elapsed);

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