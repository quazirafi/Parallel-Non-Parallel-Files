#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char*argv[]) {
  int i, t = get_omp_num_threads();
dummyMethod1();
#pragma omp parallel for
  for(i=0;i<t;i++) {
    fprintf(stdout, "Thread #%d\n", i);
  }
dummyMethod2();
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