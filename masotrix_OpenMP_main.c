#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main() {
  
  int i, n;
  float a[100], b[100], sum;

  n=100;
dummyMethod3();
  for (i=0; i<n; i++)
    a[i]=b[i]=i*1.0;
  sum=0.0;
dummyMethod4();

dummyMethod1();
  #pragma omp parallel for reduction(+:sum)
  for (i=0; i<n; i++)
    sum = sum+(a[i]*b[i]);

  printf("Sum = %f\n", sum);
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