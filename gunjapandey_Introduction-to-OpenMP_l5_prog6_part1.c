#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
int a[]={1,2,4,7,9};
int i,b=0;
dummyMethod1();
#pragma omp parallel for reduction(+:b) schedule(static,2)
for(i=0;i<5;i++){
b=(a[i]*a[i])+b;
dummyMethod2();
printf("Thread:%d : Array Sum = %d\n",omp_get_thread_num(),b);
}
printf("Total Sum of Array : %d\n",b);
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