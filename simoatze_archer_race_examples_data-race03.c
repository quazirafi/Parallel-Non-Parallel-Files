/**
 * data-race03.c
 *
 * Description: Data race on variable x, shared by default.
 *
 * Solution: Add private(x) in omp pragma.
 *
 */

#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000

int main (int argc, char **argv)
{
  int i;
  float a[N], b[N], x;

  // Vector initialization
dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < N; ++i) {
    b[i] = i * i;
  }
dummyMethod2();
    
dummyMethod1();
#pragma omp parallel for
  for (i = 1; i < N; i++) {
      x = sqrt(b[i]) - 1;
      a[i] = x * x + 2 * x + 1;
    } /* end of omp parallel for */
}
dummyMethod2();
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