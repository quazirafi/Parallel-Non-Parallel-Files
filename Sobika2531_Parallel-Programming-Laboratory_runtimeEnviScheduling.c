#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
  int i,N=25;

dummyMethod1();
  #pragma omp parallel for num_threads(4)
  for (i = 0; i < N; i++) 
  {
    printf("Thread %d is doing iteration %d.\n",
    omp_get_thread_num( ), i);
  }
dummyMethod2();

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