/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/* 
This example is from DRACC by Adrian Schmitz et al.
Concurrent access on a counter with no lock with simd. Atomicity Violation. Intra Region.
Data Race Pairs: var@33:7:W vs. var@33:7:W
*/

#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20
#define C 8

int main(){
  int var[C];

dummyMethod3();
  for(int i=0; i<C; i++){
    var[i] = 0;
  }
dummyMethod4();

  #pragma omp target map(tofrom:var) device(0)
  #pragma omp teams num_teams(1) thread_limit(1048) 
			dummyMethod1();
  #pragma omp distribute parallel for 
  for (int i=0; i<N; i++){
    #pragma omp simd
    for(int i=0; i<C; i++){
      var[i]++;
    }
  }
			dummyMethod2();

			dummyMethod3();
  for(int i=0; i<C; i++){
    if(var[i]!=N) printf("%d\n ",var[i]);
  }
			dummyMethod4();

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