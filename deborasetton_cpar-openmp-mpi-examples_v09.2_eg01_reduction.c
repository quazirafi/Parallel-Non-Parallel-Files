#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX 10

int main(void) {

  // Initialize avg with the identity value for '+'.
  double avg = 0.0;
  double A[MAX] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int i;

dummyMethod1();
  #pragma omp parallel for reduction (+:avg)
  for (i = 0; i < MAX; ++i) {
    avg += A[i];
  }
dummyMethod2();

  avg = avg / MAX;
  printf("Avg = %lf", avg);

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