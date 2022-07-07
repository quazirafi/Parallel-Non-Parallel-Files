#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
double a[10];

int foo()
{
  double max_val = - 1e99;
  double min_val = 1e99;
  int i;
  
dummyMethod1();
#pragma omp parallel for private (i) reduction (max:max_val) reduction (min:min_val)
  for (i = 0; i <= 9; i += 1) {
    if (a[i] > max_val) {
      max_val = a[i];
    }
    if (a[i] < min_val) 
      min_val = a[i];
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