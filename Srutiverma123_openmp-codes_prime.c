#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
int p,i,j,flag=1;
scanf("%d",&p);
printf("SRUTI VERMA 18BCE1005:\n");
dummyMethod1();
#pragma omp parallel for firstprivate(flag)
for(i=2;i<=p;i++)
{
f=1;
dummyMethod2();
for(j=2;j<=i/2;j++)
if(i%j==0)
	flag=0;
if(flag)
	printf("Thread no: %d\t%d is a prime number\n",omp_get_thread_num(),i);
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