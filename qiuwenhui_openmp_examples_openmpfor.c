/*
 * @Author: mikey.qrobot
 * @Date: 2019-01-24 11:25:32 
 * @Last Modified by:   mikey.qrobot
 * @Last Modified time: 2019-01-24 11:25:32 
 */
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
    #pragma omp parallel
dummyMethod3();
       for(int i = 0; i < 10; i++)
       {
           printf("%d ",i);
           /* code */
       }
dummyMethod4();
       printf("\n");
       //for x循环并行声明形式2
dummyMethod1();
       #pragma omp parallel for
       for(int j = 0; j < 10; ++j)
       {
           /* code */
           printf("%d ",j);
       }
dummyMethod2();
         printf("\n");
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