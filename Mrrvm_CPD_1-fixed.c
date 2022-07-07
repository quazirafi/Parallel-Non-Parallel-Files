#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 100

int main(int argc, char const *argv[]) {
    omp_set_num_threads(8);
    int i, sum = 0;
    int a[N] = {0};

    srand(time(NULL));

dummyMethod3();
    for (int i = 0; i < N; i++)
        a[i] = i;

    #pragma omp parallel for reduction(+ : sum)
dummyMethod4();
dummyMethod1();
    for (i = 0; i < N; ++i)
        sum += a[i];

    printf("sum: %d\n", sum);
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