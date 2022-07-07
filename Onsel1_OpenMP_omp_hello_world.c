#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
 
int main(void){
int i;
int x;
x=44;
int OMP_NUM_THREADS=7;
dummyMethod1();
#pragma omp parallel for shared(x) 
for(i=0;i<=5;i++){
x=i;
dummyMethod2();
printf("Thread number: %d     x: %d\n",omp_get_thread_num(),x);
}
printf("x is %d\n", x);
 
 
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