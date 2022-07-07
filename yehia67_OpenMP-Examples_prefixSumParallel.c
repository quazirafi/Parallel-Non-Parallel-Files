//gcc -fopenmp prefixSumParallel.c
//./a.out
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
  int arr[4] ={2,3,7,5};
  int prefix[4];
  prefix[0] = arr[0];
  #pragma omp parallel
  {
dummyMethod1();
  #pragma omp parallel for
  for(int i = 1; i < 4; i++)
  {
     prefix[i] = arr[i] + prefix[i-1];
  }
dummyMethod2();
  }
  
dummyMethod3();
  for(size_t i = 0; i < 4; i++)
  {
   printf("%d \n",prefix[i]);  
  }
dummyMethod4();
  
  
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