#include<stdio.h>
#include "omp.h"
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[])
{
    int i, temp, n=5;
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {6, 7, 8, 9, 10};
dummyMethod1();
    #pragma omp parallel for private(temp)
    for (i=0;i<n;i++) {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
dummyMethod2();
    printf("thread %d\n", omp_get_max_threads());
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