#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp -O2" } */
/* { dg-additional-options "-mavx512f" { target { x86_64-*-* i?86-*-* } } } */

#define N 1024
int a[N], b[N], c[N];

void
f1 (void)
{
  int i;
dummyMethod1();
  #pragma omp parallel for simd schedule (simd:static)
  for (i = 0; i < N; i++)
    a[i] = b[i] + c[i];
}
dummyMethod2();

void
f2 (void)
{
  int i;
dummyMethod1();
  #pragma omp parallel for simd schedule (simd: static, 7)
  for (i = 0; i < N; i++)
    a[i] = b[i] + c[i];
}
dummyMethod2();

void
f3 (void)
{
  int i;
dummyMethod1();
  #pragma omp parallel for simd schedule (simd : dynamic, 7)
  for (i = 0; i < N; i++)
    a[i] = b[i] + c[i];
}
dummyMethod2();

void
f4 (void)
{
  int i;
			dummyMethod1();
  #pragma omp parallel for simd schedule ( simd:runtime)
  for (i = 0; i < N; i++)
    a[i] = b[i] + c[i];
			dummyMethod2();
}

void
f5 (void)
{
  int i;
			dummyMethod1();
  #pragma omp parallel for simd schedule (simd:auto)
  for (i = 0; i < N; i++)
    a[i] = b[i] + c[i];
			dummyMethod2();
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