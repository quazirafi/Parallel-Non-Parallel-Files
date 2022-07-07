#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main(int argc, char** argv) {

  int buffer [10] = {1,5,2,8,4,1,0,7,3,7};
  int sum = 0;

dummyMethod1();
  #pragma omp parallel for reduction(+:sum)
  for (int i=0; i<10; i++) {
    sum += buffer[i];
  }
dummyMethod2();

  printf("Sum = %d\n", sum);
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