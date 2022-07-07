/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/*This example is referred from DRACC by Adrian Schmitz et al.
The distribute parallel for directive at line 24 will execute loop using multiple teams.
The loop iterations are distributed across the teams in chunks in round robin fashion.
The missing lock enclosing var@26:5 leads to data race. Data Race Pairs, var@26:5:W vs. var@26:5:W
*/

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){

  int var=0,i;

  #pragma omp target map(tofrom:var) device(0)
dummyMethod1();
  #pragma omp teams distribute parallel for
  for (int i=0; i<100; i++){
    var++;
  }
dummyMethod2();

  printf("%d\n",var);
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