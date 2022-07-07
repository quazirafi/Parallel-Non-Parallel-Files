#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void) {
    int i;

dummyMethod1();
    #pragma omp parallel for num_threads(2)
    for(i = 0; i < 4; i++) {
        printf("Iteration: %d, Thread %d\n", i, omp_get_thread_num());
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