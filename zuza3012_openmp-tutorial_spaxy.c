#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#else
   #define omp_get_thread_num() 0
#endif
#include <stdlib.h>

int main(void){
    int a = 2;
    int y = 3;
    int N = 10;
    int x[N], z[N];

dummyMethod1();
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        x[i]=rand()%100;
        z[i] = a * x[i] + y;
        printf("Thread id: %d z[%d] = 2 * %d + 3 = %d \n", omp_get_thread_num(), i, x[i], z[i]);
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