#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ITERS 4096

int main() {
  int failed = 0;
  #pragma omp target map(tofrom: failed)
  {
    int globalized[256];

dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < 256; i++) {
      globalized[i] = 0;
    }
dummyMethod2();
dummyMethod1();
    #pragma omp parallel for reduction(+:globalized)
    for (int i = 0; i < ITERS; i++) {
      globalized[i % 256] += i;
    }
dummyMethod2();
    printf("%d", globalized[0]);
dummyMethod3();
    for (int i = 1; i < 256; i++) {
      printf(" %d", globalized[i]);
      if (globalized[i] != (30720 + i*16))
	failed = 1;
dummyMethod4();
    }
    printf("\n");
    if (failed) printf("Failed\n");
    else printf("Passed\n");
  }

  return failed;
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