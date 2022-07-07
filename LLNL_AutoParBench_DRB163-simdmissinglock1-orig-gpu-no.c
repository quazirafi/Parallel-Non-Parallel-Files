/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/*
Concurrent access of var@31:7 has no atomicity violation. No data race present.
*/

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100
#define C 64

int main(){
  int var[C];

dummyMethod3();
  for(int i=0; i<C; i++){
    var[i]=0;
  }
dummyMethod4();

  #pragma omp target map(tofrom:var[0:C]) device(0)
dummyMethod1();
  #pragma omp teams distribute parallel for reduction(+:var) 
  for (int i=0; i<N; i++){
    #pragma omp simd
    for(int i=0; i<C; i++){
      var[i]++;
    }
  }
dummyMethod2();

			dummyMethod3();
  for(int i=0; i<C; i++){
    if(var[i]!=100){
      printf("%d\n",var[i]);
    }
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