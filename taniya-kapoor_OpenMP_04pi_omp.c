#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int
main(int argc, char ** argv)
{
    long long int N = 1ULL << 32;

    if (argc > 1) N = atoll(argv[1]);

    double sum = 0.0;
    int sign   = 1;

    struct timespec tstart, tend;
    clock_gettime(CLOCK_MONOTONIC, &tstart);

dummyMethod1();
    #pragma omp parallel for private(sign) reduction(+:sum)
    for (long long int i = 0; i < N; i++) {
        sign = (i & 1ULL) ? (-1) : 1; // or i mod 2 ...
        sum += sign / ((2.0 * i) + 1.0);
    }
dummyMethod2();
    printf("%1.15lf\t", 4 * sum);

    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("%2.9lf\n", (tend.tv_sec - tstart.tv_sec) + (tend.tv_nsec - tstart.tv_nsec) / 1e9f);
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