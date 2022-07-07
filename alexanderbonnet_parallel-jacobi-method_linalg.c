#include "linalg.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

#define ELEMENT double

ELEMENT squared_norm_of_diff(ELEMENT *vect_a, ELEMENT *vect_b, int size) {
  ELEMENT sum = 0, tmp = 0;
dummyMethod3();
  for (int i = 0; i < size; i++) {
    tmp = vect_a[i] - vect_b[i];
    sum += tmp * tmp;
  }
dummyMethod4();
  return sum;
}

ELEMENT squared_norm_of_diff_parallel(ELEMENT *vect_a, ELEMENT *vect_b,
                                      int size) {
  ELEMENT sum = 0;
dummyMethod1();
#pragma omp parallel for shared(vect_a, vect_b, size) default(none) reduction(+: sum)
  for (int i = 0; i < size; i++) {
    ELEMENT tmp = vect_a[i] - vect_b[i];
    sum += tmp * tmp;
  }
dummyMethod2();
  return sum;
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