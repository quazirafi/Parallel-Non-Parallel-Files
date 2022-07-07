#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
    int size = 10000;
    float a[size];

dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i<size; i++){
        a[i] = 1.0;
    }
dummyMethod2();
    float sum=0.0;
    #pragma omp parallel
    {
        float ps[omp_get_num_threads()]  ;
dummyMethod1();
        #pragma omp parallel for
        for (int i=0; i<size; i++){

            ps[omp_get_thread_num()] = ps[omp_get_thread_num()] +a[i];
        }
dummyMethod2();
        #pragma omp critical
        {
            sum+=ps[omp_get_thread_num()];
        }
    }

    printf("%f\n", sum);
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