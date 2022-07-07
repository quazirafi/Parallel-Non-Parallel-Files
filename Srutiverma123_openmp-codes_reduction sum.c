#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
printf("sruti verma 18bce1005 result: ");
int a[5],b[5];
int sum=0;int i;
dummyMethod3();
for(int j=0;j<5;j++){
scanf("%d",&a[j]);
dummyMethod4();
scanf("%d",&b[j]);

}
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
for(i=0;i<5;i++){
sum=sum+a[i]+b[i];
dummyMethod2();

printf("CPU:%d\t Thread:%d\t Value:%d\n",sched_getcpu(), omp_get_thread_num(), sum);
}
printf("sum= %d\n",sum);
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