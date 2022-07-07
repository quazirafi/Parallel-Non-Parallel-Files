/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/* This kernel imitates the nature of a program from the NAS Parallel Benchmarks 3.0 MG suit.
 * Due to missing construct to write r1[k]@38:9 synchronously, there is a Data Race.
 * Data Race Pair, r1[k]@38:9:W vs. r1[k]@38:9:W
 * */

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 8

int main()
{
  int i,j,k;
  double r1[N], r[N][N][N];

dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        r[i][j][k] = i;
      }
    }
  }
dummyMethod4();


			dummyMethod1();
  #pragma omp parallel for default(shared) private(j,k)
  for (i = 1; i < N-1; i++) {
    for (j = 1; j < N-1; j++) {
      for (k = 0; k < N; k++) {
        r1[k] = r[i][j-1][k] + r[i][j+1][k] + r[i-1][j][k] + r[i+1][j][k];
      }
    }
  }
			dummyMethod2();

			dummyMethod4();
			dummyMethod3();
  for (k = 0; k < N; k++) printf("%f ",r1[k]);

  printf("\n");

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