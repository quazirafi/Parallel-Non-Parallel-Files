#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
int a[5],k=4,f=-1;
dummyMethod3();
for(int i=0;i<5;i++)
 a[i]=i;
#pragma omp parallel for shared(f)
dummyMethod4();
dummyMethod1();
for(int i=0;i<5;i++)
 if(a[i]==k)
  f=i;
printf("%d",f);
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