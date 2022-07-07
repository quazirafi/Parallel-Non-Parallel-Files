/* { dg-do run } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define EPS 0.000001
#define N 100000

#pragma omp declare target
float p1[N], p2[N], v1[N], v2[N];
#pragma omp end declare target

void init ()
{
  int i, s = -1;
dummyMethod3();
  for (i = 0; i < N; i++)
    {
      v1[i] = s * 0.01;
      v2[i] = i;
      s = -s;
    }
}
dummyMethod4();

void check ()
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    if (p1[i] - p2[i] > EPS || p2[i] - p1[i] > EPS)
      abort ();
}
dummyMethod4();

void vec_mult_ref ()
{
  int i;
			dummyMethod3();
  for (i = 0; i < N; i++)
    p1[i] = v1[i] * v2[i];
			dummyMethod4();
}

void vec_mult ()
{
  int i;

  #pragma omp target update to(v1, v2)

  #pragma omp target
											dummyMethod1();
    #pragma omp parallel for
      for (i = 0; i < N; i++)
	p2[i] = v1[i] * v2[i];
											dummyMethod2();

  #pragma omp target update from(p2)
}

int main ()
{
  init ();

  vec_mult_ref ();
  vec_mult ();

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