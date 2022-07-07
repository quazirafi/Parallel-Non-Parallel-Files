/**
 * data-race04.c
 *
 * Description: Data race on index variable j, shared by default.
 *
 * Solution: Add private(j) in omp pragma.
 *
 */

#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000
#define M 1000

float compute(int i, int j) {
  return (i * j) / 2;
}

int main (int argc, char **argv)
{
  int i, j;
  float a[N][M];
    
dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      a[i][j] = compute(i,j);
    }
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