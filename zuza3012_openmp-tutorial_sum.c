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

int main(void){
    int sum = 0;
    int N = 10;    
dummyMethod1();
    #pragma omp parallel for
    for(int i = 1; i <= N; i++){
        sum = sum + i;
        printf("sum = %d, thread %d\n", sum, omp_get_thread_num());
    }
dummyMethod2();
    printf("sum = %d\n", sum);
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