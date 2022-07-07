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
    int sum;
    int i;
    
dummyMethod1();
 #pragma omp parallel for reduction(+:sum)
		for (i=0; i < 10; i++) 
		{
		sum += a[i] + b[i]; 
dummyMethod2();
		printf("%d\n",sum);
		}
		printf("%d",sum);
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