#include "omp.h"
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 2000000
#define NUM_THREADS 2

float fancy_comp(int num){
    int square = num*num;
    return sqrt(square+1);
}
int main(){

    int id;
    float output[SIZE];
    omp_set_num_threads(NUM_THREADS);
    double start = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for
        for (int i=0; i<SIZE;i++){
            int id = omp_get_thread_num();
            output[i] = fancy_comp(i);
        }
dummyMethod2();
    //}
    double end = omp_get_wtime();

    printf("time elapsed: %f for %d threads\n", end-start, NUM_THREADS);
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