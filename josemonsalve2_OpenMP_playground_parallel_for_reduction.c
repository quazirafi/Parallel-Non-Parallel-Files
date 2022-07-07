#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10

int main() {
    int x = 5;
dummyMethod1();
    #pragma omp parallel for reduction(+:x)
    for (int i = 0; i < N; i++) {
        printf("Thread %d, x=%d, address %p\n", omp_get_thread_num(), x, &x);
        x = i;
    }
dummyMethod2();
    printf("The final value of x is %d\n",x);
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