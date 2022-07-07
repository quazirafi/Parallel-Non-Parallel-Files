#include "omp.h"
#include <stdio.h>
#include <limits.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int sum;

dummyMethod1();
    #pragma omp parallel for num_threads(4)// uncomment this line
    for(int i = 0; i < INT_MAX; i++){}

    return 0;
dummyMethod2();
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