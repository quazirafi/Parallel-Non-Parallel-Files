#include <math.h>
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 50000000

void calc_stuff(void);

int main() {
  calc_stuff();

  return 0;
}

void calc_stuff() {
  double *c = (double *)malloc(sizeof(double) * SIZE);

dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < SIZE; i++) {
    c[i] = sqrt(i * 32) + sqrt(i * 16 + i * 8) + sqrt(i * 4 + i * 2 + i);
    c[i] -= sqrt(i * 32 * i * 16 + i * 4 + i * 2 + i);
    c[i] += pow(i * 32, 8) + pow(i * 16, 12);
  }
dummyMethod2();

  free(c);
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