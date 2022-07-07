#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char *argv[]) {
    omp_set_num_threads(6);
    int i, v[10];
dummyMethod1();
    #pragma omp parallel for schedule(static, 1)
    for (i = 0; i < 20; i++)
        v[omp_get_thread_num()] = i;
    #pragma omp parallel
dummyMethod2();
    #pragma omp single
dummyMethod3();
    for (i = 0; i < omp_get_num_threads(); i++)
        printf("%d\n", v[i]);
    return 0;
dummyMethod4();
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