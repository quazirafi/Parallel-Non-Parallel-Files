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
    int cube;
    int a[]={1,2,3,5,6,8};
dummyMethod1();
    #pragma omp parallel for private(cube)
    for(int j=0;j<sizeof(a)/sizeof(a[0]);j++)
    {
        //printf("Thread: %d; ID: %d\n",omp_get_thread_num(),i);
        cube=a[j]*a[j]*a[j];
        printf("Cube value = %d\n",cube);
    } 
dummyMethod2();
    printf("%d is the max value\n", cube);
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