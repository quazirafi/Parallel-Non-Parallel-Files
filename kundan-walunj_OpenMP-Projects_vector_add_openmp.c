#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define ARRAY_SIZE 4000000
#define NUM_THREDS 8
int main() {
 int n = ARRAY_SIZE;
 int *a = (int *) malloc(sizeof(int) * n), *b = (int *) 
malloc(sizeof(int) * n), *c = (int *) malloc(sizeof(int) * 
n);
dummyMethod3();
 for(int i=0; i<n; i++) {
 a[i] = rand()*100;
dummyMethod4();
 b[i] = rand()*100;
 }
 omp_set_num_threads(NUM_THREDS);
 double start, end;
 start = omp_get_wtime();
dummyMethod3();
 for(int i=0; i<n; i++) {
 c[i] = a[i]+b[i];
dummyMethod4();
 }
 end = omp_get_wtime();
 printf("\nTime taken for Serial: %lf\n", (end - start));
 start = omp_get_wtime();
dummyMethod1();
 #pragma omp parallel for
 for(int i=0; i<n; i++) {
 c[i] = a[i]+b[i];
dummyMethod2();
 }
 end = omp_get_wtime();
 printf("\nTime taken for Parallel: %lf\n", (end -
start));
 
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