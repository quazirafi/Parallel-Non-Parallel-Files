#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp-simd -fdump-tree-original" } */

#pragma omp declare simd
float bar(float b) {
  return b*b;
}

void foo(int n, float *a, float *b)
{
  int i; 
#pragma omp simd
dummyMethod3();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp for simd
dummyMethod4();
dummyMethod3();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp distribute simd
dummyMethod4();
dummyMethod3();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp distribute parallel for simd
dummyMethod4();
dummyMethod1();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp parallel for simd
dummyMethod2();
dummyMethod1();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp teams distribute simd
dummyMethod2();
dummyMethod3();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp target teams distribute simd
dummyMethod4();
dummyMethod3();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
#pragma omp teams distribute parallel for simd
dummyMethod4();
			dummyMethod1();
  for (i = 0; i < n ; i++)
    a[i] = b[i];
			dummyMethod2();
			dummyMethod1();
#pragma omp target teams distribute parallel for simd
  for (i = 0; i < n ; i++)
    a[i] = b[i];
			dummyMethod2();
}

/* { dg-final { scan-tree-dump-times "pragma omp simd" 9 "original" } } */
/* { dg-final { scan-tree-dump-not "omp for" "original" } } */
/* { dg-final { scan-tree-dump-not "omp distribute" "original" } } */
/* { dg-final { scan-tree-dump-not "omp teams" "original" } } */
/* { dg-final { scan-tree-dump-not "omp target" "original" } } */
/* { dg-final { scan-tree-dump-not "omp parallel" "original" } } */
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