// omp_atomic.cpp
// compile with: /openmp
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
dummyMethod1();
    #pragma omp parallel for
    for (int i=0;i<10;i++){
        printf("%i\n", i);
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