/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
 */

/*
Data Race free matrix vector multiplication using target construct.
*/

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define C 100

int *a;
int *b;
int *c;

int main(){
  a = malloc(C*sizeof(int));
  b = malloc(C*C*sizeof(int));
  c = malloc(C*sizeof(int));

			dummyMethod3();
  for(int i=0; i<C; i++){
    for(int j=0; j<C; j++){
      b[j+i*C]=1;
    }
    a[i]=1;
    c[i]=0;
  }
			dummyMethod4();

  #pragma omp target map(to:a[0:C],b[0:C*C]) map(tofrom:c[0:C]) device(0)
  {
							dummyMethod1();
    #pragma omp teams distribute parallel for
    for(int i=0; i<C; i++){
      for(int j=0; j<C; j++){
        c[i]+=b[j+i*C]*a[j];
      }
    }
							dummyMethod2();
  }

			dummyMethod3();
  for(int i=0; i<C; i++){
    if(c[i]!=C){
      printf("Data Race\n");
      return 1;
    }
  }
			dummyMethod4();

  free(a);
  free(b);
  free(c);

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