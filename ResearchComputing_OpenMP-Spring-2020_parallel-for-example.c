#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[]) {

  long int sum = 0;

dummyMethod1();
  #pragma omp parallel for reduction(+:sum)
  for(long int i = 1; i < 1000000001; i++){
    sum += i;
  }
dummyMethod2();

  printf("Sum of 1 to 1000000000: %ld\n", sum);

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