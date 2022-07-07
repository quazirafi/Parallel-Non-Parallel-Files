#include "omp.h"
#include<stdio.h>
#include <sched.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE 
int main () 
{
    int i=10;
dummyMethod1();
    #pragma omp parallel for firstprivate(i)
    for(int j=0;j<10;j++)
    {
        i=i+j;
        printf("Thread: %d; ID: %d\n",omp_get_thread_num(),i);
        printf("i = %d\n",i);
    } 
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