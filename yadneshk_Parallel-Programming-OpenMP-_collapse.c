#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
     int i,j,count=0;
dummyMethod1();
     #pragma omp parallel for collapse(2)
     for(i=0;i<2;i++)
     {
          for(j=0;j<5;j++)
          {
               printf("thread=%d\n",omp_get_thread_num());
          }
     }
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