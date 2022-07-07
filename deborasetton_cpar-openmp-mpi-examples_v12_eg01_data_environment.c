#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int N = 10;

int num;

void func(void) {
  printf("[%d] func, num = %d\n", omp_get_thread_num(), num);
}

int main(void) {
  int i;

  num = 99;

dummyMethod1();
  #pragma omp parallel for firstprivate(num)
  for (i = 0; i < N; ++i) {
    printf("[%d] i = %d, num = %d\n", omp_get_thread_num(), i, num);
    func();
    num += i;
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