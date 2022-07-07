#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
int main()
{
int i;
int n;
scanf("%d",&n);
int a[n];
dummyMethod1();
#pragma omp parallel for schedule(static,2)
for(i=1;i<n;i++)
{
for(int j=2;j<i;j++){
dummyMethod2();
if(i%j==0){
printf("%d\n",i);
break;
}
}}
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