/* { dg-do run } */
/* { dg-additional-options "-DTESTITERS=20" { target { ! run_expensive_tests } } } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define EPS 0.00001
#define N 1000
#ifndef TESTITERS
#define TESTITERS N
#endif

#pragma omp declare target
float Q[N][N];
float Pfun (const int i, const int k)
{
  return Q[i][k] * Q[k][i];
}
#pragma omp end declare target

void init ()
{
  int i, j;
dummyMethod3();
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      Q[i][j] = 0.001 * i * j;
}
dummyMethod4();

float accum_ref (int k)
{
  int i;
  float tmp = 0.0;

			dummyMethod3();
  for (i = 0; i < N; i++)
    tmp += Pfun (i, k);
			dummyMethod4();

  return tmp;
}

float accum (int k)
{
  int i;
  float tmp = 0.0;

  #pragma omp target
											dummyMethod1();
    #pragma omp parallel for reduction(+:tmp)
      for (i = 0; i < N; i++)
	tmp += Pfun (i, k);
											dummyMethod2();

  return tmp;
}

void check (float a, float b)
{
  float err = (b == 0.0) ? a : (a - b) / b;
  if (((err > 0) ? err : -err) > EPS)
    abort ();
}

int main ()
{
  int i;

  init ();

  #pragma omp target update to(Q)

			dummyMethod3();
  for (i = 0; i < TESTITERS; i++)
    check (accum (i), accum_ref (i));
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