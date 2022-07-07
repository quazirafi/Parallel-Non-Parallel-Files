#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main()
{
  double sum   =  0;
  int width    =  40000000;

dummyMethod1();
  #pragma omp parallel for simd reduction(+:sum)
  for(int i = 0; i < width; i++)
  {
     sum += i;
  }
dummyMethod2();

  printf("\nSum = %lf\n",sum);
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