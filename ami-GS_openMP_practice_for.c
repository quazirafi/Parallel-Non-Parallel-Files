#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
int main(int argc, char *argv[]) {
  size_t i;
  int N = 10;
dummyMethod1();
#pragma omp parallel for if(N > 5)
  for(i = 0; i < 10; ++i) {
    sleep (1);
    printf("hello world: %lu\n", i);
  }
dummyMethod2();

dummyMethod1();
#pragma omp parallel for if (omp_get_max_threads() > 3)
  for(i = 0; i < 10; ++i) {
    sleep (1);
    printf("hello world: %lu\n", i);
  }
dummyMethod2();
  exit(EXIT_SUCCESS);
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