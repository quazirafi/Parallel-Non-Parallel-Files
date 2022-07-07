#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc,char* argv[]){
    int a[20];
    int n,i,tc,sum=0;
    tc=strtol(argv[1],NULL,10);
    printf("enter the no of elements to be entered..\n");
    scanf("%d",&n);
    printf("enter the elements..\n");
dummyMethod3();
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
dummyMethod4();
dummyMethod1();
#pragma omp parallel for num_threads(tc)\
reduction(+: sum)
for(i=0;i<n;i++)
sum+=a[i];
dummyMethod2();
printf("summation is %d",sum);
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