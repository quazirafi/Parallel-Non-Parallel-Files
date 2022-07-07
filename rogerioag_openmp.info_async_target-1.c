/* { dg-do run } */
/* { dg-additional-options "-DCHUNKSZ=5000" { target { ! run_expensive_tests } } } */
/* { dg-additional-options "-DCHUNKSZ=1000" { target run_expensive_tests } } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define EPS 0.00001
#define N 100000

float Y[N];
float Z[N];

#pragma omp declare target
float F (float a)
{
  return -a;
}
#pragma omp end declare target

void pipedF_ref ()
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    Y[i] = F (Y[i]);
}
dummyMethod4();

void pipedF ()
{
  int i, C;
  for (C = 0; C < N; C += CHUNKSZ)
    {
      #pragma omp task
	#pragma omp target map(Z[C:CHUNKSZ])
									dummyMethod1();
	  #pragma omp parallel for
	    for (i = C; i < C + CHUNKSZ; i++)
	      Z[i] = F (Z[i]);
									dummyMethod2();
    }
  #pragma omp taskwait
}

void init ()
{
  int i;
  for (i = 0; i < N; i++)
    Y[i] = Z[i] = 0.1 * i;
}

void check ()
{
  int i;
  for (i = 0; i < N; i++)
    {
      float err = (Z[i] == 0.0) ? Y[i] : (Y[i] - Z[i]) / Z[i];
      if (((err > 0) ? err : -err) > EPS)
	abort ();
    }
}

int main ()
{
  init ();

  pipedF_ref ();
  pipedF ();

  check ();

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