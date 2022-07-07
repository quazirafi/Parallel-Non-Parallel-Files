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
    int a[10],b[10];
 	int I, sum[10];
    printf("Enter the values of array A :");
dummyMethod3();
    for(I=0;I<10;I++)
    {
        scanf("%d",&a[I]);
    }
dummyMethod4();
    printf("Enter the values of array B :");
dummyMethod3();
    for(I=0;I<10;I++)
    {
        scanf("%d",&b[I]);
    }
dummyMethod4();
dummyMethod1();
	#pragma omp parallel for
	for (I=0; I < 10; I++) 
	{
	    sum[I] = a[I] + b[I]; 
        printf("CPU %d \t Thread: %d Value: %d \n",sched_getcpu(),omp_get_thread_num(),sum[I]);
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