#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
int main () 
{
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    int b[10]={0,1,2,3,4,5,6,7,8,9};
    int sum[10];
    
    int i;
      int p=sched_getcpu();
dummyMethod1();
	   #pragma omp parallel for schedule(static,2)
		for (i=0; i < 10; i++) 
		{
		sum[i] = a[i] + b[i]; 
dummyMethod2();
		printf("CPU:%d\tThread:%d\tValue%d\t at i%d\n",p,omp_get_thread_num(),sum[i],i);
		}
		
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