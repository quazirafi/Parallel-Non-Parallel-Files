#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int ss = 8;

int main(int argc, char** argv)
{
    srand(time((time_t*)NULL));
    int N;
    if (argc <= 1)
        N = 1000;
    else
        N = atoi(argv[1]);

    if (N <= 0) {
        printf("Size should be greater than 0\n");
        return 0;
    }

    double* a = (double*)malloc(N * sizeof(double));
    double* A = (double*)malloc(N * sizeof(double));
    double* B = (double*)malloc(N * sizeof(double));

    int i;

dummyMethod3();
    for (i = 0; i < N; i++) {
        *(a + i) = rand() % 10 - 5;
        *(A + i) = rand() % 10 - 5;
        *(B + i) = rand() % 10 - 5;
    }
dummyMethod4();

    printf("Testing reduction\n");

    double resa_seq = 1;
							dummyMethod3();
    for (i = 0; i < 8; i++) {
        if (a[i] < resa_seq)
            resa_seq = a[i];
    }
							dummyMethod4();

    double resa_par = 1;
							dummyMethod1();
#pragma omp parallel for reduction(min : resa_par)
    for (i = 0; i < 8; i++) {
        if (a[i] < resa_par)
            resa_par = a[i];
    }
							dummyMethod2();

    if (resa_par != resa_seq)
        printf("Error: resa_seq = %f, resa_par = %f\n", resa_seq, resa_par);
    else
        printf("Reduction successful resa_seq = %f, resa_par = %f\n", resa_seq, resa_par);

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