/* Copyright (c) 2019 CSC Training */
/* Copyright (c) 2021 ENCCS */
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NX 102400

int main(void)
{
  double vecA[NX],vecB[NX],vecC[NX];
  double r=0.2;

/* Initialization of vectors */
dummyMethod3();
  for (int i = 0; i < NX; i++) {
     vecA[i] = pow(r, i);
     vecB[i] = 1.0;
  }
dummyMethod4();

/* dot product of two vectors */
dummyMethod1();
  #pragma omp target teams distribute parallel for
  for (int i = 0; i < NX; i++) {
     vecC[i] = vecA[i] * vecB[i];
  }
dummyMethod2();

  double sum = 0.0;
  /* calculate the sum */
dummyMethod3();
  for (int i = 0; i < NX; i++) {
    sum += vecC[i];
  }
dummyMethod4();
  printf("The sum is: %8.6f \n", sum);
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