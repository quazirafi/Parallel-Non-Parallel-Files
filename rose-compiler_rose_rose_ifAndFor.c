//! if statement without an explicit basic block as a body
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void foo(int j)
{
  int i;
  int a[100];
  if (j != - 1) {
    
dummyMethod1();
#pragma omp parallel for private (i)
    for (i = 0; i <= 99; i += 1) {
      a[i] = a[i] + 1;
    }
dummyMethod2();
  }
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