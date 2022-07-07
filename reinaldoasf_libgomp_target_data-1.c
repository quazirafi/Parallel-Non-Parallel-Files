/* { dg-do run } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int MAX = 1800;

void check (long long *a, long long *b, int N)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    if (a[i] != b[i])
      abort ();
}
dummyMethod4();

void init (long long *a1, long long *a2, int N)
{
  long long s = -1;
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

void vec_mult_ref (long long *p, long long *v1, long long *v2, int N)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];
}
dummyMethod4();

void vec_mult (long long *p, long long *v1, long long *v2, int N)
{
  int i;
  #pragma omp target data map(to: v1[0:N], v2[:N]) map(from: p[0:N])
    #pragma omp target
	dummyMethod1();
      #pragma omp parallel for
	for (i = 0; i < N; i++)
	  p[i] = v1[i] * v2[i];
	dummyMethod2();
}

int main ()
{
  long long *p1 = (long long *) malloc (MAX * sizeof (long long));
  long long *p2 = (long long *) malloc (MAX * sizeof (long long));
  long long *v1 = (long long *) malloc (MAX * sizeof (long long));
  long long *v2 = (long long *) malloc (MAX * sizeof (long long));

  init (v1, v2, MAX);

  vec_mult_ref (p1, v1, v2, MAX);
  vec_mult (p2, v1, v2, MAX);

  check (p1, p2, MAX);

  free (p1);
  free (p2);
  free (v1);
  free (v2);

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