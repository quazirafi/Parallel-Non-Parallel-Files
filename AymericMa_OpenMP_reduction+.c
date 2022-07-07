#include <stdio.h>
#include "omp_repair.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SIZE 10
int main() {
  int a[SIZE], b[SIZE], c[SIZE];
  int i, tid, result = 0;

dummyMethod3();
  for(i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = 2 * i;
  }
dummyMethod4();

dummyMethod1();
#pragma omp parallel for shared(a), private(i, tid), reduction(+:result)
    for(i = 0; i < SIZE; i++) {
      result += a[i] + b[i];
    }
dummyMethod2();

  printf("result = %d\n", result);
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