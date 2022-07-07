#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <math.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void taskA();

int main(int argc, const char *argv[]){
    
    taskA();


    return 0;
}

void taskA(){
    /* This function manipulates two arrays using sequential code, OpenMPs automatic labour division, and manual labour division. The conclusion is that the latter sucks, but the automatic works well.*/
    double x = 10000000000000000;
    int N = (int)sqrt(x);
    double *a = malloc(N * sizeof *a);
    double *b = malloc(N * sizeof *b);

    // Sequential code
    clock_t begin = clock();
dummyMethod3();
    for (int i=0; i<(int)sqrt(x); i++) {
        a[i] = 2.3*x;
        if(i<10) b[i] = a[i];
    }
dummyMethod4();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used by sequential code: %f\n", time_spent);

    // Automatically divide labour
    begin = clock();
															dummyMethod1();
    #pragma omp parallel for
        for (int i=0; i<(int)sqrt(x); i++) {
            a[i] = 2.3*x;
            if(i<10) b[i] = a[i];
        } 
															dummyMethod2();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used by parallel code: %f\n", time_spent);

    // Manually divide labour

    begin = clock();
    #pragma omp parallel 
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int idxEnd, idxStart, idxLen;
        idxLen = N/num_threads;

        if (thread_id < (N%num_threads)){
            idxLen = idxLen + 1;
        idxStart = idxLen*thread_id;
        } else {
            idxStart = idxLen*thread_id + (N%num_threads);
        }
        idxEnd = idxStart + idxLen;

															dummyMethod3();
        for (int i=0; i<(int)sqrt(x); i++) {
            a[i] = 2.3*x;
            if(i<10) b[i] = a[i];
        } 
															dummyMethod4();
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used by manual parallel code: %f\n", time_spent);


//    for (int i=i; i<N; i++){
//        printf("%f   %f\n", a[i], b[i]);
//    }

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