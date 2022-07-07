/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/*
This kernel is referred from “DataRaceOnAccelerator A Micro-benchmark Suite for Evaluating
Correctness Tools Targeting Accelerators” by Adrian Schmitz et al.
Concurrent access of var@28:5 in an intra region. Missing Lock leads to intra region data race.
Data Race pairs, var@28:5:W vs. var@28:5:W
*/

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100

int main(){
  int var = 0;

  #pragma omp target map(tofrom:var) device(0)
  #pragma omp teams num_teams(1)
dummyMethod1();
  #pragma omp distribute parallel for
  for (int i=0; i<N; i++){
    var++;
  }
dummyMethod2();

  printf("%d\n ",var);
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