#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DIMENSIONS 500000
#define NUM_THREADS 4
int main(){
    float a[DIMENSIONS], b[DIMENSIONS], c[DIMENSIONS];
    // fill the vectors
    printf("Filling vectors\n");
    omp_set_num_threads(NUM_THREADS);
dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i<DIMENSIONS; i++){
        a[i] = 0.0;
        b[i] = 1.0;
        c[i] = 2.0;
     }

     double start = omp_get_wtime();
     int i;
dummyMethod1();
     #pragma omp parallel for private(i)
     for (i=0; i<DIMENSIONS; i++){
         a[i] = b[i] + c[i];
     }
dummyMethod2();
     double end = omp_get_wtime();
     printf("compute time: %f\n ", end-start);
dummyMethod3();
     for (int i=0; i<DIMENSIONS; i++){
         if(a[i]!=3){
             printf("BUZZ\n");
         }
     }
dummyMethod4();


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