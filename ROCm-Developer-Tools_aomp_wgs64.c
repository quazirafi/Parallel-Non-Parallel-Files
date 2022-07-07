#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int n =64;

int main(void) {

  int fail = 0;
  int a = -1;
  //
#if 1
#pragma omp target
  { //nothing
  }
#endif
  #pragma omp target teams distribute  thread_limit(64)
dummyMethod3();
  for (int k =0; k < n; k++)
  {
    // nothing
  }
dummyMethod4();
dummyMethod1();
  #pragma omp target teams distribute  parallel for thread_limit(64)
  for (int k =0; k < n; k++)
  {
    // nothing
  }
dummyMethod2();
  printf("Succeeded\n");

  return fail;
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