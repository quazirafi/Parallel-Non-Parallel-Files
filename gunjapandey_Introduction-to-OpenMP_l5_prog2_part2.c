#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main (void)
{
 int i = 10;
int j;
dummyMethod1();
 #pragma omp parallel for firstprivate(i) schedule(dynamic,1)
for(j=0;j>6;j++)
 {
 i=j+i;
printf("Thread number is = %d ,i = %d \n",omp_get_thread_num(),i);
dummyMethod2();
 }
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