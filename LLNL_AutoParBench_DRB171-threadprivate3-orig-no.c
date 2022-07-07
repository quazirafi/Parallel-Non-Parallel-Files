/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/* This kernel imitates the nature of a program from the NAS Parallel Benchmarks 3.0 MG suit.
 * There is no data race pairs, example of a threadprivate var and update by TID==0 only.
 */

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static double x[20];
#pragma omp threadprivate(x)

int main(){
  int i;
  double j,k;

dummyMethod1();
  #pragma omp parallel for default(shared)
  for (i = 0; i < 20; i++){
    x[i] = -1.0;
    if(omp_get_thread_num()==0){
      j = x[0];
    }
    if(omp_get_thread_num()==0){
      k = i+0.05;
    }
  }
dummyMethod2();

  printf ("%f %f\n", j, k);

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