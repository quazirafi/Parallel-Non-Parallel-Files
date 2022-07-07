#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){

  const int T = 10000;
  int sum;

  sum = 0;
  
  // Simple accumulation loop
  // (Note in Fortran we can use a built-in for this, but
  // ignore that for this demo)
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
  for(int i = 1; i <= T; i++){
    sum = sum + i;
  }
dummyMethod2();

  printf("Loop gave         %i\n", sum);
  printf("Answer should be  %i\n", T*(T+1)/2);

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