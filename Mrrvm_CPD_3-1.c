#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000

int main(int argc, char const *argv[]) {
    omp_set_num_threads(8);
    int i;
    int a[N] = {0};
    int value = 0;
    int found = 0;

dummyMethod1();
    #pragma omp parallel for reduction(+ : found)
    for (i = 0; i < N; i++)
        if (a[i] == value) {
            found = found + 1;
            printf("found so far: %i values\n", found);
        }

    printf("found so far: %i values\n", found);
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