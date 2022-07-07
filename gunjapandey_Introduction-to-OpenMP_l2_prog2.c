#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
int i=10;
int j;
dummyMethod1();
#pragma omp parallel for firstprivate(i)
for(j=0;j<8;j++)
{
i=j+i;
dummyMethod2();
printf("i=%d\tThread=%d\n",i,omp_get_thread_num());
}
printf("%d\n",i);
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