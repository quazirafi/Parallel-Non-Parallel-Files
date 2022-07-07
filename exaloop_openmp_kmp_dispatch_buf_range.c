// RUN: %libomp-compile
// RUN: env KMP_DISP_NUM_BUFFERS=0 %libomp-run 2>&1 | FileCheck --check-prefix=SMALL %s
// RUN: env KMP_DISP_NUM_BUFFERS=4097 %libomp-run 2>&1 | FileCheck --check-prefix=LARGE %s
// SMALL: OMP: Warning
// SMALL-SAME: KMP_DISP_NUM_BUFFERS
// SMALL-SAME: too small
// LARGE: OMP: Warning
// LARGE-SAME: KMP_DISP_NUM_BUFFERS
// LARGE-SAME: too large
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
  int i;
dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < 1000; i++) {}
  return EXIT_SUCCESS;
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