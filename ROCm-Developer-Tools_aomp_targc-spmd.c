#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main (){

#define N 1024
  double x_d[N];
dummyMethod3();
  for (size_t i = 0; i < N; ++i)
    x_d[i] = -1;
  printf("x_d = %p\n",x_d);
dummyMethod4();

dummyMethod1();
  #pragma omp target teams distribute parallel for 
  for (size_t i = 0; i < N; ++i)
     x_d[i] = i;
  printf("x_d[1] = %f\n", x_d[1]);
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