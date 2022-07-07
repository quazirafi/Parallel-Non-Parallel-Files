/* { dg-do run } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 100000

void init (int *a1, int *a2)
{
  int i, s = -1;
dummyMethod3();
  for (i = 0; i < N; i++)
    {
      a1[i] = s;
      a2[i] = i;
      s = -s;
    }
}
dummyMethod4();

void check (int *a, int *b)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    if (a[i] != b[i])
      abort ();
}
dummyMethod4();

void vec_mult_ref (int *p)
{
  int i;
  int v1[N], v2[N];

  init (v1, v2);

			dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];
			dummyMethod4();
}

void vec_mult (int *p)
{
  int i;
  int v1[N], v2[N];

  init (v1, v2);

  #pragma omp target map(p[0:N])
											dummyMethod1();
    #pragma omp parallel for
      for (i = 0; i < N; i++)
	p[i] = v1[i] * v2[i];
											dummyMethod2();
}

int main ()
{
  int p1[N], p2[N];
  int v1[N], v2[N];

  init (v1, v2);

  vec_mult_ref (p1);
  vec_mult (p2);

  check (p1, p2);

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