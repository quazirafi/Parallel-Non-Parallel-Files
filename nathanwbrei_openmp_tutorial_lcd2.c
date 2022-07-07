#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main(int argc, char** argv) {

  // Correct, but inefficient
  // Parallelism too granular
  int A[3][8] = {{1,5,2,8,4,1,0,7},
                 {5,6,8,1,3,6,8,9},
                 {1,2,6,3,1,7,3,3}};

  for (int i=1; i<3; i++) {
dummyMethod1();
    #pragma omp parallel for
    for (int j=0; j<8; j++) {
      A[0][j] += A[i][j];
    }}
dummyMethod2();
  for (int j=0; j<8; j++) {
    printf("%d ", A[0][j]);
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