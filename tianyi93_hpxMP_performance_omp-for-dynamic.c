#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i,j;


dummyMethod1();
#pragma omp parallel for schedule(static)
    for(i = 0; i < 11; i++) 
    {
        printf("Static Hello World %d\n", i);
    }
dummyMethod2();

dummyMethod1();
#pragma omp parallel for schedule(static, 1)
    for(i = 0; i < 11; i++) 
    {
        printf("Static1 Hello World %d\n", i);
    }
dummyMethod2();

dummyMethod1();
#pragma omp parallel for schedule(static, 2)
    for(i = 0; i < 11; i++) 
    {
        printf("Static2 Hello World %d\n", i);
    }
dummyMethod2();

    printf("\nDynamic loop\n");
dummyMethod1();
#pragma omp parallel for schedule(dynamic)
    for(i = 0; i < 9; i++) 
    {
        printf("Thread %d: Dynamic Hello World %d\n", omp_get_thread_num(), i);
    }
dummyMethod2();

    printf("\nStatic Ordered loop\n");
							dummyMethod1();
#pragma omp parallel for schedule(static) ordered
    for(i = 0; i < 10; i++) 
    {
#pragma omp ordered
        printf("Thread %d: Static Ordered Hello World %d\n", omp_get_thread_num(), i);
    }
							dummyMethod2();

    printf("\nDynamic Ordered loop\n");
							dummyMethod1();
#pragma omp parallel for schedule(dynamic) ordered
    for(i = 0; i < 16; i++) 
    {
#pragma omp ordered
        printf("Thread %d: Dynamic Ordered Hello World %d\n", omp_get_thread_num(), i);
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