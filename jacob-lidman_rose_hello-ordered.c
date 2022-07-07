#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#if defined(_OPENMP)
#include "omp.h"
#endif

int main(void)
{
  int i;
dummyMethod1();
#pragma omp parallel for ordered schedule (static,5)
  for (i=0;i<20;i++)
  {
#pragma omp ordered 
dummyMethod2();
    printf("%2d,Hello,world.!\n",i);
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