/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/*
Concurrent access of var@28:5 in an intra region. Lock ensures that there is no data race.
*/

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100

int main(){
  omp_lock_t lck;
  int var=0;
  omp_init_lock(&lck);

  #pragma omp target map(tofrom:var) device(0)
  #pragma omp teams num_teams(1)
dummyMethod1();
  #pragma omp distribute parallel for
  for (int i=0; i<N; i++){
    omp_set_lock(&lck);
    var++;
    omp_unset_lock(&lck);
  }
dummyMethod2();

  omp_destroy_lock(&lck);
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