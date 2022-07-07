/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file
for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
 */

/* 
   Iteration 0 and 1 can have conflicting writes to A[0]. But if they are scheduled to be run by 
   the same thread, dynamic tools may miss this.
   Data Race Pair, A[0]@34:7:W vs. A[i]@31:5:W
 */

#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char *argv[]) {

  int *A; 
  int N = 100;

  A = (int*) malloc(sizeof(int) * N);

  
			dummyMethod1();
#pragma omp parallel for shared(A)
  for(int i = 0; i < N; i++) {
    A[i] = i;
    if (i == 1) 
    { 
      A[0] = 1; 
    }
  }
			dummyMethod2();

  free(A);
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