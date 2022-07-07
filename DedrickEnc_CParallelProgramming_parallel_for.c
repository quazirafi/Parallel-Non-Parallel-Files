/**
* this first program is for using the directive parallel
* and for in for loup. To illustrate how the parallelism is done 
* we used a openmp function to show how threads performs together in the 
* loop 
**/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
int n; //variable for iteration

dummyMethod1();
#pragma omp parallel for //telling the compiler that he should execute the following for loop in parallel

for(n=0; n<10; n++){
 printf("Iteration %d processed by thread %d \n", n, omp_get_thread_num());
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