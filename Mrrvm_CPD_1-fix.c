#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int function(int *a, int N, int value) {
    int retval = 0;
    int i;

dummyMethod1();
    #pragma omp parallel for reduction(sum : retval)
    for (i = 0; i < N; i++) {
        if (a[i] == value)
            retval++;
    }
dummyMethod2();

    return retval;
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