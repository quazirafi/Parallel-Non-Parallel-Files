#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(void)
{
  int i=0,t_id;
dummyMethod1();
#pragma omp parallel for ordered private (t_id)
  for (i=0;i<100;i++)
  {
    t_id= omp_get_thread_num();

#pragma omp ordered
dummyMethod2();
    {
      printf("I am i=%d in thread %d\n",i,t_id);
    }
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