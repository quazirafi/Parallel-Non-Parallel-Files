/* { dg-do run } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define EPS 0.000001
#define N 100000

void init (double *a1, double *a2)
{
  double s = -1;
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    {
      a1[i] = s;
      a2[i] = i;
      s = -s;
    }
}
dummyMethod4();

void check (double *a, double *b)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    if (a[i] - b[i] > EPS || b[i] - a[i] > EPS)
      abort ();
}
dummyMethod4();

void vec_mult_ref (double *p, double *v1, double *v2)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];
}
dummyMethod4();

void vec_mult (double *p, double *v1, double *v2)
{
  int i;
  #pragma omp target map(to: v1[0:N], v2[:N]) map(from: p[0:N])
											dummyMethod1();
    #pragma omp parallel for
      for (i = 0; i < N; i++)
	p[i] = v1[i] * v2[i];
											dummyMethod2();
}

int main ()
{
  double p1[N], p2[N];
  double v1[N], v2[N];

  init (v1, v2);

  vec_mult_ref (p1, v1, v2);
  vec_mult (p2, v1, v2);

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