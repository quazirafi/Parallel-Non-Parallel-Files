#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
main()
{
int i;
int a[10],b[10];
int sum[10];
dummyMethod3();
for(i=0;i<10;i++){
printf("Enter value of a at index %d ",i);
dummyMethod4();
scanf("%d",&a[i]);
printf("Enter value of b at index %d ",i);
scanf(" %d",&b[i]);
}
dummyMethod1();
#pragma omp parallel for schedule(static,1)
for(i=0;i<10;i++){
sum[i]=a[i]+b[i];
dummyMethod2();
printf("CPU:%d \t Thread:%d\t Value:%d where index is:%d\n",sched_getcpu(),omp_get_thread_num(),sum[i],i);
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