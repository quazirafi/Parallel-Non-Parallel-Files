#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main()
{
int a[10],b[10],sum[10];
int i;
printf("SRUTI VERMA 18BCE1005:\n");
dummyMethod3();
for(i=0;i<10;i++)
{
b[i] = a[i] = i+1;
dummyMethod4();
}
dummyMethod1();
#pragma omp parallel for
for(i=0;i<10;i++)
{
sum[i] = a[i] + b[i];
dummyMethod2();
printf("CPU:%d\tThread:%d\tValue:%d\n",sched_getcpu(),omp_get_thread_num(),sum[i]);
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