#include <stdio.h>
#include "omp.h"
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
  int i,sum=77;
  int num_steps=100;

  omp_set_num_threads(4);

dummyMethod1();
#pragma omp parallel for firstprivate (sum) lastprivate (sum)
  for(i=1;i<=num_steps;i++)
  {
    sum=sum + i;
  }
dummyMethod2();
  printf("sum=%d\n",sum);

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