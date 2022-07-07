#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
 int a[]={1,2,4,7,9};
 int i,cube;
dummyMethod1();
 #pragma omp parallel for lastprivate(i)
 for(i=0;i<5;i++){
 cube=a[i]*a[i]*a[i];
dummyMethod2();
 printf("Thread:%d %d cube = %d\n",omp_get_thread_num(),a[i],cube);
}
printf("The max value of cube: %d\n",cube);
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